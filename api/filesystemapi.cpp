#include "filesystemapi.h"
#include <QIcon>
FileSystemApi::FileSystemApi(FbxAPI *parent) :
    QObject(parent)
{

}

FileSystemApi::~FileSystemApi()
{
    foreach ( QFile * file, mDownloads.values()){
        file->remove();
    }

    mDownloads.clear();
}

QFile *FileSystemApi::downloadFile(QNetworkReply *reply)
{
    return mDownloads.value(reply,NULL);
}

QFile *FileSystemApi::uploadFile(QNetworkReply *reply)
{
    return mUploads.value(reply,NULL);

}

void FileSystemApi::requestList(const QString &path, bool onlyFolder, bool countSubFolder, bool removeHidden)
{

    QStringList param;
    param.append("onlyFolder=" + QString::number(onlyFolder));
    param.append("countSubFolder=" + QString::number(countSubFolder));
    param.append("removeHidden=" + QString::number(removeHidden));


    QNetworkReply * reply =
            fbx()->get(fbx()->myCreateRequest(QString("fs/ls/%1?%2").arg(path).arg(param.join("&"))));

    connect(reply,SIGNAL(finished()),this,SLOT(requestListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void FileSystemApi::requestInfo(const QString &path)
{
    QNetworkReply * reply =
            fbx()->get(fbx()->myCreateRequest(QString("fs/info/%1").arg(path)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestInfoFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void FileSystemApi::requestMove(const QStringList &paths, const QString &dest, FileSystemApi::ConflictMode mode)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/mv/"));

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

void FileSystemApi::requestCopy(const QStringList &paths, const QString &dest, FileSystemApi::ConflictMode mode)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/cp/"));

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

void FileSystemApi::requestRemove(const QStringList &paths)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/rm/"));
    QJsonObject json;
    json.insert("files", QJsonArray::fromStringList(paths));
    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestRemoveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void FileSystemApi::requestArchive(const QStringList &paths, const QString &dest)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/archive/"));

    QJsonObject json;
    json.insert("files", QJsonArray::fromStringList(paths));
    json.insert("dst",dest);
    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestArchiveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void FileSystemApi::requestExtract(const QString &source, const QString &dest, const QString &password, bool deleteArchive, bool overwrite)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/extract/"));

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

void FileSystemApi::requestMkdir(const QString &path, const QString &dirName)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/mkdir/"));

    QJsonObject json;
    json.insert("parent", path);
    json.insert("dirname",dirName);

    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestMkdirFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystemApi::requestRename(const QString &source, const QString &newName)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/rename/"));

    QJsonObject json;
    json.insert("src", source);
    json.insert("dst",newName);

    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestRenameFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystemApi::requestDownload(const QString &path, const QString &localPath)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("dl/%1").arg(path));

    request.setRawHeader(QByteArray("destination"), localPath.toUtf8());

    QFile * file = new QFile(QDir::fromNativeSeparators(localPath +
                                                        QDir::separator() +
                                                        path));

    qDebug()<<QDir::fromNativeSeparators(localPath +
                                         QDir::separator() +
                                         path);
    if (!file->open(QIODevice::WriteOnly))
    {
        qDebug()<<"cannot open file "<<file->fileName();
        delete file;
        return;
    }

    QNetworkReply * reply = fbx()->get(request);
    file->setParent(reply); // delete file when reply is deleted

    mDownloads.insert(reply, file);
    emit downloadStarted(reply);
    connect(reply,SIGNAL(readyRead()),this,SLOT(requestDownloadReadyRead()));
    connect(reply,SIGNAL(finished()),this,SLOT(requestDownloadFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void FileSystemApi::requestUpload(const QString &file, const QString &destPath)
{

    //==== Upload has 2 step request
    // 1: Get ID from uri : 'upload/'
    // 2: send file from uri : 'upload/{id}/post multiPart

    QNetworkRequest request = fbx()->myCreateRequest(QString("upload/"));
    // just write the filename to get it back from response!
    request.setRawHeader(QByteArray("filename"), file.toUtf8());
    QJsonObject json;
    json.insert("dirname",QString(destPath));
    json.insert("upload_name",QString(QFileInfo(file).fileName()));

    QJsonDocument doc(json);
    QNetworkReply * reply = fbx()->post(request, doc.toJson());

    connect(reply,SIGNAL(finished()),this,SLOT(requestStartUpload()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystemApi::requestUploadList()
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("upload/"));

    QNetworkReply * reply = fbx()->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestUploadListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystemApi::requestUploadInfo(int id)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("upload/%1").arg(id));

    QNetworkReply * reply = fbx()->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestUploadInfoFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void FileSystemApi::requestDeleteUpload(int id)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("upload/%1").arg(id));

    QNetworkReply * reply = fbx()->deleteResource(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestDeleteUploadFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}


void FileSystemApi::requestCleanUploads()
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("upload/clean"));

    QNetworkReply * reply = fbx()->deleteResource(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestCleanUploadsFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void FileSystemApi::requestTaskList()
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/tasks/"));
    QNetworkReply * reply = fbx()->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestTaskListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void FileSystemApi::requestTask(int id)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/tasks/%1").arg(id));
    QNetworkReply * reply = fbx()->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestTaskFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void FileSystemApi::requestDeleteTask(int id)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/tasks/%1").arg(id));
    QNetworkReply * reply = fbx()->deleteResource(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestDeleteTaskFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));



}

void FileSystemApi::requestUpdateTask(int id, const QString &state)
{
    QNetworkRequest request = fbx()->myCreateRequest(QString("fs/tasks/%1").arg(id));

    QJsonObject json;
    json.insert("state", state);
    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->put(request,doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateTaskFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void FileSystemApi::requestListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    qDebug()<<"list received";
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

void FileSystemApi::requestInfoFinished()
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

void FileSystemApi::requestMoveFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit moveFinished();
}

void FileSystemApi::requestCopyFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit copyFinished();
}

void FileSystemApi::requestRemoveFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit removeFinished();
}

void FileSystemApi::requestArchiveFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit archiveFinished();
}

void FileSystemApi::requestExtractFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit extractFinished();
}

void FileSystemApi::requestMkdirFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit mkdirFinished();
}

void FileSystemApi::requestRenameFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit renameFinished();

    reply->deleteLater();

}

