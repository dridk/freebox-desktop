#include "fstaskwidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QToolBar>
FSTaskWidget::FSTaskWidget(MaFreeBox *fbx, QWidget *parent) :
    QWidget(parent)
{
    mFbx = fbx;
    mModel =  new FSTaskModel(mFbx);
    mDownloadModel = new FSDownloadModel(mFbx);
    mView   = new QListView;
    mDelegate = new FSTaskDelegate;
    mTimer = new QTimer;
    mTabWidget = new QTabWidget;


//    mTimer->setInterval(1000);

    mView->setAlternatingRowColors(true);

    mView->setModel(mDownloadModel);
    mView->setItemDelegate(mDelegate);

    mTabWidget->addTab(mView,QIcon(":inbox_download"),"Download");
    mTabWidget->addTab(new QWidget,QIcon(":inbox_upload"),"Upload");


    setLayout(new QVBoxLayout);
    QToolBar * test = new QToolBar();
    test->addAction("Effacer les terminés");
    test->addAction("Arreter");
    layout()->addWidget(test);
    layout()->addWidget(mTabWidget);

    connect(mDownloadModel,SIGNAL(countChanged()),this,SIGNAL(countChanged()));
    resize(700,480);

}

void FSTaskWidget::setUpdateDelay(int ms)
{
//    mTimer->setInterval(ms);
}

void FSTaskWidget::start()
{
//    mTimer->start();
}

void FSTaskWidget::stop()
{
    //    mTimer->stop();
}

int FSTaskWidget::count()
{
    return mDownloadModel->count();
}


