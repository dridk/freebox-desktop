#include "ctmainwindow.h"

CTMainWindow::CTMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{

    mListView = new CTListView;
    mModel = new CTModel(fbx());
    mListView->setModel(mModel);
    mDetailWidget = new CTDetailWidget;

    QDockWidget * leftDock = new QDockWidget;
    leftDock->setWidget(mListView);

    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    setCentralWidget(mDetailWidget);

//    centralWidget()->setStyleSheet("background-color:white");

    connect(fbx(),SIGNAL(loginSuccess()),
            fbx()->contact(), SLOT(requestList()));

    resize(600, 400);

}
