#ifndef ACCOUNTLISTDIALOG_H
#define ACCOUNTLISTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "accountmodel.h"
#include "accountdialog.h"
#include "fbxapi.h"
#include "authorizemessagebox.h"
class AccountListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AccountListDialog(FbxAPI * fbx,QWidget *parent = 0);

signals:
    
public slots:
    void add();
    void edit();
    void remove();

protected slots:
    void loginClicked();
    void authClicked();
    void authReceived(const QString& token ,int trackId);


private:
    QTableView * mTableView;
    AccountModel * mModel;
    QPushButton * mAddButton;
    QPushButton * mEditButton;
    QPushButton * mRemoveButton;
    QPushButton * mLoginButton;
    QPushButton * mAuthLogin;
    QPushButton * mCancelButton;
    FbxAPI * mFbx;
    
};

#endif // ACCOUNTLISTDIALOG_H
