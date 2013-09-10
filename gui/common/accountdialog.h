#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "iconbutton.h"
class AccountDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AccountDialog(QWidget *parent = 0);
    ~AccountDialog();


private:
    QLineEdit * mNameEdit;
    QLineEdit * mHostNameEdit;
    QSpinBox  * mPortSpinBox;
    QDialogButtonBox * mButtonBox;
    IconButton * mIconButton;




    
};

#endif // ACCOUNTDIALOG_H
