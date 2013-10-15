#include "callapi.h"

CallApi::CallApi(FbxAPI *parent) :
    QObject(parent)
{


}

void CallApi::requestList()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("call/log/")));
    connect(reply,SIGNAL(finished()),this,SLOT(requestListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void CallApi::requestCall(int id)
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("call/log/%1").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestCallFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void CallApi::requestDelete(int id)
{
    QNetworkReply * reply = fbx()->deleteResource(fbx()->myCreateRequest(QString("call/log/%1").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestDeleteFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void CallApi::requestUpdate(int id, bool isNew)
{

    QNetworkRequest request = fbx()->myCreateRequest(QString("call/log/%1").arg(id));
    QJsonObject json;
    json.insert("new",isNew);
    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->put(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}


void CallApi::requestListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        QList<CallEntry> list;

        foreach (QJsonValue item,  doc.object().value("result").toArray())
        {
            CallEntry call;
            call.id = item.toObject().value("id").toDouble();
            call.number = item.toObject().value("number").toString();
            call.duration = item.toObject().value("duration").toDouble();
            call.contactId = item.toObject().value("contact_id").toDouble();
            call.name = item.toObject().value("name").toString();
            call.isNew = item.toObject().value("new").toBool();
            call.type = CallEntry::typeFromString(item.toObject().value("type").toString());
            call.datetime = QDateTime::fromTime_t(item.toObject().value("datetime").toDouble());
            list.append(call);
        }

        emit listReceived(list);
    }
}

void CallApi::requestCallFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");
        CallEntry call;
        call.id = item.toObject().value("id").toDouble();
        call.number = item.toObject().value("number").toString();
        call.duration = item.toObject().value("duration").toDouble();
        call.contactId = item.toObject().value("contact_id").toDouble();
        call.name = item.toObject().value("name").toString();
        call.isNew = item.toObject().value("new").toBool();
        call.type = CallEntry::typeFromString(item.toObject().value("type").toString());
        call.datetime = QDateTime::fromTime_t(item.toObject().value("datetime").toDouble());

        emit callReceived(call);
    }
}

void CallApi::requestDeleteFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        emit deleteFinished();
    }
}

void CallApi::requestUpdateFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        emit updateFinished();
    }
}
