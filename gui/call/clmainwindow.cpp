#include "clmainwindow.h"

CLMainWindow::CLMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{
    mView = new QTableView;
    mModel= new CLModel(fbx());

    mView->setModel(mModel);
    setCentralWidget(mView);

    QToolBar * toolbar = new QToolBar(this);

    toolbar->addAction("Recharger",mModel,SLOT(refresh()));
    toolbar->addAction("Tout marquer comme lu");
    toolbar->addAction("Vider l'historique");

    addToolBar(toolbar);

}
