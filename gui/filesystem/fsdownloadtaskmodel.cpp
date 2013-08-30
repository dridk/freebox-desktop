#include "fsdownloadtaskmodel.h"
#include <QMimeDatabase>
FSDownloadTaskModel::FSDownloadTaskModel(MaFreeBox *fbx, QObject *parent):
    FSAbstractTaskModel(parent)
{
    mFbx = fbx;
    connect(mFbx->fileSystem(),SIGNAL(downloadStarted(QNetworkReply*)),
            this,SLOT(add(QNetworkReply*)));

//    connect(mFbx->fileSystem(),SIGNAL(downloadEnded(QNetworkReply*)),
//            this,SLOT(rem(QNetworkReply*)));

}

int FSDownloadTaskModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

QVariant FSDownloadTaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role ==TitleRole)
        return mDatas.values().at(index.row()).title;

    if (role == Qt::WhatsThisRole || role ==SubTitleRole)
        return mDatas.values().at(index.row()).subTitle;

    if (role == ProgressRole || role ==Qt::UserRole)
        return mDatas.values().at(index.row()).progress;

    if (role == Qt::DecorationRole || role ==MimeIconRole)
        return mDatas.values().at(index.row()).mimeIconPath;

//    if (role == Qt::StatusTipRole)
//        return mDatas.values().at(index.row()).actionIconPath;

    return QVariant();
}

int FSDownloadTaskModel::count() const
{
    return rowCount();
}

const FSDownloadItem &FSDownloadTaskModel::item(const QModelIndex &index)
{
    return mDatas.values()[index.row()];
}

Qt::ItemFlags FSDownloadTaskModel::flags(const QModelIndex &index) const
{

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

void FSDownloadTaskModel::add(QNetworkReply *reply)
{
    beginInsertRows(QModelIndex(),0,0);
    FSDownloadItem item;
    item.reply = reply;
    item.time.start();
    //récupere le nom du fichier a partir de l'URL encodé en base64
    QByteArray encodedName = reply->url().toString().split("/").last().toUtf8();
    QString decodedName    = QString::fromUtf8(QByteArray::fromBase64(encodedName));
    QMimeType mime = mMimeDb.mimeTypeForUrl(decodedName);
    //récupere l'icone.
    QString icon = mime.iconName().replace("-","_").replace("/","_");
    item.mimeIconPath = QString(":mime/%1.png").arg(icon);
    item.title = decodedName;

    mDatas.insert(reply, item);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
    endInsertRows();
    emit countChanged();
}

void FSDownloadTaskModel::rem(QNetworkReply *reply)
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

void FSDownloadTaskModel::clearFinished()
{
    foreach ( QNetworkReply * reply, mDatas.keys())
    {
        if (mDatas.contains(reply))
        {
            if (mDatas[reply].progress == 100)
             rem(reply);
        }
    }
}

void FSDownloadTaskModel::removeTask(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    QNetworkReply* reply = mDatas.values().at(index.row()).reply;
    rem(reply);
    if (reply)
        reply->abort();



}
void FSDownloadTaskModel::downloadProgress(qint64 bytes, qint64 total)
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    if (reply && mDatas.contains(reply))
    {
        // calcul de la progress Bar
        mDatas[reply].progress = double(bytes) / double(total) * 100;

        qDebug()<<"progress..."<<mDatas[reply].progress;


        if (mDatas[reply].progress < 100)
        {
        //calcul de la vitesse
        int elapsed = mDatas[reply].time.elapsed();
        mDatas[reply].time.restart();
        int diff = bytes - mDatas[reply].bytes;
        double speed = double(diff) / double(elapsed) ;
        mDatas[reply].bytes    = bytes;

        // calcul du temps restant
        double remain = (int(total) - int(bytes)) / int(speed);
        QTime remainTime = QTime(0,0,0);
        remainTime = remainTime.addSecs(qRound(remain/1000));

        // definition du  subtitle
        mDatas[reply].subTitle = QString("%1 sur %2 à :%3/sec - %4 restante")
                .arg(FSModel::sizeHuman(bytes))
                .arg(FSModel::sizeHuman(total))
                .arg(FSModel::sizeHuman(speed))
                .arg(remainTime.toString("hh:mm"));

        }

        else
        {
            mDatas[reply].subTitle = QString("%1 terminé à %2")
                    .arg(FSModel::sizeHuman(total))
                    .arg(QDateTime::currentDateTime().toString());
        }

        int row = mDatas.keys().indexOf(reply);
        if (row > -1)
            emit dataChanged(index(row),index(row));

    }
}
