#include "dlgeneralconfigwidget.h"
#include <QFormLayout>
#include "tools.h"
#include "fsdirview.h"
DLGeneralConfigWidget::DLGeneralConfigWidget(FbxAPI *fbx, QWidget *parent) :
    QWidget(parent)
{
    mFbx = fbx;
    QFormLayout * layout = new QFormLayout;
    mMaxDownloadingTasksSpinBox = new QSpinBox;
    mDownloadDirEdit = new QLineEdit;
    mUseWatchDirCheckBox = new QCheckBox;
    mWatchDirEdit = new QLineEdit;
    mDownloadDirButton = new QPushButton("Modifier");
    mWatchDirButton    = new QPushButton("Modifier");

    QHBoxLayout * firstLayout   =new QHBoxLayout;
    QHBoxLayout * secondLayout  =new QHBoxLayout;

    firstLayout->addWidget(mDownloadDirEdit);
    firstLayout->addWidget(mDownloadDirButton);

    secondLayout->addWidget(mWatchDirEdit);
    secondLayout->addWidget(mWatchDirButton);


    layout->addRow("Nombre de téléchargements simultanés :",
                   mMaxDownloadingTasksSpinBox);

    layout->addRow("Dossier de téléchargement :",
                   firstLayout);

    layout->addRow("Utiliser le dossier surveillé :",
                   mUseWatchDirCheckBox);

    layout->addRow("Dossier surveillé:",
                   secondLayout);


    setLayout(layout);
    setWindowTitle("Réglages généraux");
    connect(mWatchDirButton,SIGNAL(clicked()),this,SLOT(getWatchDir()));
    connect(mDownloadDirButton,SIGNAL(clicked()),this,SLOT(getDownloadDir()));

}

DLGeneralConfigWidget::~DLGeneralConfigWidget()
{
    delete mMaxDownloadingTasksSpinBox;
    delete mDownloadDirEdit;
    delete mUseWatchDirCheckBox;
    delete mWatchDirEdit;
}

void DLGeneralConfigWidget::setConfig(const DownloadConfiguration &cfg)
{
    mCfg = cfg;
    mMaxDownloadingTasksSpinBox->setValue(cfg.maxDownloadingTasks);
    mDownloadDirEdit->setText(Tools::pathFrom64(cfg.downloadDir));
    mUseWatchDirCheckBox->setChecked(cfg.useWatchDir);
    mWatchDirEdit->setText(Tools::pathFrom64(cfg.watchDir));

}

const DownloadConfiguration &DLGeneralConfigWidget::config()
{

    mCfg.maxDownloadingTasks = mMaxDownloadingTasksSpinBox->value();
    mCfg.downloadDir = Tools::pathTo64(mDownloadDirEdit->text());
    mCfg.useWatchDir = mUseWatchDirCheckBox->checkState() == Qt::Checked;
    mCfg.watchDir = Tools::pathTo64(mWatchDirEdit->text());

    return mCfg;
}

void DLGeneralConfigWidget::getWatchDir()
{
    QDialog dialog;

    // faut faire un QString path = FSDirDialog::getDirectory()
    FSDirView view(mFbx);
    view.init();
    dialog.setLayout(new QVBoxLayout);
    dialog.layout()->addWidget(&view);
    dialog.exec();

}

void DLGeneralConfigWidget::getDownloadDir()
{
}
