#include "dltableview.h"
#include <QDebug>
#include <QActionGroup>
#include <QHeaderView>
DLTableView::DLTableView(FbxAPI *fbx, QWidget *parent) :
    QTableView(parent)
{
    mFbx = fbx;
    mModel = new DLModel(fbx);
    mFilterModel = new QSortFilterProxyModel;
    mDelegate = new DLDelegate;
    mPropertyWidget = new DLPropertyWidget;
    mPropertyWidget->setModel(mModel);
    mFilterModel->setSourceModel(mModel);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setModel(mFilterModel);
    setItemDelegate(mDelegate);
    verticalHeader()->setDefaultSectionSize(30);
    setColumnWidth(2, 250);
    setColumnWidth(4, 200);
    hideColumn(10);

    mFilterModel->setFilterKeyColumn(10);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    horizontalHeader()->setSectionsMovable(true); // ATTENTION QT5 ONLY
    horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(2,QHeaderView::Interactive);
    horizontalHeader()->setSectionResizeMode(9,QHeaderView::Stretch);
    setAlternatingRowColors(true);


    setAcceptDrops(true);



}

void DLTableView::dragEnterEvent(QDragEnterEvent *event)
{
    bool accept = false;
    if (event->mimeData()->hasUrls()) {
        foreach ( QUrl url, event->mimeData()->urls())
        {
            QFileInfo info(url.toString());
            if (info.suffix() == "torrent") {
                mDropUrls.append(url.toString());
                accept  = true;

            }
        }
    }

    if (accept)
        qDebug()<<"enter";
    event->acceptProposedAction();


}

void DLTableView::dragMoveEvent(QDragMoveEvent * event)
{
    qDebug()<<"move";
    event->acceptProposedAction();
}

void DLTableView::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event)

}

void DLTableView::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event)



}

void DLTableView::contextMenuEvent(QContextMenuEvent * event)
{
    if (selectionModel()->selectedRows().isEmpty())
        return;


    QMenu menu;
    QFont font;font.setBold(true);
    menu.addAction(QIcon(),"Propriétés",this,SLOT(showPropertyDialog()))->setFont(font);
    menu.addSeparator();
    menu.addAction(QIcon(),"Reprendre",this,SLOT(setCurrentRestart()));
    menu.addAction(QIcon(),"Réessayer",this,SLOT(setCurrentRetry()));
    menu.addAction(QIcon(),"Pause",this,SLOT(setCurrentPause()));
    QAction * supprAction = menu.addAction(QIcon(),"Supprimer");
    QMenu supprMenu;
    supprMenu.addAction(QIcon(),"En conservant les fichiers",this,SLOT(setCurrentRemove()));
    supprMenu.addAction(QIcon(),"En effacant les fichiers",this,SLOT(setCurrentErase()));
    supprAction->setMenu(&supprMenu);
    menu.addAction(supprAction);
    menu.addSeparator();

    QAction * priorAction = menu.addAction(QIcon(),"Changer la priorité réseau");
    QMenu priorMenu;

    QActionGroup priorityGroup(this);
    QAction *a = priorityGroup.addAction(QIcon(),"Haute");
    QAction *b = priorityGroup.addAction(QIcon(),"Normale");
    QAction *c = priorityGroup.addAction(QIcon(),"Faible");

    a->setCheckable(true);
    b->setCheckable(true);
    c->setCheckable(true);

    connect(a,SIGNAL(triggered()),this,SLOT(setCurrentPriorityHigh()));
    connect(b,SIGNAL(triggered()),this,SLOT(setCurrentPriorityNormal()));
    connect(c,SIGNAL(triggered()),this,SLOT(setCurrentPriorityLow()));


    QModelIndex firstIndex = selectionModel()->selectedRows(5).first();
    qDebug()<<firstIndex.data().toString();
    if (firstIndex.data().toString() == "high")
        a->setChecked(true);
    if (firstIndex.data().toString() == "normal")
        b->setChecked(true);
    if (firstIndex.data().toString() == "low")
        c->setChecked(true);


    priorMenu.addActions(priorityGroup.actions());

    priorAction->setMenu(&priorMenu);
    menu.addAction(priorAction);


    menu.move(event->globalPos());
    menu.exec();

}

void DLTableView::showPropertyDialog()
{


    qDebug()<<"set data";
    mPropertyWidget->setModel(mModel);
    mPropertyWidget->setCurrentIndex(mFilterModel->mapToSource(currentIndex()));
    mPropertyWidget->show();



}

