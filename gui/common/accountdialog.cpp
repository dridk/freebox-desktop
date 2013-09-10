#include "accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent)
{

    QHBoxLayout * mainLayout = new QHBoxLayout;
    mTableWidget = new QTableWidget;

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

    mainLayout->addWidget(mTableWidget);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);


}
