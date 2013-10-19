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
//    void requestList();
//    void requestCall(int id);
//    void requestDelete(int id);
//    void requestUpdate(int id, bool isNew);

signals:
//    void listReceived(const QList<CallEntry>& list);
//    void callReceived(const CallEntry& call);
//    void deleteFinished();
//    void updateFinished();

protected slots:
//    void requestListFinished();
//    void requestCallFinished();
//    void requestDeleteFinished();
//    void requestUpdateFinished();



protected:
    FbxAPI * fbx() {
        return qobject_cast<FbxAPI*>(parent());
    }

};

#endif // CONTACTAPI_H
