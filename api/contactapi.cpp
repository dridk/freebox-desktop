#include "contactapi.h"
ContactApi::ContactApi(FbxAPI *parent)
    :QObject(parent)
{


}

void ContactApi::requestList()
{
    qDebug()<<"requestList";
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("contact/")));

    connect(reply,SIGNAL(finished()),this,SLOT(requestListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void ContactApi::requestContact(int id)
{
}

void ContactApi::requestCreate(const ContactEntry &entry)
{
}

void ContactApi::requestDelete(int id)
{
}

void ContactApi::requestUpdate(int id, ContactEntry &entry)
{
}


void ContactApi::requestListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        QList<ContactEntry> list;
        foreach (QJsonValue item,  doc.object().value("result").toArray())
            list.append(fromJson(item));
        emit listReceived(list);
    }
}

void ContactApi::requestContactFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {
        ContactEntry contact =fromJson(doc.object().value("result"));
        emit contactReceived(contact);
    }
}

void ContactApi::requestCreateFinished()
{
}

void ContactApi::requestDeleteFinished()
{
}

void ContactApi::requestUpdateFinished()
{
}

ContactEntry ContactApi::fromJson(const QJsonValue &item)
{
    ContactEntry contact;
    contact.id = item.toObject().value("id").toDouble();
    contact.displayName = item.toObject().value("display_name").toString();
    contact.firstName = item.toObject().value("first_name").toString();
    contact.lastName = item.toObject().value("last_name").toString();
    contact.company = item.toObject().value("company").toString();
    contact.photoUrl = item.toObject().value("photo_url").toString();
    contact.lastUpdate = QDateTime::fromTime_t(item.toObject().value("last_update").toDouble());
    contact.notes = item.toObject().value("notes").toString();

    //======== DEBUT D AJOUT DES SUB ITEM ===

    //----------- Ajout des adresses --------------
    contact.addresses.clear();
    foreach (QJsonValue subItem,  item.toObject().value("addresses").toArray())
    {
        ContactAddress address;
        address.id = subItem.toObject().value("id").toDouble();
        address.contactId = subItem.toObject().value("contact_id").toDouble();
        address.number = subItem.toObject().value("number").toString();
        address.street = subItem.toObject().value("street").toString();
        address.street2 = subItem.toObject().value("street2").toString();
        address.city = subItem.toObject().value("city").toString();
        address.zipcode = subItem.toObject().value("zipcode").toString();
        address.country = subItem.toObject().value("country").toString();
        contact.addresses.append(address);
    }

    //----------- Ajout des emais --------------
    contact.emails.clear();
    foreach (QJsonValue subItem,  item.toObject().value("addresses").toArray())
    {
        ContactEmail email;
        email.id = subItem.toObject().value("id").toDouble();
        email.contactId = subItem.toObject().value("contact_id").toDouble();
        email.email = subItem.toObject().value("email").toString();
        contact.emails.append(email);
    }
    //----------- Ajout des numbers --------------
    contact.numbers.clear();
    foreach (QJsonValue subItem,  item.toObject().value("addresses").toArray())
    {
        ContactNumber number;
        number.id = subItem.toObject().value("id").toDouble();
        number.contactId = subItem.toObject().value("contact_id").toDouble();
        number.number = subItem.toObject().value("number").toString();
        number.isDefault = subItem.toObject().value("is_default").toBool();
        number.isOwn  = subItem.toObject().value("is_own").toBool();
        contact.numbers.append(number);
    }

    //----------- Ajout des Urls -----------
    contact.urls.clear();
    foreach (QJsonValue subItem,  item.toObject().value("addresses").toArray())
    {
        ContactUrl url;
        url.id = subItem.toObject().value("id").toDouble();
        url.contactId = subItem.toObject().value("contact_id").toDouble();
        url.url = subItem.toObject().value("url").toString();
        contact.urls.append(url);
    }

    return contact;
}

