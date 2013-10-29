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
    static QString typeToString(const Type& type){
        switch (type)
        {
        case FixedType : return "fixed";
        case MobileType: return "mobile";
        case WorkType: return "work";
        case FaxType : return "fax";
        case OtherType: return "other";
        default: return "other";
        }
    }

    static Type typeFromString(const QString& string)
    {
        if (string == "fixed")
            return FixedType;
        if (string == "mobile")
            return MobileType;
        if (string == "work")
            return WorkType;
        if (string == "fax")
            return FaxType;
        if (string == "other")
            return OtherType;
        return OtherType;
    }
};


class ContactAddress {
public:
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

    static QString typeToString(const Type& type){
        switch (type)
        {
        case HomeType : return "home";
        case WorkType: return "work";
        case OtherType: return "other";
        default: return "other";
        }
    }

    static Type typeFromString(const QString& string)
    {
        if (string == "home")
            return HomeType;
        if (string == "work")
            return WorkType;
        if (string == "other")
            return OtherType;
        return OtherType;
    }

};


class ContactUrl{
public:
    enum Type{ProfileType, BlogType, SiteType, OtherType};
    int id;
    int contactId;
    Type type;
    QString url;

    static QString typeToString(const Type& type){
        switch (type)
        {
        case ProfileType : return "profile";
        case BlogType: return "blog";
        case SiteType: return "site";
        case OtherType: return "other";
        default: return "other";
        }
    }

    static Type typeFromString(const QString& string)
    {
        if (string == "profile")
            return ProfileType;
        if (string == "blog")
            return BlogType;
        if (string == "site")
            return SiteType;
        if (string == "other")
            return OtherType;
        return OtherType;
    }


};

class ContactEmail {
public :
    enum Type{HomeType, WorkType, OtherType};
    int id;
    int contactId;
    Type type;
    QString email;

    static QString typeToString(const Type& type){
        switch (type)
        {
        case HomeType : return "profile";
        case WorkType: return "blog";
        case OtherType: return "other";
        default: return "other";
        }
    }

    static Type typeFromString(const QString& string)
    {
        if (string == "home")
            return HomeType;
        if (string == "work")
            return WorkType;
        if (string == "other")
            return OtherType;
        return OtherType;
    }


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

    ContactEntry fromJson(const QJsonValue& item);

};



#endif // CONTACTAPI_H


