#include "accountdialog.h"
#include <QFormLayout>

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent)
{
    QFormLayout * layout = new QFormLayout;
    mNameEdit = new QLineEdit;
    mHostNameEdit = new QLineEdit;
    mIconButton  = new IconButton;
    mPortSpinBox = new QSpinBox;
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Save|
                                      QDialogButtonBox::Cancel);


    layout->addRow("Icône :", mIconButton);
    layout->addRow("Nom :", mNameEdit);
    layout->addRow("Serveur :", mHostNameEdit);
    layout->addRow("Port :", mPortSpinBox);

    layout->setAlignment(Qt::AlignCenter|Qt::AlignRight);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(mButtonBox);
    setLayout(mainLayout);

}

AccountDialog::~AccountDialog()
{
    delete mNameEdit;
    delete mHostNameEdit;
    delete mPortSpinBox;

}
