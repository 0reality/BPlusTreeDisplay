#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QLayout>
#include <QLabel>
#include <QtMath>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QStackedLayout>
#include <QResizeEvent>
#include <QTime>
#include <QScrollBar>
#include <QStack>
#include "BPlusTree.h"
#include "arrowoverlay.h"
#include "isConfirm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QVector<QHBoxLayout*> *treeLayout;
    QVector<QVector<QHBoxLayout*>> *treeRankLayout;
    QVector<QVector<QWidget*>> *treeRankWidget;
    QVector<QVector<QVector<QLabel*>>> *treeDate;
    BPlusTree *tree;
    ArrowOverlay *arrowOverlay;
    QVector<QString> msgs;
    QStack<QVector<int>> stack;
    isConfirm* confirm;
    int rankNow;
    void flushDate();
    void iterateBPNode(int rank,BPNode* now);
    void iterateLNode(int i,int j,LinkList* linkList,bool isLeaf);
    void clearTreeLayout();
    void clearTreeRankLayout(int j);
    void clearTreeDate(int i,int j);
    void drawArrows();
    void addMessage(const QString &message, const QColor &color = Qt::black);
    void appendStyledText(const QString &text, const QColor &color);

private slots:
    void inserte();
    void delet();
    void find();
    void withdraw();
    void rank();
    void notingWidget();

protected:
    void resizeEvent(QResizeEvent *event) override {
        QWidget::resizeEvent(event);
        if (arrowOverlay) {
            arrowOverlay->resize(event->size());
            drawArrows();
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
