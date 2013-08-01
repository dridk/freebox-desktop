#include "filesystem.h"

FileSystem::FileSystem(MaFreeBox *parent) :
    QObject(parent)
{
    mSource = parent;
}

void FileSystem::requestFileList(const QString &path)
{

    QNetworkReply * reply = mSource->get(mSource->createRequest("fs/ls/L0Rpc3F1ZSBkdXI="));

    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),mSource,SLOT(errorReceived(QNetworkReply::NetworkError)));
    connect(reply,SIGNAL(finished()),this,SLOT(requestFileListFinished()));



}

void FileSystem::requestFileListFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if (mSource->parseResult(doc))
    {
        QList<File> filesList;
        foreach (QVariant item, doc.object().value("result").toVariant().toList())
        {
            File f;
            f.name = item.toMap().value("name").toString();
            f.index = item.toMap().value("name").toInt();
            f.link = item.toMap().value("name").toBool();
            //            f.modified = QDateTime::fromString(item.toMap().value("name").toString(),"");
            f.path = item.toMap().value("name").toString();
            f.size = item.toMap().value("name").toInt();
            f.type = item.toMap().value("name").toString();

            filesList.append(f);

        }

        emit fileListReceived(filesList);

    }



}
