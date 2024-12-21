#include "./head/isConfirm.h"
#include "ui_isConfirm.h"

isConfirm::isConfirm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::isConfirm)
{
    ui->setupUi(this);

    connect(ui->buttonBox,SIGNAL(accepted()),parent,SLOT(accept()));
}

isConfirm::~isConfirm()
{
    delete ui;
}
