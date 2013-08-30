#include "fsactiontaskmodel.h"
#include <QDebug>
FSActionTaskModel::FSActionTaskModel(MaFreeBox *fbx, QObject *parent) :
    FSAbstractTaskModel(parent)
{
    mFbx = fbx;
    connect(mFbx->fileSystem(),SIGNAL(taskListReceived(QList<FileTask>)),
            this,SLOT(dataReceived(QList<FileTask>)));
}

int FSActionTaskModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}


QVariant FSActionTaskModel::data(const QModelIndex &index, int role) const
{

    if (role == Qt::DisplayRole)
        return mDatas.at(index.row()).progress;

    return QVariant();
}


void FSActionTaskModel::load()
{
    qDebug()<<"load";
    mFbx->fileSystem()->requestTaskList();

}

void FSActionTaskModel::dataReceived(const QList<FileTask> &list)
{

    beginResetModel();
    mDatas = list;
    endResetModel();

}
