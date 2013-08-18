#include "fstaskmodel.h"
#include <QDebug>
FSTaskModel::FSTaskModel(MaFreeBox *fbx, QObject *parent) :
    QAbstractListModel(parent)
{
    mFbx = fbx;
    connect(mFbx->fileSystem(),SIGNAL(taskListReceived(QList<FileTask>)),
            this,SLOT(dataReceived(QList<FileTask>)));
}

int FSTaskModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}


QVariant FSTaskModel::data(const QModelIndex &index, int role) const
{

    if (role == Qt::DisplayRole)
        return mDatas.at(index.row()).progress;

    return QVariant();
}


void FSTaskModel::load()
{
    qDebug()<<"load";
    mFbx->fileSystem()->requestTaskList();

}

void FSTaskModel::dataReceived(const QList<FileTask> &list)
{

    beginResetModel();
    mDatas = list;
    endResetModel();

}
