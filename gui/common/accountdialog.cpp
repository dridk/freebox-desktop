#include "accountdialog.h"
#include <QSettings>
AccountDialog::AccountDialog(QWidget *parent) :
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

    load();
}


void AccountDialog::add()
{
    mModel->addAccount("home2","mafreebox.free.fr");

}

void AccountDialog::edit()
{
}

void AccountDialog::remove()
{
    mModel->removeAccount(mTableView->currentIndex().row());
}

void AccountDialog::exportKey()
{
}

void AccountDialog::setDefault()
{
    mModel->setDefaultAccount(mTableView->currentIndex().row());
}



