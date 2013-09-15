#include "accountlistdialog.h"
#include <QSettings>
AccountListDialog::AccountListDialog(QWidget *parent) :
    QDialog(parent)
{

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mTableView = new QTableView;
    mModel = new AccountModel;

    mTableView->setModel(mModel);
    mTableView->horizontalHeader()->setStretchLastSection(true);
    mTableView->setAlternatingRowColors(true);
    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableView->verticalHeader()->hide();


    mAddButton = new QPushButton("Nouveau");
    mEditButton = new QPushButton("Editer");
    mRemoveButton = new QPushButton("Supprimer");
    mSetDefaultButton = new QPushButton("Par defaut");
    mExportButton = new QPushButton("Exporter la clef");
    mCancelButton = new QPushButton("Annuler");
    QVBoxLayout * buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(mAddButton);
    buttonLayout->addWidget(mEditButton);
    buttonLayout->addWidget(mRemoveButton);
    buttonLayout->addWidget(mSetDefaultButton);
    buttonLayout->addWidget(mExportButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(mCancelButton);

    mainLayout->addWidget(mTableView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);


    connect(mAddButton,SIGNAL(clicked()),this,SLOT(add()));
    connect(mEditButton,SIGNAL(clicked()),this,SLOT(edit()));
    connect(mRemoveButton,SIGNAL(clicked()),this,SLOT(remove()));
    connect(mExportButton,SIGNAL(clicked()),this,SLOT(exportKey()));
    connect(mSetDefaultButton,SIGNAL(clicked()),this,SLOT(setDefault()));
    connect(mTableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(edit()));
}




void AccountListDialog::add()
{
    AccountDialog dialog(this);
    dialog.setEditMode(false);
    if (dialog.exec() == QDialog::Accepted)
    {

        qDebug()<<dialog.icon();
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
        mModel->updateAccount(dialog.name(),
                           dialog.hostName(),
                           dialog.port(),
                           dialog.icon());
    }
}

void AccountListDialog::remove()
{
    int row = mTableView->currentIndex().row();
    mModel->removeAccount(mModel->nameOf(row));
}

void AccountListDialog::exportKey()
{
}

void AccountListDialog::setDefault()
{
    int row = mTableView->currentIndex().row();
    mModel->setDefaultAccount(mModel->nameOf(row));
}



