#include "accountdialog.h"
#include <QSettings>
AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent)
{

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mTableView = new QTableView;
    mModel = new QStandardItemModel;

    mModel->setColumnCount(2);
    mModel->setHorizontalHeaderLabels(QStringList()<<"Nom"<<"Server");
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

void AccountDialog::load()
{
    mModel->clear();
    QSettings settings;
    settings.beginGroup("accounts");

    foreach (QString key, settings.childGroups())
    {

        settings.beginGroup(key);
        QFont font;
        font.setBold(settings.value("default").toBool());
        QStandardItem * nameItem = new QStandardItem;
        nameItem->setText(key);
        nameItem->setFont(font);

        QStandardItem * hostItem = new QStandardItem;
        hostItem->setText(settings.value("hostname").toString());
        hostItem->setFont(font);

        QList<QStandardItem*> items;
        items.append(nameItem);
        items.append(hostItem);
        mModel->appendRow(items);


        settings.endGroup();


    }


    settings.endGroup();



}

void AccountDialog::add()
{
    QSettings settings;
    settings.beginGroup("accounts");
    settings.remove("test");
    settings.beginGroup("test");

    settings.setValue("hostname", "mafreebox.free.fr");
    settings.setValue("port", "80");
    settings.setValue("icon", "icon");
    settings.setValue("default", true);


    settings.endGroup();
    settings.endGroup();
    load();
}

void AccountDialog::edit()
{
}

void AccountDialog::remove()
{
}

void AccountDialog::exportKey()
{
}

void AccountDialog::setDefault()
{
}