void FileSystemApi::requestDownloadFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());


    if (mDownloads.contains(reply)){
        QString rawName = reply->rawHeader("Content-disposition");
        rawName.remove("attachment; filename=");
        rawName.chop(1); // remove last quote
        rawName.remove(0,1); // remove first quote
        QString fileName = rawName;
        qDebug()<<"filename"<<fileName;

        QString completeFileName = QFileInfo(*(mDownloads[reply])).absoluteFilePath();

        QFileInfo path(completeFileName);


        mDownloads[reply]->rename(path.absoluteDir().path()+QDir::separator()+fileName);
        mDownloads[reply]->close();

        delete mDownloads[reply];
        mDownloads.remove(reply);
        emit downloadFinished(completeFileName);
        emit downloadEnded(reply);

    }
    reply->deleteLater();

}

void FileSystemApi::requestDownloadReadyRead()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    if (mDownloads.contains(reply)){
        mDownloads[reply]->write(reply->readAll());
    }
}

void FileSystemApi::requestDownloadError()
{
    qDebug()<<"download Error";
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    if (mDownloads.contains(reply)) {
        mDownloads[reply]->remove();
        mDownloads.remove(reply);
    }

    reply->deleteLater();
}

void FileSystemApi::requestUploadFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if (fbx()->parseResult(doc) && mUploads.contains(reply)) {
        mUploads[reply]->close();
        emit uploadFinished(reply->objectName());
        emit uploadEnded(reply);
    }

    reply->deleteLater();

}

void FileSystemApi::requestStartUpload()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        //Get Upload ID and send file
        QString id = doc.object().value("result").toObject().value("id").toVariant().toString();
        QString fileName = reply->request().rawHeader(QByteArray("filename"));

        QFile * file = new QFile(fileName);
        if (!file->open(QIODevice::ReadOnly))
        {
            qDebug()<<"Cannot open file "<<fileName;
            reply->deleteLater();
            return;
        }


        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QNetworkRequest request = fbx()->myCreateRequest(QString("upload/%1/send/").arg(id));
        QHttpPart filePart;
        filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                           mMimeDatabase.mimeTypeForFile(fileName).name());
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QString("form-data; name=\"%1\";filename=\"%1\"")
                           .arg(QFileInfo(fileName).fileName()));

        filePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        multiPart->append(filePart);

        request.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data; boundary=" + multiPart->boundary());

        QNetworkReply *uploadReply = fbx()->post(request, multiPart);
        multiPart->setParent(uploadReply);
        uploadReply->setObjectName(fileName); // save fileName to get it back from response

        mUploads[uploadReply] = file;
        connect(uploadReply,SIGNAL(finished()),this,SLOT(requestUploadFinished()));
        connect(uploadReply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
        emit uploadStarted(uploadReply);

    }
    reply->deleteLater();
}


void FileSystemApi::requestUploadListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        QList<FileUpload> list;

        foreach (QJsonValue item,  doc.object().value("result").toArray())
        {
            FileUpload file;
            file.id = item.toObject().value("id").toString();
            file.size =item.toObject().value("size").toDouble();
            file.uploaded = item.toObject().value("uploaded").toDouble();
            file.status = item.toObject().value("uploaded").toString();
            file.lastUpdate = QDateTime::fromTime_t(item.toObject().value("last_update").toDouble());
            file.startDate = QDateTime::fromTime_t(item.toObject().value("start_update").toDouble());
            file.dirName = item.toObject().value("dirname").toString();
            file.uploadName = item.toObject().value("upload_name").toString();
            list.append(file);
        }

        emit uploadListReceived(list);

    }


    reply->deleteLater();


}

