#include "dlmainwindow.h"
#include <QFileDialog>
DLMainWindow::DLMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{

    mView  = new DLTableView(fbx());
    mCategoryWidget = new DLCategoryWidget;
    mDetailWidget = new DLDetailWidget;
    mDirectUrlEdit =  new QLineEdit;



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
    manageButton->menu()->addAction(QIcon(":control_pause_blue.png"),"Tout susprendre",
                                    this,SLOT(suspendAll()));
    manageButton->menu()->addAction(QIcon(":control_play_blue.png"),"Tout reprendre",
                                    this,SLOT(revivalAll()));
    //    manageButton->menu()->addAction(QIcon(":bin_recycle.png"),"Supprimer les tâches terminées");
    manageButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(manageButton);

    QToolBar * addBar = new QToolBar("ajout direct");
    QToolButton * rssButton = new QToolButton;
    rssButton->setText("Flux RSS");
    rssButton->setIcon(QIcon(":rss_add.png"));
    rssButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    rssButton->setDisabled(true);
    rssButton->setMenu(new QMenu);
    rssButton->menu()->addAction(QIcon(":rss_add.png"),"Nouveau flux RSS");
    rssButton->menu()->addAction(QIcon(":rss_go.png"),"Mettre à jour les RSS");
    rssButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(rssButton);
    //    addBar->addWidget(new QLabel("Ajout direct:"));
    addBar->addWidget(mDirectUrlEdit);
    addBar->addAction(QIcon(":add.png"),"+",this,SLOT(addDirectUrl()));
    addBar->setMovable(true);

    addToolBar(Qt::TopToolBarArea,toolBar);
    addToolBar(Qt::TopToolBarArea,addBar);

    connect(mCategoryWidget,SIGNAL(statusClicked(QString)), mView, SLOT(setStatusFilter(QString)));
    connect(mDirectUrlEdit,SIGNAL(returnPressed()),this,SLOT(addDirectUrl()));
    connect(fbx(),SIGNAL(loginSuccess()),this,SLOT(addPathFromArgs()));

    setWindowTitle("Téléchargement");
    setWindowIcon(QIcon(":main_dl.png"));

    mLeftDock->setMaximumWidth(150);


}

void DLMainWindow::addUrl()
{
    DLAddDialog dialog(fbx(),this);

    dialog.exec();


}

void DLMainWindow::addFile()
{
    //    DLAddFileDialog dialog;
    //    dialog.exec();

    //test

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Images (*.torrent *.nzb)"));

    fbx()->download()->requestAddFile(fileName);

}

void DLMainWindow::addFile(const QString &path)
{
    QFileInfo info(path);
    if (info.suffix() == "nzb" || info.suffix() == "torrent")
        mPathFromArgs = path;
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

void DLMainWindow::suspendAll()
{

    mView->suspendAll();



}

void DLMainWindow::revivalAll()
{

    mView->revivalAll();



}

void DLMainWindow::addPathFromArgs()
{
    fbx()->download()->requestAddFile(mPathFromArgs);
}
