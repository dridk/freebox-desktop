#include "dladddialog.h"
#include <QGroupBox>

DLAddDialog::DLAddDialog(FbxAPI *api, QWidget *parent):
    QDialog(parent)
{
    mFbx = api;
    mUrlEdit = new QLineEdit;
    mDestinationEdit = new QLineEdit;
    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    QGroupBox * firstBox = new QGroupBox;
    QGroupBox * secondBox = new QGroupBox;
    QPushButton * destButton = new QPushButton("Modifier");


//    mUrlEdit->setValidator(new QRegExpValidator(QRegExp("^http://|ftp://|https://|magnet:.*")));

    // group Box 1
    firstBox->setTitle("Télécharger depuis une URL");
    QVBoxLayout * firstLayout = new QVBoxLayout;
    firstLayout->addWidget(mUrlEdit);
    firstLayout->addWidget(new QLabel("<b>schémas supportés: </b> (http://, https://, ftp://, magnet:)"));

    // group Box 2
    secondBox->setTitle("Destination");
    QVBoxLayout * secondLayout= new QVBoxLayout;
    QHBoxLayout * lineLayout = new QHBoxLayout;
    lineLayout->addWidget(mDestinationEdit);
    lineLayout->addWidget(destButton);
    QWidget * lineWidget = new QWidget;
    lineWidget->setLayout(lineLayout);
    lineLayout->setContentsMargins(0,0,0,0);
    secondLayout->addWidget(lineWidget);

    firstBox->setLayout(firstLayout);
    secondBox->setLayout(secondLayout);

    QVBoxLayout*mainLayout =  new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->addWidget(firstBox);
    mainLayout->addWidget(secondBox);
    mainLayout->addStretch();
    mainLayout->addWidget(mButtonBox);

    setWindowTitle(firstBox->title());


    resize(400,200);

    connect(destButton,SIGNAL(clicked()),this,SLOT(getDestination()));
    connect(mUrlEdit,SIGNAL(textChanged(QString)),this,SLOT(urlChanged(QString)));
    connect(mButtonBox,SIGNAL(accepted()),this,SLOT(add()));
    connect(mButtonBox,SIGNAL(rejected()),this,SLOT(reject()));

}

void DLAddDialog::getDestination()
{




}

void DLAddDialog::add()
{
    if (mUrlEdit->text().isEmpty())
        return;


  mFbx->download()->requestAdd(mUrlEdit->text());
  accept();

}

void DLAddDialog::urlChanged(const QString &text)
{




}
