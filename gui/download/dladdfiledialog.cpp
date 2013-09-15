#include "dladdfiledialog.h"

DLAddFileDialog::DLAddFileDialog(QWidget *parent) :
    QDialog(parent)
{
    QFormLayout * layout = new QFormLayout;
    mFileEdit = new QLineEdit;
    mDestEdit = new QLineEdit;
    mPassEdit = new QLineEdit;
    mBoxButton = new QDialogButtonBox(QDialogButtonBox::Ok);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    layout->addRow("Fichier: ", mFileEdit);
    layout->addRow("Destination: ", mDestEdit);
    layout->addRow("Mot de passe: ", mPassEdit);

    mainLayout->addLayout(layout);
    mainLayout->addStretch();
    mainLayout->addWidget(mBoxButton);

    setLayout(mainLayout);



}

DLAddFileDialog::~DLAddFileDialog()
{
    delete mFileEdit;
    delete mDestEdit;
    delete mPassEdit;
}

const QString &DLAddFileDialog::fileName() const
{
    return mFileEdit->text();
}
