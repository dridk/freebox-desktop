#include "connectionapi.h"

ConnectionApi::ConnectionApi(QObject *parent) :
    QObject(parent)
{
}

void ConnectionApi::requestStatus()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest("connection/"));
    connect(reply,SIGNAL(finished()),this,SLOT(requestStatusFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void ConnectionApi::requestConfiguration()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest("connection/config/"));
    connect(reply,SIGNAL(finished()),this,SLOT(requestStatusFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void ConnectionApi::requestUpdateConfigurationFinished(bool ping, bool remoteAccess, int remoteAccessPort,
                                                       bool wool, bool adblock, bool allowTokenRequest)
{
    QNetworkRequest request = fbx()->myCreateRequest("connection/config/");
    QJsonObject json;
    json.insert("ping",ping);
    json.insert("remote_access",remoteAccess);
    json.insert("remote_access_port",remoteAccessPort);
    json.insert("wool",wool);
    json.insert("adblock",adblock);
    json.insert("allow_token_request",allowTokenRequest);

    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->put(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateConfigurationFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));



}

void ConnectionApi::requestStatusFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");

        ConnectionStatus status;

        status.bytesDownPriv = item.toObject().value("bytes_down_priv").toDouble();
        status.bytesUpPriv = item.toObject().value("bytes_up_priv").toDouble();
        status.bytesUp= item.toObject().value("bytes_up").toDouble();
        status.bytesDown =  item.toObject().value("bytes_down").toDouble();
        status.rateDown =  item.toObject().value("rate_down").toDouble();
        status.rateUp=  item.toObject().value("rate_up").toDouble();
        status.rateUpPriv=  item.toObject().value("bytes_up_priv").toDouble();
        status.rateDownPriv=  item.toObject().value("rate_down_priv").toDouble();
        status.bandwidthUp=  item.toObject().value("bandwidth_up").toDouble();
        status.ipv4=  item.toObject().value("ipv4").toString();
        status.ipv6=  item.toObject().value("ipv6").toString();
        status.state =  status.stateFromString(item.toObject().value("ipv6").toString());
        status.type =  status.typeFromString(item.toObject().value("type").toString());
        status.media =  status.mediaFromString(item.toObject().value("media").toString());

        emit statusReceived(status);

    }


}

void ConnectionApi::requestConfigurationFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");

        ConnectionConfiguration config;

        config.ping = item.toObject().value("ping").toBool();
        config.isSecurePass = item.toObject().value("is_secure_pass").toBool();
        config.remoteAccessPort = item.toObject().value("remote_access_port").toDouble();
        config.remoteAccess = item.toObject().value("remote_access").toBool();
        config.wol = item.toObject().value("wol").toBool();
        config.adblock = item.toObject().value("adblock").toBool();
        config.adblockNotSet = item.toObject().value("adblock_not_set").toBool();
        config.apiRemoteAccess = item.toObject().value("api_remote_access").toBool();
        config.allowTokenRequest = item.toObject().value("allow_token_request").toBool();
        config.remoteAccessIp = item.toObject().value("remote_access_ip").toString();

        emit configurationReceived(config);

    }


}

void ConnectionApi::requestUpdateConfigurationFinished()
{

    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
        emit updateConfigurationFinished();


}



