#include "fsmainwindow.h"
#include <QMessageBox>
FSMainWindow::FSMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mFbx = new MaFreeBox;
    mTreeView = new QTreeView;
    mTableView = new QTableView;
    mHeaderWidget= new HeaderPathWidget;
    mSplitter = new QSplitter(Qt::Horizontal);
    mModel = new FileSystemModel(mFbx);

    mSplitter->setHandleWidth(4);

    mTableView->setModel(mModel);
    mTreeView->setModel(mModel);

    qDebug()<<mModel->rowCount();

    mTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    mTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    mTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
    mTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    mTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);


    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableView->verticalHeader()->setDefaultSectionSize(24);
    mTableView->setAlternatingRowColors(true);
    mTableView->verticalHeader()->hide();

    mTreeView->hideColumn(1);
    mTreeView->hideColumn(2);
    mTreeView->hideColumn(3);




    //    setStyleSheet("QMainWindow{background:#3a3a3a;}");

    mToolBar = addToolBar("tool");

    QMenu * fileMenu  = new QMenu("File",this);
    QAction * login = fileMenu->addAction("Connexion");
    menuBar()->addMenu(fileMenu);


    connect(login,SIGNAL(triggered()),this,SLOT(login()));
    //    connect(mFbx,SIGNAL(error(QString,Error)), this,SLOT(showError()));
    connect(mFbx,SIGNAL(loginSuccess()),mModel,SLOT(fetchMore()));
    connect(mTreeView,SIGNAL(clicked(QModelIndex)),mTableView,SLOT(setRootIndex(QModelIndex)));


    //   mToolBar->setStyleSheet("QToolBar{background:#3a3a3a;}");
    //   mToolBar->setStyleSheet("*{color:white; font-weight:bold; font-size: 12px }");

    mToolBar->setIconSize(QSize(16,16));
    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QAction * mkdirAction = mToolBar->addAction(QIcon(":folder.png"),"Nouveau dosser");
    QAction * uploadAction = mToolBar->addAction(QIcon(":folder_add.png"),"Uploader ici");
    QAction * refreshAction = mToolBar->addAction(QIcon(":arrow_refresh.png"),"Rafraîchir");


    mHeaderWidget->addButton("C:", "");
    mHeaderWidget->addButton("Disque Dur", "");
    mHeaderWidget->addButton("Vidéo", "");



    QVBoxLayout * centerLayout = new QVBoxLayout;
    centerLayout->addWidget(mHeaderWidget);
    centerLayout->addWidget(mTableView);
    centerLayout->setContentsMargins(0,0,0,0);

    QWidget * centerWidget = new QWidget;
    centerWidget->setLayout(centerLayout);

    mSplitter->addWidget(mTreeView);
    mSplitter->addWidget(centerWidget);

    setCentralWidget(mSplitter);



}

void FSMainWindow::login()
{

    //Attention.. ca marchera pas chez vous... Vous devez authorizer l'app
    //faite un requestAuth pour récuperé l'app token et faite :
    //mFbx->setApplicationToken(token);


    mFbx->setApplicationId("fr.freebox.testapp2");
    mFbx->requestLogin();




}

void FSMainWindow::showError()
{
    QMessageBox::critical(this,"freebox error", mFbx->errorString());
}




