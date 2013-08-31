#include "dlmainwindow.h"

DLMainWindow::DLMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{


    mModel = new DLModel;
    mView  = new DLTableView;
    mCategoryWidget = new DLCategoryWidget;
    mDetailWidget = new DLDetailWidget;
    mView->setModel(mModel);


    QDockWidget * mLeftDock = new QDockWidget;
    mLeftDock->setWidget(mCategoryWidget);
    addDockWidget(Qt::LeftDockWidgetArea, mLeftDock);


    QSplitter * splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(mView);
    splitter->addWidget(mDetailWidget);

    setCentralWidget(splitter);

    QToolBar * toolBar = new QToolBar;

    //1st action
    QToolButton * newDLButton = new QToolButton;
    newDLButton->setAutoRaise(true);
    newDLButton->setMenu(new QMenu);
    newDLButton->menu()->addAction(QIcon(""),"Téléchargement depuis une URL");
    newDLButton->menu()->addAction(QIcon(""),"Téléchargement depuis un fichier");
    newDLButton->menu()->addAction(QIcon(""),"Téléchargement avancé");
    newDLButton->setPopupMode(QToolButton::InstantPopup);
    newDLButton->setText("Nouveau téléchargement");

    toolBar->addWidget(newDLButton);

    //2nd action
    toolBar->addAction(QIcon(),"Paramètres");

    //3th action
    QToolButton * manageButton = new QToolButton;
    manageButton->setText("Gestion");
    manageButton->setMenu(new QMenu);
    manageButton->menu()->addAction(QIcon(),"Tout susprendre");
    manageButton->menu()->addAction(QIcon(),"Tout reprendre");
    manageButton->menu()->addAction(QIcon(),"Supprimer les tâches terminées");
    manageButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(manageButton);

    QToolBar * addBar = new QToolBar("ajout direct");
    QToolButton * rssButton = new QToolButton;
    rssButton->setText("Flux RSS");
    rssButton->setMenu(new QMenu);
    rssButton->menu()->addAction(QIcon(),"Nouveau flux RSS");
    rssButton->menu()->addAction(QIcon(),"Mettre à jour les RSS");
    rssButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(rssButton);
    addBar->addWidget(new QLabel("Ajout direct:"));
    addBar->addWidget(new QLineEdit);
    addBar->addAction(QIcon(),"+");
    addBar->setMovable(true);

    addToolBar(toolBar);
    addToolBar(addBar);

}
