#include "dlmainwindow.h"

DLMainWindow::DLMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{


    mModel = new DLModel(fbx());
    mView  = new DLTableView;
    mCategoryWidget = new DLCategoryWidget;
    mDetailWidget = new DLDetailWidget;
    mDelegate = new DLDelegate;
    mView->setModel(mModel);
    mView->setItemDelegate(mDelegate);
    mView->verticalHeader()->setDefaultSectionSize(20);
    mView->setColumnWidth(2, 300);
    mView->setColumnWidth(4, 200);

    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    mView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Interactive);
        mView->horizontalHeader()->setSectionResizeMode(9,QHeaderView::Stretch);
    mView->setAlternatingRowColors(true);

    QDockWidget * mLeftDock = new QDockWidget;
    mLeftDock->setWidget(mCategoryWidget);
    addDockWidget(Qt::LeftDockWidgetArea, mLeftDock);


    QSplitter * splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(mView);
    splitter->addWidget(mDetailWidget);

    setCentralWidget(splitter);

    QToolBar * toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //1st action
    QToolButton * newDLButton = new QToolButton;
    newDLButton->setAutoRaise(true);
    newDLButton->setIcon(QIcon(":add.png"));
    newDLButton->setText("Nouveau téléchargement");
    newDLButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    newDLButton->setMenu(new QMenu);
    newDLButton->menu()->addAction(QIcon(":world_add.png"),"Téléchargement depuis une URL");
    newDLButton->menu()->addAction(QIcon(":page_add.png"),"Téléchargement depuis un fichier");
    newDLButton->menu()->addAction(QIcon(":cog_add.png"),"Téléchargement avancé");
    newDLButton->setPopupMode(QToolButton::InstantPopup);

    toolBar->addWidget(newDLButton);

    //2nd action
    toolBar->addAction(QIcon(":setting_tools.png"),"Paramètres");

    //3th action
    QToolButton * manageButton = new QToolButton;
    manageButton->setText("Gestion");
    manageButton->setIcon(QIcon(":control_play_blue.png"));
    manageButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    manageButton->setMenu(new QMenu);
    manageButton->menu()->addAction(QIcon(":control_pause_blue.png"),"Tout susprendre");
    manageButton->menu()->addAction(QIcon(":control_play_blue.png"),"Tout reprendre");
    manageButton->menu()->addAction(QIcon(":bin_recycle.png"),"Supprimer les tâches terminées");
    manageButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(manageButton);

    QToolBar * addBar = new QToolBar("ajout direct");
    QToolButton * rssButton = new QToolButton;
    rssButton->setText("Flux RSS");
    rssButton->setIcon(QIcon(":rss_add.png"));
    rssButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    rssButton->setMenu(new QMenu);
    rssButton->menu()->addAction(QIcon(":rss_add.png"),"Nouveau flux RSS");
    rssButton->menu()->addAction(QIcon(":rss_go.png"),"Mettre à jour les RSS");
    rssButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(rssButton);
    addBar->addWidget(new QLabel("Ajout direct:"));
    addBar->addWidget(new QLineEdit);
    addBar->addAction(QIcon(":add.png"),"+");
    addBar->setMovable(true);

    addToolBar(toolBar);
    addToolBar(addBar);


    QAction * test = toolBar->addAction("START AUTO REFRESH");

    connect(test,SIGNAL(triggered()),mModel,SLOT(start()));

}
