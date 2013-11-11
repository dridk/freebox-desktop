#include "ctmainwindow.h"

CTMainWindow::CTMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{

    mListView = new CTListView;
    mModel = new CTModel(fbx());
    mListView->setModel(mModel);
    mDetailWidget = new CTDetailView;

    QDockWidget * leftDock = new QDockWidget;
    leftDock->setWidget(mListView);

    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    setCentralWidget(QWidget::createWindowContainer(mDetailWidget));

    QToolBar * toolbar = new QToolBar();
    addToolBar(toolbar);

    toolbar->addAction("Ajouter un contact");
    toolbar->addAction("Importer des contacts");
    toolbar->addAction("Exporter les contacts");




    connect(fbx(),SIGNAL(loginSuccess()),
            fbx()->contact(), SLOT(requestList()));

    resize(800, 400);

}
