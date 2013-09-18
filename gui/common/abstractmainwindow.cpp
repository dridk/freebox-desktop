#include "abstractmainwindow.h"
#include <QApplication>
#include <QDesktopServices>
#include <QtWidgets>
#include <QHostInfo>
#include <QSettings>
AbstractMainWindow::AbstractMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mFbx = new FbxAPI;

    //construction du window Menu
    mFreeboxMenu    = new QMenu("Freebox",this);
    mAccountsDialog = new AccountListDialog(mFbx,this);
    mFreeboxMenu->addAction(QIcon(""),"Gestion des freebox...", this,SLOT(showAccountDialog()));
    mFreeboxMenu->addSeparator();
    loadAccountList();


    menuBar()->addMenu(mFreeboxMenu);


    QMenu * helpMenu = new QMenu("Aide",this);
    QAction * githubAction  = helpMenu->addAction(QIcon(":github.png"),"reporter un bug sur Github");
    QAction * aboutAction   = helpMenu->addAction(QIcon(":help.png"),"A propos de "+qApp->applicationName()+"...");
    QAction * aboutQtAction = helpMenu->addAction(QIcon(":qt.png"),"A propos de Qt...");

    menuBar()->addMenu(helpMenu);

    connect(mAccountsDialog,SIGNAL(loginClicked(QString)),this,SLOT(login(QString)));
    connect(mAccountsDialog,SIGNAL(authClicked(QString)),this,SLOT(authorize(QString)));

    connect(fbx(),SIGNAL(authorizeReceived(QString,int)), this,SLOT(authorizeReceived(QString,int)));
    connect(fbx(),SIGNAL(error(QString,QString)), this,SLOT(showError()));
    connect(githubAction,SIGNAL(triggered()),this,SLOT(openGithub()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(showAboutDialog()));
    connect(aboutQtAction,SIGNAL(triggered()),qApp, SLOT(aboutQt()));
    connect(fbx(),SIGNAL(loginSuccess()),this,SLOT(loginSuccess()));

    mStatusLabel = new QLabel;
    mStatusLabel->setPixmap(QPixmap(":low"));
    statusBar()->addPermanentWidget(mStatusLabel);

    setAttribute(Qt::WA_DeleteOnClose);

}

AbstractMainWindow::~AbstractMainWindow()
{
    delete mFbx;
    delete mStatusLabel;
}

void AbstractMainWindow::login(const QString &name)
{
    mFbx->logout();
    mCurrentLoginName   = name;
    QString token       = mAccountsDialog->model()->applicationToken(name);
    QString hostname    = mAccountsDialog->model()->hostName(name);
    int port            = mAccountsDialog->model()->port(name);

    mFbx->setApplicationToken(token);
    mFbx->setHostName(hostname, port);
    mFbx->requestLogin();
}

void AbstractMainWindow::authorize(const QString &name)
{
    mFbx->logout();
    mCurrentLoginName   = name;
    QString hostname    = mAccountsDialog->model()->hostName(name);
    int port            = mAccountsDialog->model()->port(name);
    mFbx->setHostName(hostname, port);
    mFbx->requestAuthorize();
}


void AbstractMainWindow::authorizeReceived(const QString &token, int trackId)
{
    setEnabled(false);
    statusBar()->showMessage("En cours d'authorisation");
    AuthorizeMessageBox * box = new AuthorizeMessageBox(mFbx, this);
    box->setTrackId(trackId);

    if (box->exec() == QDialog::Accepted){

        mFbx  ->setApplicationToken(token);
        mAccountsDialog->model()->setApplicationToken(mCurrentLoginName,token);
        QMessageBox::information(this,"Authorisation", "Authorisation réussi");
    }

    else
    {
        QMessageBox::warning(this,"Authorisation", "Authorisation refusé");
    }

    setEnabled(true);
}

void AbstractMainWindow::showError()
{
    QMessageBox::critical(this,fbx()->errorCode(), fbx()->errorString());

}
void AbstractMainWindow::showAboutDialog()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void AbstractMainWindow::showAccountDialog()
{
    mAccountsDialog->exec();

}

void AbstractMainWindow::openGithub()
{

    QDesktopServices::openUrl(QUrl("https://github.com/dridk/mafreebox/issues?state=open"));

}

void AbstractMainWindow::loginSuccess()
{
    mStatusLabel->setPixmap(QPixmap(":high"));
    statusBar()->showMessage(QString("Vous êtes connecté(e)s sur %1 : %2")
                             .arg(mCurrentLoginName)
                             .arg(fbx()->hostName()));

    mAccountsDialog->close();
}

void AbstractMainWindow::loadAccountList()
{

    foreach (QString name, mAccountsDialog->model()->names()) {

        QAction * action = mFreeboxMenu->addAction(name);
        action->setData(name);
        connect(action,SIGNAL(triggered()),this,SLOT(loginFromAction()));
    }


}

void AbstractMainWindow::loginFromAction()
{

    QAction * action = qobject_cast<QAction*>(sender());
    if (action){
        qDebug()<<"from";
        login(action->data().toString());

    }



}
