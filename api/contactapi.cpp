#ifndef CONTACTAPI_H
#define CONTACTAPI_H

#include <QObject>
#include "fbxapi.h"

class ContactNumber;
class ContactAddress;
class ContactUrl;
class ContactEmail;
class ContactEntry;
class ContactApi;


class ContactNumber{
public:
    enum Type{FixedType, MobileType, WorkType, FaxType, OtherType};
    int id;
    int contactId;
    Type type;
    QString number;
    bool isDefault;
    bool isOwn;

};


class ContactAddress {
    enum Type{HomeType, WorkType, OtherType};
    int id;
    int contactId;
    Type type;
    QString number;
    QString street;
    QString street2;
    QString city;
    QString zipcode;
    QString country;

};


class ContactUrl{
public:
    enum Type{ProfileType, BlogType, SiteType, OtherType};
    int id;
    int contactId;
    Type type;
    QString url;

};

class ContactEmail {
public :
    enum Type{HomeType, WorkType, OtherType};
    int id;
    int contactId;
    Type type;
    QString email;
};

class ContactEntry {
public:
    int id;
    QString displayName;
    QString firstName;
    QString lastName;
    QString company;
    QString photoUrl;
    QDateTime lastUpdate;
    QString notes;
    QList<ContactAddress> addresses;
    QList<ContactEmail> emails;
    QList<ContactNumber> numbers;
    QList<ContactUrl> urls;
};

class ContactApi : public QObject
{
    Q_OBJECT
public:
    explicit ContactApi(FbxAPI *parent);

public slots:
        void requestList();
        void requestContact(int id);
        void requestCreate(const ContactEntry& entry);
        void requestDelete(int id);
        void requestUpdate(int id, ContactEntry& entry);

    //    void requestCall(int id);
    //    void requestDelete(int id);
    //    void requestUpdate(int id, bool isNew);

signals:
        void listReceived(const QList<ContactEntry>& list);
        void contactReceived(const ContactEntry& entry);
        void createFinished();
        void deleteFinished();
        void updateFinished();

protected slots:
        void requestListFinished();
        void requestContactFinished();
        void requestCreateFinished();
        void requestDeleteFinished();
        void requestUpdateFinished();


protected:
    FbxAPI * fbx() {
        return qobject_cast<FbxAPI*>(parent());
    }

};


void ContactApi::requestList()
{
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
}

void ContactApi::requestContactFinished()
{
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

#endif // CONTACTAPI_H
