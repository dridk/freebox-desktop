#include "accountlistdialog.h"
#include <QSettings>
AccountListDialog::AccountListDialog(FbxAPI *fbx, QWidget *parent) :
    QDialog(parent)
{

    mFbx = fbx;
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mTableView = new QTableView;
    mModel = new AccountModel;

    mTableView->setModel(mModel);
    mTableView->horizontalHeader()->setStretchLastSection(true);
    mTableView->setAlternatingRowColors(true);
    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableView->verticalHeader()->hide();
    mTableView->setIconSize(QSize(32,32));


    mAddButton = new QPushButton("Nouveau");
    mEditButton = new QPushButton("Editer");
    mRemoveButton = new QPushButton("Supprimer");
    mLoginButton = new QPushButton("Se connecter");
    mAuthLogin = new QPushButton("Auhoriser");
    mCancelButton = new QPushButton("Annuler");
    QVBoxLayout * buttonLayout = new QVBoxLayout;


    buttonLayout->addWidget(mAddButton);
    buttonLayout->addWidget(mEditButton);
    buttonLayout->addWidget(mRemoveButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(mLoginButton);
    buttonLayout->addWidget(mAuthLogin);
    buttonLayout->addWidget(mCancelButton);

    mainLayout->addWidget(mTableView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);


    connect(mAddButton,SIGNAL(clicked()),this,SLOT(add()));
    connect(mEditButton,SIGNAL(clicked()),this,SLOT(edit()));
    connect(mRemoveButton,SIGNAL(clicked()),this,SLOT(remove()));
    connect(mLoginButton,SIGNAL(clicked()),this,SLOT(loginClicked()));
    connect(mAuthLogin,SIGNAL(clicked()),this,SLOT(authClicked()));
    connect(mFbx,SIGNAL(authorizeReceived(QString,int)),this,SLOT(authReceived(QString,int)));

}




void AccountListDialog::add()
{
    AccountDialog dialog(this);
    dialog.setEditMode(false);
    if (dialog.exec() == QDialog::Accepted)
    {
        mModel->addAccount(dialog.name(),
                           dialog.hostName(),
                           dialog.port(),
                           dialog.icon());

    }
    //    mModel->addAccount("home2","mafreebox.free.fr");

}

void AccountListDialog::edit()
{
    AccountDialog dialog(this);

    QModelIndex index=mModel->index(mTableView->currentIndex().row(),0);
    dialog.setData(index.data().toString());
    dialog.setEditMode(true);
    if (dialog.exec() == QDialog::Accepted)
    {
        bool success = mModel->updateAccount(dialog.name(),
                                             dialog.hostName(),
                                             dialog.port(),
                                             dialog.icon());
    }
}

void AccountListDialog::remove()
{
    if (!mTableView->currentIndex().isValid())
        return;

    int row = mTableView->currentIndex().row();
    mModel->removeAccount(row);
}

void AccountListDialog::loginClicked()
{
    if (mTableView->currentIndex().isValid()) {

        mFbx->logout();
        QString currentName = mModel->name(mTableView->currentIndex().row());
        QString token       = mModel->applicationToken(currentName);
        QString hostName    = mModel->hostName(currentName);
        int port            = mModel->port(currentName);

        mFbx->setApplicationToken(token);
        qDebug()<<mFbx->applicationToken();
        mFbx->setHostName(hostName, port);
        mFbx->setApplicationId(qApp->organizationDomain() + qApp->applicationName());
        mFbx->requestLogin();

    }





}

void AccountListDialog::authClicked()
{
    if (mTableView->currentIndex().isValid())
    {
        setEnabled(false);
        QString appId = qApp->organizationDomain() + qApp->applicationName();
        mFbx->requestAuthorize(appId, qApp->applicationName(), qApp->applicationVersion(), QHostInfo::localHostName());

    }
}

void AccountListDialog::authReceived(const QString &token, int trackId)
{

    AuthorizeMessageBox * box = new AuthorizeMessageBox(mFbx, this);
    box->setTrackId(trackId);

    if (box->exec() == QDialog::Accepted)
    {
        QString currentName = mModel->name(mTableView->currentIndex().row());
        mModel->setApplicationToken(currentName, token);
        mFbx  ->setApplicationToken(token);
    }

    else
    {
        QMessageBox::warning(this,"Authorisation", "Authorisation refusé");
    }


    setEnabled(true);

}




