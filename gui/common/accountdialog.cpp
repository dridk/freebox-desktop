#include "accountdialog.h"
#include <QFormLayout>
#include <QMessageBox>
#include <QSettings>
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

    connect(mButtonBox,SIGNAL(accepted()),this,SLOT(validate()));
    connect(mButtonBox,SIGNAL(rejected()),this,SLOT(reject()));




}

AccountDialog::~AccountDialog()
{
    delete mNameEdit;
    delete mHostNameEdit;
    delete mPortSpinBox;
}

 QString AccountDialog::name() const
{
    return mNameEdit->text();
}

 QString AccountDialog::hostName() const
{
    return mHostNameEdit->text();
}

int AccountDialog::port() const
{
    return mPortSpinBox->value();
}

 QIcon AccountDialog::icon() const
{
     return mIconButton->icon();
 }

 void AccountDialog::setEditMode(bool enable)
 {
     mNameEdit->setDisabled(enable);
 }

 void AccountDialog::setData(const QString &name)
 {
    QSettings settings;
    settings.beginGroup("accounts");
     settings.beginGroup(name);

     mNameEdit->setText(name);
     mHostNameEdit->setText(settings.value("hostname").toString());
     mPortSpinBox->setValue(settings.value("port").toInt());
     mIconButton->setIcon(settings.value("icon").value<QIcon>());

     settings.endGroup();
     settings.endGroup();


 }

 void AccountDialog::validate()
 {

     if (mHostNameEdit->text().isEmpty() || mNameEdit->text().isEmpty())
     {
         QMessageBox::warning(this,"Erreur","Veuillez remplir tous les champs");
         return;
     }

     accept();
 }
