#ifndef ABSTRACTMAINWINDOW_H
#define ABSTRACTMAINWINDOW_H

#include <QMainWindow>
#include "fbxapi.h"
#include "authorizemessagebox.h"
#include "aboutdialog.h"
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
    void login();
    void authorize();

protected slots:
    void showError();
    void authorizeReceived(const QString& token ,int trackId);
    void showAboutDialog();
    void openGithub();

private:
    FbxAPI * mFbx;
};

#endif // ABSTRACTMAINWINDOW_H
