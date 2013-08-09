#include "fsmainwindow.h"
#include <QMessageBox>
#include <QCoreApplication>
#include "modeltest.h"
#include "authorizemessagebox.h"
FSMainWindow::FSMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mFbx = new MaFreeBox;
    mTreeView = new QTreeView;
    mTableView = new QTableView;
    mHeaderWidget= new HeaderPathWidget;
    mSplitter = new QSplitter(Qt::Horizontal);
    mModel = new FileSystemModel(mFbx);
    mFolderModel = new FolderFilterProxyModel;


 mFolderModel->setSourceModel(mModel);

    mSplitter->setHandleWidth(4);

    //Construction des Views
    mTableView->setModel(mModel);
  // mTreeView->setModel(mFolderModel);
    //    mTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //    mTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //    mTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
    //    mTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    //    mTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    mTableView->verticalHeader()->setDefaultSectionSize(24);
    //    mTableView->setAlternatingRowColors(true);
    //    mTableView->verticalHeader()->hide();
    //    mTreeView->hideColumn(1);
    //    mTreeView->hideColumn(2);
    //    mTreeView->hideColumn(3);


    //construction du window Menu
    QMenu * fileMenu  = new QMenu("File",this);
    QAction * authAction = fileMenu->addAction("Authoriser l'application");
    QAction * loginAction = fileMenu->addAction("Connexion");
    menuBar()->addMenu(fileMenu);

    //construction de la ToolBar
    mToolBar = addToolBar("tool");
//    QAction * mkdirAction =
    mToolBar->addAction(QIcon(":folder.png"),"Nouveau dossier");
//    QAction * uploadAction =
    mToolBar->addAction(QIcon(":folder_add.png"),"Télécharger ici");
//    QAction * refreshAction =
    mToolBar->addAction(QIcon(":arrow_refresh.png"),"Rafraîchir");

    mToolBar->setIconSize(QSize(16,16));
    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mHeaderWidget->addButton("C:", "");
    mHeaderWidget->addButton("Disque Dur", "");
    mHeaderWidget->addButton("Vidéo", "");


    //construction de l'ensemble
    QVBoxLayout * centerLayout = new QVBoxLayout;
    centerLayout->addWidget(mHeaderWidget);
    centerLayout->addWidget(mTableView);
    centerLayout->setContentsMargins(0,0,0,0);

    QWidget * centerWidget = new QWidget;
    centerWidget->setLayout(centerLayout);

    mSplitter->addWidget(mTreeView);
    mSplitter->addWidget(centerWidget);
    setCentralWidget(mSplitter);

    //connection

    connect(loginAction,SIGNAL(triggered()),this,SLOT(login()));
    connect(authAction,SIGNAL(triggered()),this,SLOT(authorize()));
    connect(mFbx,SIGNAL(error(QString,QString)), this,SLOT(showError()));
    connect(mFbx,SIGNAL(loginSuccess()),mModel,SLOT(fetchMore()));
    connect(mFbx,SIGNAL(authorizeReceived(QString,int)),this,SLOT(authorizeReceived(QString,int)));
    connect(mTreeView,SIGNAL(clicked(QModelIndex)),mTableView,SLOT(setRootIndex(QModelIndex)));

    connect(mTableView,SIGNAL(doubleClicked(QModelIndex)),mTableView,SLOT(setRootIndex(QModelIndex)));

    connect(mTableView,SIGNAL(clicked(QModelIndex)),mModel,SLOT(fetchMore()));


//  new ModelTest(mModel, this);
}

void FSMainWindow::login()
{
    qDebug()<<qApp->applicationName();
    mFbx->setApplicationId("org.labsquare" + qApp->applicationName());
    mFbx->requestLogin();
}

void FSMainWindow::showError()
{
    QMessageBox::critical(this,mFbx->errorCode(), mFbx->errorString());
}

void FSMainWindow::authorize()
{
    QString appId = "org.labsquare" + qApp->applicationName();
    mFbx->requestAuthorize(appId, qApp->applicationName(), qApp->applicationVersion(), "Desktop");

}

void FSMainWindow::test()
{
}

void FSMainWindow::authorizeReceived(const QString &token, int trackId)
{

    AuthorizeMessageBox * box = new AuthorizeMessageBox(mFbx, this);
    box->setTrackId(trackId);

    if (box->exec() == QDialog::Accepted)
    {
        mFbx->setApplicationToken(token);
        mFbx->saveApplicationToken();
        login();
    }

    else
    {
        QMessageBox::warning(this,"Authorisation", "Authorisation refusé");
    }

}





