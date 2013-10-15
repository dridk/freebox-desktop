#include "clmodel.h"

CLModel::CLModel(FbxAPI *fbx, QObject *parent) :
    QAbstractTableModel(parent)
{
    mFbx = fbx;
    connect(mFbx->call(),SIGNAL(listReceived(QList<CallEntry>)),
            this,SLOT(load(QList<CallEntry>)));
}

int CLModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int CLModel::columnCount(const QModelIndex &parent) const
{
    return 2;

}

QVariant CLModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole )
    {

        if (index.column() == 0)
            return mDatas[index.row()].name;

        if (index.column() == 1)
            return mDatas[index.row()].datetime;

    }


    return QVariant();

}


void CLModel::refresh()
{
    mDatas.clear();
    mFbx->call()->requestList();

}

void CLModel::load(const QList<CallEntry> &list)
{
    beginResetModel();
    mDatas = list;
    endResetModel();
}
