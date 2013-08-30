#include "fsuploadtaskmodel.h"
#include "fsmodel.h"
FSUploadTaskModel::FSUploadTaskModel(MaFreeBox *fbx, QObject *parent) :
    FSAbstractTaskModel(parent)
{
    mFbx = fbx;
    connect(mFbx->fileSystem(),SIGNAL(uploadStarted(QNetworkReply*)),this,SLOT(add(QNetworkReply*)));
}

int FSUploadTaskModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}
void FSUploadTaskModel::add(QNetworkReply *reply)
{
    qDebug()<<"ADD upload";
    beginInsertRows(QModelIndex(),0,0);
    FSUploadItem item;
    item.reply = reply;
    item.time.start();
    item.title = reply->objectName();

    mDatas.insert(reply, item);
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));
    endInsertRows();
    emit countChanged();
}

void FSUploadTaskModel::rem(QNetworkReply *reply)
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

void FSUploadTaskModel::clearFinished()
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

void FSUploadTaskModel::removeTask(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    QNetworkReply* reply = mDatas.values().at(index.row()).reply;
    rem(reply);
    if (reply)
        reply->abort();
}

int FSUploadTaskModel::count()
{
    int c = 0;
    foreach (FSUploadItem item, mDatas.values()){
        if (item.progress < 100)
            c++;
    }

    return c;
}

void FSUploadTaskModel::uploadProgress(qint64 bytes, qint64 total)
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    if (reply && mDatas.contains(reply))
    {
        // evite division par 0
        if (total == 0 )
         mDatas[reply].progress = 100;
        else
        mDatas[reply].progress = double(bytes) / double(total) * 100;

        qDebug()<<mDatas[reply].progress;

        // Affichage qd ca telecharge...
        if (mDatas[reply].progress <100)
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

        // affichage du mode fini...
        else
        {
            mDatas[reply].subTitle = QString("%1 terminé à %2")
                    .arg(FSModel::sizeHuman(total))
                    .arg(QDateTime::currentDateTime().toString());
            emit countChanged();
        }

        int row = mDatas.keys().indexOf(reply);
        if (row > -1)
            emit dataChanged(index(row),index(row));

    }


}
QVariant FSUploadTaskModel::data(const QModelIndex &index, int role) const
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


    return QVariant();
}
