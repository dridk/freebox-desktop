#include "dlmodel.h"

DLModel::DLModel(FbxAPI *fbx, QObject *parent):
    QAbstractTableModel(parent)
{
    mFbx = fbx;
    mTimer = new QTimer();
    connect(mFbx->download(),SIGNAL(listReceived(QList<DownloadTask>)),this,SLOT(setData(QList<DownloadTask>)));

    mTimer->setInterval(1000);
    connect(mTimer,SIGNAL(timeout()),mFbx->download(),SLOT(requestList()));

    mDatas.append(DownloadTask());

}

int DLModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int DLModel::columnCount(const QModelIndex &parent) const
{
    return 10;
}

QVariant DLModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        DownloadTask task = mDatas.at(index.row());
        switch (index.column())
        {

        case 0 : return task.id; break;
        case 1 : return task.status; break;
        case 2 : return task.name; break;
        case 3 : return task.size; break;
        case 4 : return task.rxPct; break;
        case 5 : return task.eta; break;
        case 6 : return task.rxRate; break;
        case 7 : return task.txRate; break;
        case 8 : return QVariantList()<<task.rxBytes<<task.txBytes<<task.stopRatio; break;
        case 9 : return task.createdTs.toString(); break;


        }




    }

    return QVariant();
}

QVariant DLModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();

}

void DLModel::setData(const QList<DownloadTask> &data)
{
    if (data.isEmpty())
        return;

    if (data.count() != mDatas.count())
    {
        beginResetModel();
        mDatas = data;
        endResetModel();
    }

    else {
     mDatas = data;
     emit dataChanged(index(0,0), index(data.count()-1, columnCount()-1));

    }










}
