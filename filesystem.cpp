#include "filesystem.h"
FileSystem::FileSystem(MaFreeBox *parent) :
    QObject(parent)
{

}

FileSystem::~FileSystem()
{
    foreach ( QFile * file, mDownloads.values()){
        file->remove();
    }

    mDownloads.clear();
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
    QNetworkRequest request = fbx()->createRequest(QString("fs/cp/"));

    QString textMode = QString(metaObject()->enumerator(mode).valueToKey(mode));
    textMode = textMode.toLower().remove("mode");

    QJsonObject json;
    json.insert("files", QJsonArray::fromStringList(paths));
    json.insert("dst",dest);
    json.insert("mode",textMode);

    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->post(request, doc.toJson());

    connect(reply,SIGNAL(finished()),this,SLOT(requestCopyFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void FileSystem::requestRemove(const QStringList &paths)
{
    QNetworkRequest request = fbx()->createRequest(QString("fs/rm/"));
    QJsonObject json;
    json.insert("files", QJsonArray::fromStringList(paths));
    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestRemoveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void FileSystem::requestArchive(const QStringList &paths, const QString &dest)
{
    QNetworkRequest request = fbx()->createRequest(QString("fs/archive/"));

    QJsonObject json;
    json.insert("files", QJsonArray::fromStringList(paths));
    json.insert("dst",dest);
    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestArchiveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void FileSystem::requestExtract(const QString &source, const QString &dest, const QString &password, bool deleteArchive, bool overwrite)
{
    QNetworkRequest request = fbx()->createRequest(QString("fs/extract/"));

    QJsonObject json;
    json.insert("src", source);
    json.insert("dst",dest);
    json.insert("password",password);
    json.insert("delete_archive",deleteArchive);
    json.insert("overwrite",overwrite);


    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestExtractFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystem::requestMkdir(const QString &path, const QString &dirName)
{
    QNetworkRequest request = fbx()->createRequest(QString("fs/mkdir/"));

    QJsonObject json;
    json.insert("parent", path);
    json.insert("dirname",dirName);

    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestMkdirFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystem::requestRename(const QString &source, const QString &newName)
{
    QNetworkRequest request = fbx()->createRequest(QString("fs/rename/"));

    QJsonObject json;
    json.insert("src", source);
    json.insert("dst",newName);

    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestRenameFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystem::requestDownload(const QString &path, const QString &localPath)
{
    QNetworkRequest request = fbx()->createRequest(QString("dl/%1").arg(path));

    QFile * file = new QFile(QDir::fromNativeSeparators(localPath +
                                                        QDir::separator() +
                                                         path));
    if (!file->open(QIODevice::WriteOnly))
    {
        qDebug()<<"cannot open file "<<file->fileName();
        delete file;
        return;
    }

    QNetworkReply * reply = fbx()->get(request);
    mDownloads.insert(reply, file);

    connect(reply,SIGNAL(readyRead()),this,SLOT(requestDownloadReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(requestDownloadFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


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
    if(fbx()->parseResult(doc))
        emit moveFinished();
}

void FileSystem::requestCopyFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit copyFinished();
}

void FileSystem::requestRemoveFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit removeFinished();
}

void FileSystem::requestArchiveFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit archiveFinished();
}

void FileSystem::requestExtractFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit extractFinished();
}

void FileSystem::requestMkdirFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit mkdirFinished();
}

void FileSystem::requestRenameFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit renameFinished();

    reply->deleteLater();

}

void FileSystem::requestDownloadFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    if (mDownloads.contains(reply)){
        QString rawName = reply->rawHeader("Content-disposition");
        rawName.remove("attachment; filename=");
        rawName.chop(1); // remove last quote
        rawName.remove(0,1); // remove first quote
        QString fileName = rawName;

        QString completeFileName = QFileInfo(*(mDownloads[reply])).absoluteFilePath();

        mDownloads[reply]->rename(fileName);
        mDownloads[reply]->close();

        delete mDownloads[reply];
        mDownloads.remove(reply);

        emit downloadFinished(completeFileName);
    }
    reply->deleteLater();

}

void FileSystem::requestDownloadReadyRead()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    if (mDownloads.contains(reply)){
        mDownloads[reply]->write(reply->readAll());
    }
    reply->deleteLater();

}

void FileSystem::requestDownloadError()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    if (mDownloads.contains(reply)) {
        mDownloads[reply]->remove();
        delete(mDownloads[reply]);
        mDownloads.remove(reply);
    }

    reply->deleteLater();
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

