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

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTabWidget);
    mainLayout->addWidget(mButtonBox);

    setLayout(mainLayout);

    addTab(mThrottlingWidget);
    addTab(mGeneralWidget);
    addTab(mBtWidget);
    addTab(mFeedWidget);
    addTab(mBlocklistWidget);



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




}

void DLConfigDialog::addTab(QWidget *widget)
{

    mTabWidget->addTab(widget, widget->windowIcon(), widget->windowTitle());
}

