#ifndef ABSTRACTMAINWINDOW_H
#define ABSTRACTMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "fbxapi.h"
#include "authorizemessagebox.h"
#include "aboutdialog.h"
#include "accountlistdialog.h"
#include "authorizemessagebox.h"
class AbstractMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AbstractMainWindow(QWidget *parent = 0);
    ~AbstractMainWindow();

    FbxAPI * fbx() {
        return mFbx;
    }


public slots:
    void login(const QString& name);
    void authorize(const QString& name);


protected slots:
    void showError();
    void authorizeReceived(const QString& token ,int trackId);
    void showAboutDialog();
    void showAccountDialog();
    void openGithub();
    void loginSuccess();
    void loadAccountList();
    void loginFromAction();




private:
    FbxAPI * mFbx;
    AccountListDialog* mAccountsDialog;
    QLabel * mStatusLabel;
    QMenu * mFreeboxMenu;
    QString mCurrentLoginName;
};

#endif // ABSTRACTMAINWINDOW_H
