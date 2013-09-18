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
    AccountModel * model();

signals:
    void loginClicked(const QString& name);
    void authClicked(const QString& name);

public slots:
    void add();
    void edit();
    void remove();

protected slots:
    void onLoginClicked();
    void onAuthClicked();


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
