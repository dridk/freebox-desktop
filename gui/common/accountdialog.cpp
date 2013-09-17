#include "accountdialog.h"
#include <QFormLayout>
#include <QMessageBox>
#include <QSettings>
AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent)
{

    QGroupBox * box = new QGroupBox;
    QHBoxLayout * layout = new QHBoxLayout;
    mNameEdit = new QLineEdit;
    mHostNameEdit = new QLineEdit;
    mIconButton  = new IconButton;
    mPortSpinBox = new QSpinBox;
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Save|
                                      QDialogButtonBox::Cancel);

    box->setLayout(layout);
    box->setTitle("Nouvelle Freebox");

    mNameEdit->setPlaceholderText("Nom de la freebox");
    mNameEdit->setText("Maison");
    mHostNameEdit->setPlaceholderText("hostname");
    mHostNameEdit->setText("mafreebox.freebox.fr");
    mPortSpinBox->setValue(80);


    QFormLayout * formLayout = new QFormLayout;
    formLayout->addRow("Nom :", mNameEdit);
    formLayout->addRow("Serveur :", mHostNameEdit);
    formLayout->addRow("Port :", mPortSpinBox);
    formLayout->setLabelAlignment(Qt::AlignTop);

    layout->addWidget(mIconButton);
    layout->addLayout(formLayout);
    layout->setAlignment(Qt::AlignTop);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(box);
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
