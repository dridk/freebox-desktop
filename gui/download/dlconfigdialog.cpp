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

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTabWidget);
    mainLayout->addWidget(mButtonBox);

    setLayout(mainLayout);

    addTab(mGeneralWidget);
    addTab(mBtWidget);
    addTab(mFeedWidget);



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

    mFeedWidget->setFetchInterval(configuration.feed.fetchInterval);
    mFeedWidget->setMaxItems(configuration.feed.maxItems);

    mBtWidget->setConfig(configuration.bt);
    mGeneralWidget->setConfig(configuration);





}

void DLConfigDialog::addTab(QWidget *widget)
{

    mTabWidget->addTab(widget, widget->windowIcon(), widget->windowTitle());
}

