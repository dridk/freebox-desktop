#include "mafreebox.h"
#include <QDebug>
#include <QJsonDocument>
#include <QSettings>
MaFreeBox::MaFreeBox(QObject *parent) :
    QObject(parent)
{
    mNetManager = new QNetworkAccessManager(this);
    mHost = "mafreebox.free.fr";
    mPort = 80;

    QSettings settings;
    mAppToken = settings.value("app_token").toString();
    mTrackId  = settings.value("track_id").toString();

}

void MaFreeBox::init()
{

    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://%1:%2/api_version").arg(mHost).arg(mPort)));
    connect(mNetManager->get(request),SIGNAL(finished()),this,SLOT(initFinished()));


}

void MaFreeBox::authorize(const QString &appId, const QString &appName, const QString &appVersion, const QString &deviceName)
{

    QJsonObject json;
    json.insert("app_id", appId);
    json.insert("app_name",appName);
    json.insert("app_version",appVersion);
    json.insert("device_name",deviceName);

    QNetworkRequest request = createRequest("login/authorize");

    QNetworkReply * reply = mNetManager->post(request,QJsonDocument(json).toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(authorizeFinished()));

}

void MaFreeBox::setHostName(const QString &host)
{
    mHost = host;
}

void MaFreeBox::setPort(int port)
{
    mPort = port;
}

const QString &MaFreeBox::appToken() const
{
    return mAppToken;
}

void MaFreeBox::initFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply->error()) {

        QJsonDocument doc =  QJsonDocument::fromJson(reply->readAll());

        mApiVersion =  doc.object().value("api_version").toString();
        mDeviceType =  doc.object().value("device_type").toString();
        mBaseUrl    =  doc.object().value("api_base_url").toString();
        mDeviceName =  doc.object().value("device_name").toString();
        emit ready();
    }
}

void MaFreeBox::authorizeFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply->error())
    {
        QJsonDocument doc =  QJsonDocument::fromJson(reply->readAll());
        mAppToken = doc.object().value("result").toObject().value("app_token").toString();
        mTrackId  = doc.object().value("result").toObject().value("track_id").toString();
        QSettings settings; // save token as settings file ...
        settings.setValue("app_token", mAppToken);
        settings.setValue("track_id", mAppToken);

        emit authorizedReceived(mAppToken);

     }
}

QNetworkRequest MaFreeBox::createRequest(const QString& uri) const
{


    //convertion du string 1.0 en v1. Soit "v" + integer. Ca suppose que 1.1 => v1
    int version = qRound(mApiVersion.toDouble());

    QString url = QString("http://%1:%2%3v%4/%5")
            .arg(mHost).arg(mPort).arg(mBaseUrl).arg(version).arg(uri);



    return QNetworkRequest(QUrl(url));

}
