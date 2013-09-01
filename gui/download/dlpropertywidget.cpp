#include "dlpropertywidget.h"
#include "fsmodel.h"
DLPropertyWidget::DLPropertyWidget(QWidget *parent) :
    QDialog(parent)
{

    QFormLayout * layout = new QFormLayout;
    mMapper       = new QDataWidgetMapper;
    mNameLabel       = new QLabel;
    mStatusLabel     = new QLabel;
    mCreatedTsLabel  = new QLabel;
    mSizeLabel       = new QLabel;
    mIoPriorityLabel = new QLabel;
    mDownloadDirLabel= new QLabel;
    mTxBytesLabel    = new QLabel;
    mRxBytesLabel    = new QLabel;
    mTxRateLabel     = new QLabel;
    mRxRateLabel     = new QLabel;
    mErrorLabel      = new QLabel;
    mToolButton      = new QDialogButtonBox;
    mToolButton->setStandardButtons(QDialogButtonBox::Ok);

    mNameLabel->setWordWrap(true);

    layout->addRow("Nom:", mNameLabel);
    layout->addRow("Statut:", mStatusLabel);
    layout->addRow("Date d'ajout:", mCreatedTsLabel);
    layout->addRow("Taille:", mSizeLabel);
    layout->addRow("Priorité:", mIoPriorityLabel);
    layout->addRow("Destionation:", mDownloadDirLabel);
    layout->addRow("Reçu:", mRxBytesLabel);
    layout->addRow("Réception:", mRxRateLabel);
    layout->addRow("Emis:", mTxBytesLabel);
    layout->addRow("Emission:", mTxRateLabel);
    layout->addRow("Erreur:", mErrorLabel);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addStretch();
    mainLayout->addWidget(mToolButton);

    connect(mToolButton,SIGNAL(accepted()),this,SLOT(accept()));
    setLayout(mainLayout);



}

void DLPropertyWidget::setCurrentIndex(const QModelIndex &index)
{

    qDebug()<<"set current..";

    mMapper->addMapping(mNameLabel,2,"text");
    mMapper->addMapping(this,2,"windowTitle");

    mMapper->addMapping(mSizeLabel,3,"text");
 mMapper->addMapping(mIoPriorityLabel,5,"text");

    mMapper->addMapping(mRxRateLabel,7,"text");
    mMapper->addMapping(mTxRateLabel,8,"text");

    mMapper->addMapping(mCreatedTsLabel,9,"text");

    mMapper->setCurrentIndex(index.row());




}

//void DLPropertyWidget::setData(const DownloadTask &task)
//{

//    mNameLabel->setText(task.name);
//    mStatusLabel->setText(task.status);
//    mCreatedTsLabel->setText(task.createdTs.toString());
//    mSizeLabel->setText(FSModel::sizeHuman(task.size));
//    mIoPriorityKLabel->setText(task.ioPriority);
//    mDownloadDirLabel->setText(task.downloadDir);
//    mTxBytesLabel->setText(FSModel::sizeHuman(task.txBytes));
//    mRxBytesLabel->setText(FSModel::sizeHuman(task.rxBytes));
//    mTxRateLabel->setText(FSModel::sizeHuman(task.txRate)+"/s");
//    mRxRateLabel->setText(FSModel::sizeHuman(task.rxRate)+"/s");
//    mErrorLabel->setText(task.error);



//}

void DLPropertyWidget::setModel(QAbstractItemModel *model)
{
    mMapper->setModel(model);
}
