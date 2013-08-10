#include "stdmodel.h"
#include <QDebug>
#include <QStandardItem>
StdModel::StdModel(MaFreeBox *fbx, QObject *parent) :
    QStandardItemModel(parent)
{
    mFbx = fbx;

}

bool StdModel::canFetchMore(const QModelIndex &parent) const
{
    qDebug()<<"can fetchmore";
    int t = parent.data(Qt::UserRole+1).toInt();
    if (t > 0 && itemFromIndex(parent)->rowCount() == 0)
        return true;

    return QStandardItemModel::canFetchMore(parent);
}

void StdModel::fetchMore(const QModelIndex &parent)
{
    qDebug()<<"fetch more";
    QString path = parent.data(Qt::UserRole+2).toString();

    if (itemFromIndex(parent)->rowCount()>0)
        return ;

    mCurrentIndex = parent;
    mFbx->fileSystem()->requestList(path,false,true,true);

}

bool StdModel::hasChildren(const QModelIndex &parent) const
{
    int t = parent.data(Qt::UserRole+1).toInt();
    if (t > 0)
        return true;

   else
        return QStandardItemModel::hasChildren(parent);


}

void StdModel::init()
{
    qDebug()<<"init";
    mCurrentIndex = QModelIndex();
    mFbx->fileSystem()->requestList(QString(),false,true,true);
    connect(mFbx->fileSystem(),SIGNAL(listReceived(QList<FileInfo>)),
            this,SLOT(load(QList<FileInfo>)));
}

void StdModel::load(const QList<FileInfo> &list)
{

    foreach (FileInfo i, list)
    {
        qDebug()<<i.name;
        QStandardItem * item  = new QStandardItem;
        item->setText(i.name);
        item->setData(i.folderCount + i.fileCount);
        item->setData(i.path, Qt::UserRole+2);
        if(!mCurrentIndex.isValid())
            appendRow(item);
        else
            itemFromIndex(mCurrentIndex)->appendRow(item);

    }



}
