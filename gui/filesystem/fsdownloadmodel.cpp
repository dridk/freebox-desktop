#include "fsdownloadmodel.h"

FSDownloadModel::FSDownloadModel(MaFreeBox *fbx, QObject *parent):
    QAbstractTableModel(parent)
{
    mFbx = fbx;
    connect(mFbx->fileSystem(),SIGNAL(downloadStarted(QNetworkReply*)),
            this,SLOT(add(QNetworkReply*)));

    connect(mFbx->fileSystem(),SIGNAL(downloadEnded(QNetworkReply*)),
            this,SLOT(rem(QNetworkReply*)));
}

int FSDownloadModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int FSDownloadModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FSDownloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    FSDownloadItem item = mDatas.values().at(index.row());

    if (!item.reply)
        return QVariant();


    if (role == Qt::DisplayRole && index.column() == 0)
        return item.filename;

    if (role == Qt::DisplayRole && index.column() == 1)
        return item.progress;

    return QVariant();
}

int FSDownloadModel::count() const
{
    return rowCount();
}

void FSDownloadModel::add(QNetworkReply *reply)
{
    beginInsertRows(QModelIndex(),0,0);
    FSDownloadItem item;
    item.reply = reply;

    mDatas.insert(reply, item);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),
            this,SLOT(downloadProgress(qint64,qint64)));
    endInsertRows();
    emit countChanged();
}

void FSDownloadModel::rem(QNetworkReply *reply)
{
    if (mDatas.contains(reply))
    {
        int row = mDatas.keys().indexOf(reply);
        beginRemoveRows(QModelIndex(),row,row);
        mDatas.remove(reply);
        endRemoveRows();
        emit countChanged();
    }

}

void FSDownloadModel::downloadProgress(qint64 bytes, qint64 total)
{

    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    if (reply && mDatas.contains(reply))
    {
        mDatas[reply].bytes    = bytes;
        mDatas[reply].total    = total;
        mDatas[reply].progress = double(bytes) / double(total) * 100;

        QString rawName = reply->rawHeader("Content-disposition");
        rawName.remove("attachment; filename=");
        rawName.chop(1); // remove last quote
        rawName.remove(0,1); // remove first quote
        mDatas[reply].filename = rawName;

        int row = mDatas.keys().indexOf(reply);
        if (row > -1)
            emit dataChanged(index(row,0), index(row,columnCount()-1));





    }



}
