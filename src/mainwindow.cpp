#include "./head/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //数据初始化
    treeLayout = new QVector<QHBoxLayout*>;
    treeRankLayout = new QVector<QVector<QHBoxLayout*>>;
    treeDate = new QVector<QVector<QVector<QLabel*>>>;
    treeRankWidget = new QVector<QVector<QWidget*>>;
    tree = new BPlusTree(4);

    //初始化串口样式
    QFile qf(":/qss/qss/Button.qss");
    if(qf.open(QFile::ReadOnly | QFile::Text)){
        QTextStream r(&qf);
        QString ButtonStyle = r.readAll();
        this->setStyleSheet(ButtonStyle);
    }

    ui->messegeLabel->setReadOnly(true);

    ui->rankSpinBox->setMinimum(3);
    ui->rankSpinBox->setValue(4);

    arrowOverlay = new ArrowOverlay(ui->displayWidget);

    connect(ui->inButton,SIGNAL(clicked(bool)),this,SLOT(inserte()));
    connect(ui->delButton,SIGNAL(clicked(bool)),this,SLOT(delet()));
    connect(ui->findButton,SIGNAL(clicked(bool)),this,SLOT(find()));
    connect(ui->withdrawButton,SIGNAL(clicked(bool)),this,SLOT(withdraw()));
    connect(ui->rankButton,SIGNAL(clicked(bool)),this,SLOT(rankChange()));
    connect(ui->clearButton,SIGNAL(clicked(bool)),this,SLOT(clearTree()));
}

MainWindow::~MainWindow()
{
    clearTreeLayout();
    delete treeLayout;
    delete treeRankLayout;
    delete treeDate;
    delete treeRankWidget;
    delete tree;
    delete arrowOverlay;
    delete ui;
}

void MainWindow::notingWidget(){
    confirm = new isConfirm(this);
    confirm->show();
}

void MainWindow::rank(){
    int value = ui->rankSpinBox->value();
    delete tree;
    delete confirm;
    addMessage("rank更改为rank=" + QString::number(value),Qt::white);
    clearTreeLayout();
    stack.clear();
    tree = new BPlusTree(value);
    flushDate();
}

void MainWindow::accept(){
    if(choice == 1)rank();
    else{
        clearTreeLayout();
        int rank = tree->getRank();
        delete tree;
        tree = new BPlusTree(rank);
        addMessage("删除了一棵树",Qt::white);
    }
}

void MainWindow::withdraw(){
    if(stack.empty()){
        QMessageBox::critical(this,"撤回失败","已经退回到初始状态");
        return;
    }
    QVector<int> qv = stack.pop();
    switch(qv[0]){
        case 1:
            tree->deleteBPNode(qv[1]);
            break;
        case 2:
            tree->insertBPNode(qv[1],qv[2]);
            break;
        default:break;
    }
    addMessage("撤回了一个操作",Qt::white);
    flushDate();
}

void MainWindow::flushDate(){
    rankNow = -1;
    clearTreeLayout();
    iterateBPNode(0,tree->getRoot());
    drawArrows();
}

void MainWindow::clearTreeLayout(){
    int size = treeLayout->size();
    for(int i = 0;i < size;i++){
        clearTreeRankLayout(i);
        ui->displayBox->removeItem((*treeLayout)[i]);
        delete (*treeLayout)[i];
    }
    treeLayout->clear();
    treeRankLayout->clear();
    treeDate->clear();
    treeRankWidget->clear();
    arrowOverlay->clearArrows();
}

void MainWindow::clearTreeRankLayout(int j){
    int size = (*treeRankLayout)[j].size();
    for(int i = 0;i < size;i++){
        clearTreeDate(j,i);
        (*treeLayout)[j]->removeWidget((*treeRankWidget)[j][i]);
        // (*treeRankWidget)[j][i]->setParent(nullptr);
        delete (*treeRankLayout)[j][i];
        delete (*treeRankWidget)[j][i];
    }
}

void MainWindow::clearTreeDate(int i,int j){
    int size = (*treeDate)[i][j].size();
    for(int k = 0;k < size;k++){
        QLabel* label = (*treeDate)[i][j][k];
        (*treeRankLayout)[i][j]->removeWidget(label);
        delete label;
    }
}

void MainWindow::iterateBPNode(int rank,BPNode* now){
    if(now == nullptr)return;
    if(rank > rankNow){
        QHBoxLayout* qhbl = new QHBoxLayout();
        ui->displayBox->addLayout(qhbl);
        treeLayout->push_back(qhbl);
        treeRankLayout->push_back({});
        treeRankWidget->push_back({});
        treeDate->push_back({});
        rankNow = rank;
    }
    LinkList* linkList = now->getLinkList();
    LNode* p = linkList->getHead();

    QWidget *qw = new QWidget();
    qw->setStyleSheet("border: 2px solid white;"
                      "max-width: " + QString::number(tree->getRank() * 80) + "px;"
                      "min-height: 60px;"
                      "max-height: 60px;"
                      "border-radius: 15px;"
                      );
    (*treeLayout)[rank]->addWidget(qw);
    (*treeRankWidget)[rank].push_back(qw);
    QHBoxLayout *rqhbl = new QHBoxLayout();
    qw->setLayout(rqhbl);
    (*treeRankLayout)[rank].push_back(rqhbl);
    (*treeDate)[rank].push_back({});
    iterateLNode(rank,(*treeRankWidget)[rank].size() - 1,linkList,now->isLeaf());
    while(p != nullptr){
        iterateBPNode(rank + 1,p->getChild());
        p = p->getNext();
    }
}

