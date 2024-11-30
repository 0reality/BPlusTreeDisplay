#include "mainwindow.h"
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
    QFile qf(":/qss/Combinear.qss");
    if(qf.open(QFile::ReadOnly | QFile::Text)){
        QTextStream r(&qf);
        QString ButtonStyle = r.readAll();
        this->setStyleSheet(ButtonStyle);
    }

    arrowOverlay = new ArrowOverlay(this);
    arrowOverlay->setStyleSheet("background-color:red;");
    arrowOverlay->resize(1000,1000);
    arrowOverlay->show();


    connect(ui->inButton,SIGNAL(clicked(bool)),this,SLOT(inserte()));
    connect(ui->delButton,SIGNAL(clicked(bool)),this,SLOT(delet()));
    connect(ui->findButton,SIGNAL(clicked(bool)),this,SLOT(find()));
}

MainWindow::~MainWindow()
{
    clearTreeLayout();
    delete treeLayout;
    delete treeRankLayout;
    delete treeDate;
    delete treeRankWidget;
    delete tree;
    delete ui;
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
    }
    else{
        QMessageBox::critical(this, "插入失败", "key已经存在!!");
    }
}

void MainWindow::delet(){
    int key = ui->delKeySpinButton->value();
    bool isSuccess = tree->deleteBPNode(key);
    if(isSuccess){
        flushDate();
    }
    else{
        QMessageBox::critical(this, "删除失败", "key不存在!!");
    }
}

void MainWindow::find(){
    int key = ui->findKeySpinBox->value();
    LNode* isSuccess = tree->findBPNode(key);
    if(isSuccess){
        QMessageBox::information(this, "查找成功", "key：" + QString::number(key) + " and value：" + QString::number(isSuccess->getValue()));
    }
    else{
        QMessageBox::critical(this, "删除失败", "key不存在!!");
    }
}

void MainWindow::drawArrows(){
    for(int i = 0;i < treeLayout->size() - 1;i++){
        qDebug() << i << "<-i";
        for(int j = 0;j < (*treeRankWidget)[i].size();j++){
            for(int k = 0;k < (*treeDate)[i][j].size();k++){
                QPoint start = this->mapFromGlobal((*treeDate)[i][j][k]->mapToGlobal(QPoint(0, (*treeDate)[i][j][k]->height())));
                QPoint end = this->mapFromGlobal((*treeRankWidget)[i + 1][k]->mapToGlobal(QPoint((*treeRankWidget)[i + 1][k]->width() / 2, 0)));
                qDebug() << start.x() << " " << start.y() << "->" << end.x() << " " << end.y() << "\n";
                qDebug() << i << " " << j << " " << k << "\n";
                arrowOverlay->addArrow(start,end);
            }
        }
    }
}




