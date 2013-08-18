#include "fstaskwidget.h"
#include <QVBoxLayout>
FSTaskWidget::FSTaskWidget(MaFreeBox *fbx, QWidget *parent) :
    QWidget(parent)
{
    mFbx = fbx;
    mModel =  new FSTaskModel(mFbx);
    mView   = new QListView;
    mDelegate = new FSTaskDelegate;
    mTimer = new QTimer;


    mTimer->setInterval(1000);

    mView->setModel(mModel);
    mView->setItemDelegate(mDelegate);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(mView);
    setLayout(layout);

    connect(mTimer,SIGNAL(timeout()),mModel,SLOT(load()));


}

void FSTaskWidget::setUpdateDelay(int ms)
{
    mTimer->setInterval(ms);
}

void FSTaskWidget::start()
{
    mTimer->start();
}

void FSTaskWidget::stop()
{
    mTimer->stop();
}
