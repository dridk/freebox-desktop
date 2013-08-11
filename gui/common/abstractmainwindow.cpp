#include "abstractmainwindow.h"
#include <QApplication>
#include <QtWidgets>
AbstractMainWindow::AbstractMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mFbx = new MaFreeBox;

    //construction du window Menu
    QMenu * fileMenu  = new QMenu("File",this);
    QAction * authAction = fileMenu->addAction("Authoriser l'application");
    QAction * loginAction = fileMenu->addAction("Connexion");
    menuBar()->addMenu(fileMenu);

    connect(loginAction,SIGNAL(triggered()),this,SLOT(login()));
    connect(authAction,SIGNAL(triggered()),this,SLOT(authorize()));
    connect(fbx(),SIGNAL(error(QString,QString)), this,SLOT(showError()));
    connect(fbx(),SIGNAL(authorizeReceived(QString,int)),this,SLOT(authorizeReceived(QString,int)));

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
