#ifndef ISCONFIRM_H
#define ISCONFIRM_H

#include <QDialog>

namespace Ui {
class isConfirm;
}

class isConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit isConfirm(QWidget *parent = nullptr);
    ~isConfirm();

private:
    Ui::isConfirm *ui;
};

#endif // ISCONFIRM_H
