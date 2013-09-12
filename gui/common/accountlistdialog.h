#ifndef ACCOUNTLISTDIALOG_H
#define ACCOUNTLISTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "accountmodel.h"
#include "accountdialog.h"
class AccountListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AccountListDialog(QWidget *parent = 0);

signals:
    
public slots:
    void add();
    void edit();
    void remove();
    void exportKey();
    void setDefault();

private:
    QTableView * mTableView;
    AccountModel * mModel;
    QPushButton * mAddButton;
    QPushButton * mEditButton;
    QPushButton * mRemoveButton;
    QPushButton * mSetDefaultButton;
    QPushButton * mExportButton;
    QPushButton * mCancelButton;
    
};

#endif // ACCOUNTLISTDIALOG_H