void MainWindow::iterateLNode(int i,int j,LinkList* linkList,bool isLeaf){
    LNode *p = linkList->getHead();
    while(p != nullptr){
        QString qs = "Key:" + QString::number(p->getKey());
        if(isLeaf)qs += "\nValue:" + QString::number(p->getValue());
        QLabel *ql = new QLabel(qs);
        ql->setStyleSheet("min-width: 60px;"
                     "max-width: 60px;"
                     "min-height: 30px;"
                     "max-height: 30px;"
                     "border-radius: 15px;"
                     "border: 2px solid white;");
        (*treeRankLayout)[i][j]->addWidget(ql);
        (*treeDate)[i][j].push_back(ql);
        p = p->getNext();
    }
}

void MainWindow::inserte(){
    int key = ui->inKeySpinBox->value();
    int value = ui->inValueSpinBox->value();
    bool isSuccess = tree->insertBPNode(key,value);
    if(isSuccess){
        flushDate();
        stack.push({1,key,value});
        addMessage("插入成功一个key:" + QString::number(key) + ",value:" + QString::number(value) + "的节点",Qt::white);
    }
    else{
        QMessageBox::critical(this, "插入失败", "key已经存在!!");
        addMessage("插入失败已经存在key:" + QString::number(key) + "的节点",Qt::white);
    }
}

void MainWindow::delet(){
    int key = ui->delKeySpinButton->value();
    LNode* lNode = tree->findBPNode(key);
    int value = lNode != nullptr ? lNode->getValue() : 0;
    bool isSuccess = tree->deleteBPNode(key);
    if(isSuccess){
        flushDate();
        stack.push({2,key,value});
        addMessage("删除成功key:" + QString::number(key) + "的节点",Qt::white);
    }
    else{
        QMessageBox::critical(this, "删除失败", "key不存在!!");
        addMessage("删除失败,没有找到key:" + QString::number(key) + "的节点",Qt::white);
    }
}

void MainWindow::find(){
    int key = ui->findKeySpinBox->value();
    LNode* isSuccess = tree->findBPNode(key);
    if(isSuccess){
        QString msg = "key：" + QString::number(key) + " and value：" + QString::number(isSuccess->getValue());
        QMessageBox::information(this, "查找成功", msg);
        addMessage("查找到了" + msg,Qt::white);
    }
    else{
        QMessageBox::critical(this, "删除失败", "key不存在!!");
        addMessage("查找失败没有找到key:" + QString::number(key) + "的节点",Qt::white);
    }
}

void MainWindow::drawArrows(){
    arrowOverlay->clearArrows();
    QApplication::processEvents();
    for(int i = 0;i < treeLayout->size() - 1;i++){
        for(int j = 0,total = 0;j < (*treeRankWidget)[i].size();j++){
            for(int k = 0;k < (*treeDate)[i][j].size();k++){
                QLabel* s = (*treeDate)[i][j][k];
                QWidget* e = (*treeRankWidget)[i + 1][total++];
                //qDebug() << s << " " << e;
                QPoint start = arrowOverlay->mapFromGlobal(s->mapToGlobal(QPoint(s->width() / 2, s->height())));
                QPoint end = arrowOverlay->mapFromGlobal(e->mapToGlobal(QPoint(e->width() / 2, 0)));
                //qDebug() << start << "->" << end;
                arrowOverlay->addArrow(start,end,Qt::white,2);
            }
        }
    }
    int maxRankIdx = treeLayout->size() - 1;
    if(maxRankIdx < 0)return;
    int cnt = (*treeRankWidget)[maxRankIdx].size();
    for(int i = 1;i < cnt;i++){
        QWidget* s = (*treeRankWidget)[maxRankIdx][i - 1];
        QWidget* e = (*treeRankWidget)[maxRankIdx][i];
        QPoint start = arrowOverlay->mapFromGlobal(s->mapToGlobal(QPoint(s->width(), s->height() / 2)));
        QPoint end = arrowOverlay->mapFromGlobal(e->mapToGlobal(QPoint(0, e->height() / 2)));
        arrowOverlay->addArrow(start,end,Qt::white,2);
    }
}

void MainWindow::addMessage(const QString &message, const QColor &color)
{
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString("hh:mm:ss");

    appendStyledText("[" + timestamp + "] " + message, color);

    QScrollBar* verticalBar = ui->messegeLabel->verticalScrollBar();

    verticalBar->setValue(verticalBar->maximum());
}

void MainWindow::appendStyledText(const QString &text, const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(color);

    QTextCursor cursor = ui->messegeLabel->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->messegeLabel->setTextCursor(cursor);

    ui->messegeLabel->mergeCurrentCharFormat(format);
    ui->messegeLabel->insertPlainText(text + "\n");
}




