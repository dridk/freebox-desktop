#include "filesystem.h"

FileSystem::FileSystem(MaFreeBox *parent) :
    QObject(parent)
{

}

void FileSystem::requestList(const QString &path)
{
    QNetworkReply * reply =
            fbx()->get(fbx()->createRequest(QString("fs/ls/%1").arg(path)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void FileSystem::requestInfo(const QString &path)
{
    QNetworkReply * reply =
            fbx()->get(fbx()->createRequest(QString("fs/info/%1").arg(path)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestInfoFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void FileSystem::requestMove(const QStringList &paths, const QString &dest, FileSystem::ConflictMode mode)
{
    QNetworkRequest request = fbx()->createRequest(QString("fs/mv/"));

    QString textMode = QString(metaObject()->enumerator(mode).valueToKey(mode));
    textMode = textMode.toLower().remove("mode");

    QJsonObject json;
    json.insert("files", QJsonArray::fromStringList(paths));
    json.insert("dst",dest);
    json.insert("mode",textMode);

    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->post(request, doc.toJson());

    qDebug()<<doc.toJson();
    connect(reply,SIGNAL(finished()),this,SLOT(requestMoveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void FileSystem::requestCopy(const QStringList &paths, const QString &dest, FileSystem::ConflictMode mode)
{
}

void FileSystem::requestRemove(const QStringList &paths)
{
}

void FileSystem::requestArchive(const QStringList &paths, const QString &dest)
{
}

void FileSystem::requestExtract(const QString &source, const QString &dest, const QString &password, bool deleteAfter, bool overwrite)
{
}

void FileSystem::requestMkdir(const QString &path, const QString &dirName)
{
}

void FileSystem::requestRename(const QString &source, const QString &newName)
{
}

void FileSystem::requestDownload(const QString &path)
{
}

void FileSystem::requestUpload(const QString &file, const QString &destPath)
{
}

void FileSystem::requestUploadList()
{
}

void FileSystem::requestUploadInfo(int id)
{
}

void FileSystem::requestRemoveUpload(int id)
{
}

void FileSystem::requestCleanUploads()
{
}


void FileSystem::requestListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if (fbx()->parseResult(doc))
    {

        QJsonArray array = doc.object().value("result").toArray();
        QList<FileInfo> list;
        foreach (QJsonValue item, array)
        {

            FileInfo file;
            file.path = item.toObject().value("path").toString();
            file.fileCount = item.toObject().value("filecount").toDouble();
            file.link = item.toObject().value("link").toBool();
            file.modified =  QDateTime::fromTime_t(item.toObject().value("modification").toDouble());
            file.folderCount = item.toObject().value("foldercount").toDouble();
            file.name = item.toObject().value("name").toString();
            file.index = item.toObject().value("index").toDouble();
            file.mimetype = item.toObject().value("mimetype").toString();
            file.hidden = item.toObject().value("hidden").toBool();
            file.isDir = item.toObject().value("type").toString() == "dir";
            file.size = item.toObject().value("size").toDouble();
            list.append(file);
        }

        emit listReceived(list);

    }




}

void FileSystem::requestInfoFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if (fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result").toObject();
        FileInfo file;
        file.path = item.toObject().value("path").toString();
        file.fileCount = item.toObject().value("filecount").toDouble();
        file.link = item.toObject().value("link").toBool();
        file.modified =  QDateTime::fromTime_t(item.toObject().value("modification").toDouble());
        file.folderCount = item.toObject().value("foldercount").toDouble();
        file.name = item.toObject().value("name").toString();
        file.index = item.toObject().value("index").toDouble();
        file.mimetype = item.toObject().value("mimetype").toString();
        file.hidden = item.toObject().value("hidden").toBool();
        file.isDir = item.toObject().value("type").toString() == "dir";
        file.size = item.toObject().value("size").toDouble();

        qDebug()<<file.name;
        emit infoReceived(file);

    }
}

void FileSystem::requestMoveFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());


    qDebug()<<doc;
    if (fbx()->parseResult(doc))
    {



    }





}

void FileSystem::requestCopyFinished()
{
}

void FileSystem::requestRemoveFinished()
{
}

void FileSystem::requestArchiveFinished()
{
}

void FileSystem::requestExtractFinished()
{
}

void FileSystem::requestMkdirFinished()
{
}

void FileSystem::requestRenameFinished()
{
}

void FileSystem::requestDownloadFinished()
{
}

void FileSystem::requestUploadFinished()
{
}

void FileSystem::requestUploadListFinished()
{
}

void FileSystem::requestUploadInfoFinished()
{
}

void FileSystem::requestRemoveUploadFinished()
{
}

void FileSystem::requestCleanUploadsFinished()
{
}