void DLTableView::setStatusFilter(const QString &status)
{
    mFilterModel->setFilterFixedString(status);
}

void DLTableView::setAutoUpdate(bool enable)
{


}

void DLTableView::suspendAll()
{
    qDebug()<<"suspendAll();";
    QList<DownloadTask> tasks;
    for (int row=0; row<mFilterModel->sourceModel()->rowCount(); row++)
    {
        DLModel * dlModel = qobject_cast<DLModel*>(mFilterModel->sourceModel());
        DownloadTask task = dlModel->downloadTask(row);
        tasks.append(task);

    }

    foreach (DownloadTask task, tasks)
        mFbx->download()->requestUpdate(task.id,task.ioPriority,"stopped");

}

void DLTableView::revivalAll()
{
    qDebug()<<"revivalALl();";
    QList<DownloadTask> tasks;
    for (int row=0; row<mFilterModel->sourceModel()->rowCount(); row++)
    {
        DLModel * dlModel = qobject_cast<DLModel*>(mFilterModel->sourceModel());
        DownloadTask task = dlModel->downloadTask(row);
        tasks.append(task);

    }

    foreach (DownloadTask task, tasks)
        mFbx->download()->requestUpdate(task.id,task.ioPriority,"downloading");

}

void DLTableView::setPropertyDialog()
{




}

void DLTableView::setCurrentPause()
{
    if (currentIndex().isValid())
    {
        QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
        int id = mModel->index(mIndex.row(),0).data().toInt();
        QString priority = mModel->index(mIndex.row(),5).data().toString();
        mFbx->download()->requestUpdate(id,priority,"stopped");
    }
}

void DLTableView::setCurrentRestart()
{
    if (currentIndex().isValid())
    {
        QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
        int id = mModel->index(mIndex.row(),0).data().toInt();
        QString priority = mModel->index(mIndex.row(),5).data().toString();
        mFbx->download()->requestUpdate(id,priority,"downloading");
    }
}

void DLTableView::setCurrentRetry()
{
    if (currentIndex().isValid())
    {
        QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
        int id = mModel->index(mIndex.row(),0).data().toInt();
        QString priority = mModel->index(mIndex.row(),5).data().toString();
        mFbx->download()->requestUpdate(id,priority,"retry");
    }
}

void DLTableView::setCurrentRemove()
{
    if (currentIndex().isValid())
    {
        QMessageBox box;
        box.setWindowTitle("Suppression");
        box.setText("Voulez-vous supprimer cette tâche (en conservant le fichier)");
        box.setIcon(QMessageBox::Question);
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        if (box.exec() == QMessageBox::Yes) {
            QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
            int id = mModel->index(mIndex.row(),0).data().toInt();
            mFbx->download()->requestErase(id);
        }
    }
}

void DLTableView::setCurrentErase()
{
    if (currentIndex().isValid())
    {

        QMessageBox box;
        box.setWindowTitle("Suppression");
        box.setText("Voulez-vous supprimer cette tâche (en effaçant les fichiers)");
        box.setIcon(QMessageBox::Question);
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        if (box.exec() == QMessageBox::Yes) {
            QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
            int id = mModel->index(mIndex.row(),0).data().toInt();
            mFbx->download()->requestErase(id);
        }
    }

}

void DLTableView::setCurrentPriorityLow()
{
    if (currentIndex().isValid())
    {
        QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
        int id = mModel->index(mIndex.row(),0).data().toInt();
        QString status = mModel->index(mIndex.row(),10).data().toString();
        mFbx->download()->requestUpdate(id,"low",status);
    }
}

void DLTableView::setCurrentPriorityNormal()
{
    if (currentIndex().isValid())
    {
        QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
        int id = mModel->index(mIndex.row(),0).data().toInt();
        QString status = mModel->index(mIndex.row(),10).data().toString();
        mFbx->download()->requestUpdate(id,"normal",status);
    }
}

void DLTableView::setCurrentPriorityHigh()
{
    if (currentIndex().isValid())
    {
        QModelIndex mIndex = mFilterModel->mapToSource(currentIndex());
        int id = mModel->index(mIndex.row(),0).data().toInt();
        QString status = mModel->index(mIndex.row(),10).data().toString();
        mFbx->download()->requestUpdate(id,"high",status);
    }
}


