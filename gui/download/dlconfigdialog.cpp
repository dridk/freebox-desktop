#include "dlconfigdialog.h"

DLConfigDialog::DLConfigDialog(FbxAPI *fbx, QWidget *parent) :
    QDialog(parent)
{
    mFbx = fbx;
    mTabWidget= new QTabWidget;
    mButtonBox= new QDialogButtonBox(QDialogButtonBox::Ok|
                                     QDialogButtonBox::Apply|
                                     QDialogButtonBox::Cancel);
    mFeedWidget = new DLFeedConfigWidget;
    mBtWidget   = new DLBtConfigWidget;
    mGeneralWidget= new DLGeneralConfigWidget(mFbx);
    mBlocklistWidget = new DLBlocklistConfigWidget;
    mThrottlingWidget = new DLThrottlingConfigWidget;
    mNewGroupWidget = new DLNewsGroupConfigWidget;

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTabWidget);
    mainLayout->addWidget(mButtonBox);

    setLayout(mainLayout);

    addTab(mThrottlingWidget);
    addTab(mGeneralWidget);
    addTab(mNewGroupWidget);
    addTab(mBtWidget);
    addTab(mFeedWidget);
    addTab(mBlocklistWidget);


    connect(mButtonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(mButtonBox,SIGNAL(clicked(QAbstractButton*)),this,SLOT(acceptClicked(QAbstractButton*)));

}

DLConfigDialog::~DLConfigDialog()
{
    delete mTabWidget;
    delete mButtonBox;
    //    delete mFeedWidget;
    //    delete mBtWidget;
    //    delete mGeneralWidget;
}

void DLConfigDialog::setConfiguration(const DownloadConfiguration &configuration)
{

    mFeedWidget->setConfig(configuration.feed);
    mBtWidget->setConfig(configuration.bt);
    mGeneralWidget->setConfig(configuration);
    mBlocklistWidget->setConfig(configuration.blocklist);
    mThrottlingWidget->setConfig(configuration.throttling);
    mNewGroupWidget->setConfig(configuration.news);




}

void DLConfigDialog::addTab(QWidget *widget)
{

    mTabWidget->addTab(widget, widget->windowIcon(), widget->windowTitle());
}

void DLConfigDialog::acceptClicked(QAbstractButton *button)
{


    if (mButtonBox->buttonRole(button) == QDialogButtonBox::Cancel){
        emit reject();
        return;
    }

    DownloadConfiguration cfg = mGeneralWidget->config();
    cfg.throttling = mThrottlingWidget->config();
    cfg.feed = mFeedWidget->config();
    cfg.bt = mBtWidget->config();
    cfg.blocklist = mBlocklistWidget->config();
    cfg.news = mNewGroupWidget->config();


    mFbx->download()->requestUpdateConfig(cfg);

    qDebug()<<mButtonBox->buttonRole(button);
    if (mButtonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
    {
        emit accept();
        return;
    }

}

