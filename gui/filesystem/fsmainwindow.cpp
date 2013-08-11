#include "fsmainwindow.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileSystemModel>
#include "authorizemessagebox.h"

FSMainWindow::FSMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{
    mTreeView = new FSTreeView;
    mTableView = new FSTableView;
    mHeaderWidget= new FSPathToolBar;
    mSplitter = new QSplitter(Qt::Horizontal);
    mModel = new FSModel(fbx());
    mFolderModel = new QSortFilterProxyModel;

    mFolderModel->setFilterKeyColumn(0);
    mFolderModel->setFilterRole(FSModel::IsDirRole);
    mFolderModel->setFilterFixedString("true");

    mFolderModel->setSourceModel(mModel);
    mTreeView->setModel(mFolderModel);
    mTableView->setModel(mModel);
    mHeaderWidget->setModel(mModel);

    mTreeView->setAnimated(true);

    mTableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    mTableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    mTableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    mTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableView->verticalHeader()->setDefaultSectionSize(24);
    mTableView->setAlternatingRowColors(true);
    mTableView->verticalHeader()->hide();
    mTreeView->hideColumn(1);
    mTreeView->hideColumn(2);
    mTreeView->hideColumn(3);


    mSplitter->setHandleWidth(4);

    //construction de la ToolBar
    mToolBar = addToolBar("tool");
    //    QAction * mkdirAction =
    mToolBar->addAction(QIcon(":folder.png"),"Nouveau dossier");
    //    QAction * uploadAction =
    mToolBar->addAction(QIcon(":folder_add.png"),"Télécharger ici");
    QAction * refreshAction =
            mToolBar->addAction(QIcon(":arrow_refresh.png"),"Rafraîchir");

    mToolBar->setIconSize(QSize(16,16));
    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);



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


    connect(fbx(),SIGNAL(loginSuccess()),mModel,SLOT(init()));
    connect(mTreeView,SIGNAL(clicked(QModelIndex)),this,SLOT(setRootIndex(QModelIndex)));
    connect(mHeaderWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(setRootIndex(QModelIndex)));






}

FSMainWindow::~FSMainWindow()
{
    delete mTreeView;
    delete mTableView;
    delete mHeaderWidget;
    delete mSplitter;
    delete mToolBar;
    delete mModel;
    delete mFolderModel;

}


void FSMainWindow::refresh()
{
    mTreeView->reset();

}

void FSMainWindow::setRootIndex(const QModelIndex &index)
{
    qDebug()<<sender()->metaObject()->className();
    if (sender()->metaObject()->className() == QString("FSTreeView") )
        mTableView->setRootIndex(mFolderModel->mapToSource(index));

    if (sender()->metaObject()->className() == QString("FSTableView"))
        mTableView->setRootIndex(index);

    if (sender()->metaObject()->className() == QString("FSPathToolBar"))
    {
        mTableView->setRootIndex(mFolderModel->mapToSource(index));
        mTreeView->setCurrentIndex(index);
    }
    mHeaderWidget->setCurrentIndex(index);


    qDebug()<<mModel->columnCount();
//    if (mModel->columnCount() >=3)
//    {

//        mTableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
//        mTableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
//        mTableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
//    }



}




