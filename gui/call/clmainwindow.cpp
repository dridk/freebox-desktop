#include "clmainwindow.h"

CLMainWindow::CLMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{
    mView = new QTableView;
    mModel= new CLModel(fbx());
    mDelegate = new CLDelegate;
    mFilterBox = new QComboBox;
    mView->setModel(mModel);
    mView->setItemDelegate(mDelegate);
    setCentralWidget(mView);
    mView->verticalHeader()->hide();
    mView->horizontalHeader()->hide();


    mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->verticalHeader()->setDefaultSectionSize(40);
    mView->verticalHeader()->setIconSize(QSize(64,64));
    mView->setSelectionMode(QAbstractItemView::SingleSelection);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mFilterBox->addItem("Tous les appels");
    mFilterBox->addItem("Appels entrants");
    mFilterBox->addItem("Appels sortants");
    mFilterBox->addItem("Appels manqués");


    QToolBar * toolbar = new QToolBar(this);

    toolbar->addAction("Recharger",mModel,SLOT(refresh()));
    toolbar->addAction("Tout marquer comme lu");
    toolbar->addAction("Vider l'historique");
    toolbar->addSeparator();
    toolbar->addWidget(mFilterBox);

    addToolBar(toolbar);

    login("Maison");

}