void FileSystemApi::requestUploadInfoFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");
        FileUpload file;
        file.id = item.toObject().value("id").toString();
        file.size =item.toObject().value("size").toDouble();
        file.uploaded = item.toObject().value("uploaded").toDouble();
        file.status = item.toObject().value("uploaded").toString();
        file.lastUpdate = QDateTime::fromTime_t(item.toObject().value("last_update").toDouble());
        file.startDate = QDateTime::fromTime_t(item.toObject().value("start_update").toDouble());
        file.dirName = item.toObject().value("dirname").toString();
        file.uploadName = item.toObject().value("upload_name").toString();

        emit uploadInfoReceived(file);

    }


    reply->deleteLater();



}

void FileSystemApi::requestDeleteUploadFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
        emit deleteUploadFinished();

    reply->deleteLater();


}
void FileSystemApi::requestCleanUploadsFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
        emit cleanUploadFinished();

    reply->deleteLater();
}

void FileSystemApi::requestTaskListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    qDebug()<<"task list received";
    qDebug()<<doc.toJson();

    if(fbx()->parseResult(doc))
    {
        QList<FileTask> list;

        foreach (QJsonValue item,  doc.object().value("result").toArray())
        {
            FileTask file;
            file.id = item.toObject().value("id").toVariant().toInt();
            file.type = item.toObject().value("type").toString();
            file.state = item.toObject().value("state").toString();
            file.error = item.toObject().value("error").toString();
            file.createdDate = QDateTime::fromTime_t(item.toObject().value("created_ts").toDouble());
            file.startedDate = QDateTime::fromTime_t(item.toObject().value("started_ts").toDouble());
            file.doneDate = QDateTime::fromTime_t(item.toObject().value("done_ts").toDouble());
            file.duration = item.toObject().value("duration").toVariant().toInt();
            file.progress = item.toObject().value("progress").toVariant().toInt();
            file.eta = item.toObject().value("eta").toVariant().toInt();
            file.from = item.toObject().value("from").toString();
            file.to = item.toObject().value("to").toString();
            file.nfiles = item.toObject().value("nfiles").toVariant().toInt();
            file.nfilesDone = item.toObject().value("nfiles_done").toVariant().toInt();
            file.totalBytes = item.toObject().value("total_bytes").toVariant().toInt();
            file.totalBytesDone = item.toObject().value("total_bytes_done").toVariant().toInt();
            file.currBytes = item.toObject().value("curr_bytes").toVariant().toInt();
            file.rate = item.toObject().value("rate").toVariant().toInt();

            list.append(file);
        }

        if (list.count() > 0 )
            qDebug()<<"YEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEES";

        emit taskListReceived(list);

    }
    reply->deleteLater();
}

void FileSystemApi::requestTaskFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");
        FileTask file;
        file.id = item.toObject().value("id").toVariant().toInt();
        file.type = item.toObject().value("type").toString();
        file.state = item.toObject().value("state").toString();
        file.error = item.toObject().value("error").toString();
        file.createdDate = QDateTime::fromTime_t(item.toObject().value("created_ts").toDouble());
        file.startedDate = QDateTime::fromTime_t(item.toObject().value("started_ts").toDouble());
        file.doneDate = QDateTime::fromTime_t(item.toObject().value("done_ts").toDouble());
        file.duration = item.toObject().value("duration").toVariant().toInt();
        file.progress = item.toObject().value("progress").toVariant().toInt();
        file.eta = item.toObject().value("eta").toVariant().toInt();
        file.from = item.toObject().value("from").toString();
        file.to = item.toObject().value("to").toString();
        file.nfiles = item.toObject().value("nfiles").toVariant().toInt();
        file.nfilesDone = item.toObject().value("nfiles_done").toVariant().toInt();
        file.totalBytes = item.toObject().value("total_bytes").toVariant().toInt();
        file.totalBytesDone = item.toObject().value("total_bytes_done").toVariant().toInt();
        file.currBytes = item.toObject().value("curr_bytes").toVariant().toInt();
        file.rate = item.toObject().value("rate").toVariant().toInt();

        emit taskReceived(file);
    }

    reply->deleteLater();
}

void FileSystemApi::requestDeleteTaskFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
        emit deleteTaskFinished();

    reply->deleteLater();
}

void FileSystemApi::requestUpdateTaskFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
        emit updateTaskFinished();

    reply->deleteLater();
}

