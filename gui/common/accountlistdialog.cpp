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
    mLoginButton = new QPushButton(QIcon(":server_connect.png"),"Se connecter");
    mAuthLogin = new QPushButton(QIcon(":email_authentication.png"),"Autoriser");
    mCancelButton = new QPushButton("Annuler");
    QVBoxLayout * buttonLayout = new QVBoxLayout;




    buttonLayout->addWidget(mAddButton);
    buttonLayout->addWidget(mEditButton);
    buttonLayout->addWidget(mRemoveButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(mLoginButton);
    buttonLayout->addWidget(mAuthLogin);
//    buttonLayout->addWidget(mCancelButton);

    mainLayout->addWidget(mTableView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);


    connect(mAddButton,SIGNAL(clicked()),this,SLOT(add()));
    connect(mEditButton,SIGNAL(clicked()),this,SLOT(edit()));
    connect(mRemoveButton,SIGNAL(clicked()),this,SLOT(remove()));
    connect(mLoginButton,SIGNAL(clicked()),this,SLOT(onLoginClicked()));
    connect(mAuthLogin,SIGNAL(clicked()),this,SLOT(onAuthClicked()));

}

AccountModel *AccountListDialog::model()
{
    return mModel;
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

void AccountListDialog::onLoginClicked()
{
    if (mTableView->currentIndex().isValid()) {

        QString currentName = mModel->name(mTableView->currentIndex().row());
        emit loginClicked(currentName);
    }
}

void AccountListDialog::onAuthClicked()
{
    if (mTableView->currentIndex().isValid())
    {
        QString currentName = mModel->name(mTableView->currentIndex().row());
        emit authClicked(currentName);
    }
}




