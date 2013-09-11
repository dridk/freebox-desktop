#include "dlmainwindow.h"

DLMainWindow::DLMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{

    mView  = new DLTableView(fbx());
    mCategoryWidget = new DLCategoryWidget;
    mDetailWidget = new DLDetailWidget;
    mDirectUrlEdit =  new QLineEdit;
    mPlotWidget  = new DLPlotWidget;
    mStatusTimer = new QTimer;

    QDockWidget * mLeftDock = new QDockWidget;
    mLeftDock->setWidget(mCategoryWidget);
    addDockWidget(Qt::LeftDockWidgetArea, mLeftDock);

    QDockWidget * plotDock = new QDockWidget;
    plotDock->setWidget(mPlotWidget);
    addDockWidget(Qt::LeftDockWidgetArea, plotDock);





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
    newDLButton->menu()->addAction(QIcon(":world_add.png"),"Téléchargement depuis une URL",this,SLOT(addUrl()));
    newDLButton->menu()->addAction(QIcon(":page_add.png"),"Téléchargement depuis un fichier",this,SLOT(addFile()));
    newDLButton->menu()->addAction(QIcon(":cog_add.png"),"Téléchargement avancé",this,SLOT(addAdvancedUrl()));
    newDLButton->setPopupMode(QToolButton::InstantPopup);

    toolBar->addWidget(newDLButton);

    //2nd action
    toolBar->addAction(QIcon(":setting_tools.png"),"Paramètres",this,SLOT(showConfigDialog()));

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
    addBar->addWidget(mDirectUrlEdit);
    addBar->addAction(QIcon(":add.png"),"+",this,SLOT(addDirectUrl()));
    addBar->setMovable(true);

    addToolBar(toolBar);
    addToolBar(addBar);

    //======== Define Timer to update Status ( plot and statusBar)
        mStatusTimer->setInterval(1000);
        mStatusTimer->setSingleShot(true);

    connect(fbx()->download(),SIGNAL(statsReceived(DownloadStats)),
            this,SLOT(setStats(DownloadStats)));

    connect(fbx(),SIGNAL(loginSuccess()),mStatusTimer,SLOT(start()));
    connect(mStatusTimer,SIGNAL(timeout()),fbx()->download(),SLOT(requestStats()));

    connect(mCategoryWidget,SIGNAL(statusClicked(QString)), mView, SLOT(setStatusFilter(QString)));
    connect(mDirectUrlEdit,SIGNAL(returnPressed()),this,SLOT(addDirectUrl()));


    setWindowTitle("Téléchargement");
    setWindowIcon(QIcon(":main_dl.png"));

}

void DLMainWindow::addUrl()
{
    DLAddDialog dialog(fbx(),this);

    dialog.exec();


}

void DLMainWindow::addFile()
{
}

void DLMainWindow::addAdvancedUrl()
{


}

void DLMainWindow::addDirectUrl()
{
    fbx()->download()->requestAdd(mDirectUrlEdit->text());
    mDirectUrlEdit->clear();

}

void DLMainWindow::showConfigDialog()
{

    mView->setAutoUpdate(false);

    DLConfigDialog dialog(fbx());
    connect(fbx()->download(),SIGNAL(configReceived(DownloadConfiguration)),
            &dialog,SLOT(setConfiguration(DownloadConfiguration)));

    fbx()->download()->requestConfig();
    dialog.exec();
    mView->setAutoUpdate(true);
}

void DLMainWindow::setStats(const DownloadStats &stats)
{
    qDebug()<<"stats";


    statusBar()->showMessage(QString::number(stats.rxRate));

    mStatusTimer->start(1000);
}
