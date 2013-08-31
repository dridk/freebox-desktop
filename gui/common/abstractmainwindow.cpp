#include "abstractmainwindow.h"
#include <QApplication>
#include <QDesktopServices>
#include <QtWidgets>
AbstractMainWindow::AbstractMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mFbx = new MaFreeBox;

    //construction du window Menu
    QMenu * fileMenu  = new QMenu("Fichier",this);
    QAction * authAction = fileMenu->addAction(QIcon(":email_authentication.png"),"Authoriser l'application");
    QAction * loginAction = fileMenu->addAction(QIcon(":server_connect.png"),"Connexion");
    menuBar()->addMenu(fileMenu);


    QMenu * helpMenu = new QMenu("Aide",this);
    QAction * githubAction  = helpMenu->addAction(QIcon(":github.png"),"reporter un bug sur Github");
    QAction * aboutAction   = helpMenu->addAction(QIcon(":help.png"),"A propos de "+qApp->applicationName()+"...");
    QAction * aboutQtAction = helpMenu->addAction(QIcon(":qt.png"),"A propos de Qt...");

    menuBar()->addMenu(helpMenu);

    connect(loginAction,SIGNAL(triggered()),this,SLOT(login()));
    connect(authAction,SIGNAL(triggered()),this,SLOT(authorize()));
    connect(fbx(),SIGNAL(error(QString,QString)), this,SLOT(showError()));
    connect(fbx(),SIGNAL(authorizeReceived(QString,int)),this,SLOT(authorizeReceived(QString,int)));
    connect(githubAction,SIGNAL(triggered()),this,SLOT(openGithub()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(showAboutDialog()));
    connect(aboutQtAction,SIGNAL(triggered()),qApp, SLOT(aboutQt()));

}

AbstractMainWindow::~AbstractMainWindow()
{
    delete mFbx;
}

void AbstractMainWindow::login()
{

    qDebug()<<qApp->applicationName();
    fbx()->setApplicationId("org.labsquare" + qApp->applicationName());
    fbx()->requestLogin();
}

void AbstractMainWindow::authorize()
{
    QString appId = "org.labsquare" + qApp->applicationName();
    fbx()->requestAuthorize(appId, qApp->applicationName(), qApp->applicationVersion(), "Desktop");
}

void AbstractMainWindow::showError()
{
    QMessageBox::critical(this,fbx()->errorCode(), fbx()->errorString());

}

void AbstractMainWindow::authorizeReceived(const QString &token, int trackId)
{
    AuthorizeMessageBox * box = new AuthorizeMessageBox(mFbx, this);
    box->setTrackId(trackId);

    if (box->exec() == QDialog::Accepted)
    {
        fbx()->setApplicationToken(token);
        fbx()->saveApplicationToken();
        login();
    }

    else
    {
        QMessageBox::warning(this,"Authorisation", "Authorisation refusé");
    }


}

void AbstractMainWindow::showAboutDialog()
{
    AboutDialog dialog;
    dialog.exec();
}

void AbstractMainWindow::openGithub()
{

    QDesktopServices::openUrl(QUrl("https://github.com/dridk/mafreebox/issues?state=open"));

}
