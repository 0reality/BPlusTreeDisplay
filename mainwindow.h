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
#include "BPlusTree.h"
#include "Arrows.h"

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
    int rankNow;
    void flushDate();
    void iterateBPNode(int rank,BPNode* now);
    void iterateLNode(int i,int j,LinkList* linkList,bool isLeaf);
    void clearTreeLayout();
    void clearTreeRankLayout(int j);
    void clearTreeDate(int i,int j);
    void drawArrows();

private slots:
    void inserte();
    void delet();
    void find();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
