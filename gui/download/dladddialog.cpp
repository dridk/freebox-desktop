#include "dladddialog.h"
#include <QGroupBox>
#include <QDialogButtonBox>
#include "fsdirview.h"
#include "tools.h"
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

    QDialog dialog(this);
    QVBoxLayout *  layout  = new QVBoxLayout(&dialog);
    dialog.setLayout(layout);
    FSDirView view(mFbx);
    QDialogButtonBox buttonBox;
    buttonBox.setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Close);
    connect(&buttonBox,SIGNAL(accepted()),&dialog,SLOT(accept()));
    connect(&buttonBox,SIGNAL(rejected()),&dialog,SLOT(reject()));

    view.init();
    layout->addWidget(&view);
    layout->addWidget(&buttonBox);

    if (dialog.exec() == QDialog::Accepted)
        mDestinationEdit->setText(Tools::pathFrom64(view.currentPath()));
}

void DLAddDialog::add()
{
    if (mUrlEdit->text().isEmpty())
        return;

    if (mDestinationEdit->text().isEmpty())
        mFbx->download()->requestAdd(mUrlEdit->text());

    else
        mFbx->download()->requestAdd(mUrlEdit->text(), Tools::pathTo64(mDestinationEdit->text()));


    accept();

}

void DLAddDialog::urlChanged(const QString &text)
{
    Q_UNUSED(text)




}
