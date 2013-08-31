#include "download.h"

Download::Download(FbxAPI *parent) :
    QObject(parent)
{
}

void Download::requestList()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest("downloads"));

    connect(reply,SIGNAL(finished()),this,SLOT(requestListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestDownload(int id)
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/%1").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestDownloadFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestRemove(int id)
{
    QNetworkReply * reply = fbx()->deleteResource(fbx()->myCreateRequest(QString("downloads/%1").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestRemoveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestErase(int id)
{
    QNetworkReply * reply = fbx()->deleteResource(fbx()->myCreateRequest(QString("downloads/%1/erase").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestEraseFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestUpdate(int id,const QString &p, const QString &s)
{
    QJsonObject json;
    json.insert("io_priority",p);
    json.insert("status",s);
    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->put(fbx()->myCreateRequest(QString("downloads/%1").arg(id)),
                                       doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestLog(int id)
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/%1/log").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestLogFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestStats()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/stats")));

    connect(reply,SIGNAL(finished()),this,SLOT(requestStatsFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestAdd(const QString &url, const QString &destination, bool recursive, const QString &username, const QString &password, const QString archivePassword)
{

    QJsonObject json;
    json.insert("download_url",url);
    if (!destination.isEmpty())
    json.insert("download_dir",destination);
    json.insert("recursive",recursive);
    if (!username.isEmpty())
    json.insert("username",username);
    if (!password.isEmpty())
    json.insert("password",password);
    if (!archivePassword.isEmpty())
    json.insert("archive_password",archivePassword);

    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->post(fbx()->myCreateRequest(QString("downloads/add")),
                                       doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestAddFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void Download::requestAddList(const QStringList &url, const QString &destination, bool recursive, const QString &username, const QString &password, const QString archivePassword)
{
    QJsonObject json;
    json.insert("download_url_list",url.join("\n"));
    if (!destination.isEmpty())
    json.insert("download_dir",destination);
    json.insert("recursive",recursive);
    if (!username.isEmpty())
    json.insert("username",username);
    if (!password.isEmpty())
    json.insert("password",password);
    if (!archivePassword.isEmpty())
    json.insert("archive_password",archivePassword);

    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->post(fbx()->myCreateRequest(QString("downloads/add")),
                                       doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestAddListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}


//======================== SLOT FINISHED ==============================


void Download::requestListFinished()
{
}

void Download::requestDownloadFinished()
{
}

void Download::requestRemoveFinished()
{
}

void Download::requestEraseFinished()
{
}

void Download::requestUpdateFinished()
{
}

void Download::requestLogFinished()
{
}

void Download::requestStatsFinished()
{
}

void Download::requestAddFinished()
{
}

void Download::requestAddListFinished()
{
}
