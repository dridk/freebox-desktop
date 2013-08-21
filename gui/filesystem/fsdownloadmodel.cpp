#include "fsdownloadmodel.h"

FSDownloadModel::FSDownloadModel(MaFreeBox *fbx, QObject *parent):
    QAbstractListModel(parent)
{
    mFbx = fbx;
    connect(mFbx->fileSystem(),SIGNAL(downloadStarted(QNetworkReply*)),
            this,SLOT(add(QNetworkReply*)));

    connect(mFbx->fileSystem(),SIGNAL(downloadEnded(QNetworkReply*)),
            this,SLOT(rem(QNetworkReply*)));

    FSDownloadItem item;
    item.bytes = 43;
    item.total = 132;
    item.progress = 55;
    item.speed = 4.3;

    QNetworkReply* a;
    QNetworkReply* b;
    mDatas.insert(a, item);
    mDatas.insert(b, item);

}

int FSDownloadModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

QVariant FSDownloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant();
}

int FSDownloadModel::count() const
{
    return rowCount();
}

const FSDownloadItem &FSDownloadModel::item(const QModelIndex &index)
{
    return mDatas.values()[index.row()];
}

Qt::ItemFlags FSDownloadModel::flags(const QModelIndex &index) const
{

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

void FSDownloadModel::add(QNetworkReply *reply)
{
    beginInsertRows(QModelIndex(),0,0);
    FSDownloadItem item;
    item.reply = reply;
    qDebug()<<"add download "<<reply;

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
            emit dataChanged(index(row),index(row));





    }



}
