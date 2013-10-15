#ifndef CALLAPI_H
#define CALLAPI_H

#include <QObject>
#include "fbxapi.h"

class callEntry;
class CallApi;

class CallEntry {
public:
    enum Type {MissedType, AcceptedType, OutgoingType};
    int id;
    QDateTime datetime;
    QString number;
    QString name;
    int duration;
    bool isNew;
    int contactId;
    Type type;

    static QString typeToString(const Type& type){

        if (type == MissedType)
            return "missed";
        if (type == AcceptedType)
            return "accepted";
        if (type == OutgoingType)
            return "outgoing";
        return "missed";
    }

    static Type typeFromString(const QString& string){
        if (string == "missed")
            return MissedType;
        if (string == "accepted")
            return AcceptedType;
        if (string == "outgoing")
            return OutgoingType;
        return MissedType;
    }
};

class CallApi : public QObject
{
    Q_OBJECT
public:
    explicit CallApi(FbxAPI *parent);
    
public slots:
    void requestList();
    void requestCall(int id);
    void requestDelete(int id);
    void requestUpdate(int id, bool isNew);

signals:
    void listReceived(const QList<CallEntry>& list);
    void callReceived(const CallEntry& call);
    void deleteFinished();
    void updateFinished();

protected slots:
    void requestListFinished();
    void requestCallFinished();
    void requestDeleteFinished();
    void requestUpdateFinished();



protected:
    FbxAPI * fbx() {
        return qobject_cast<FbxAPI*>(parent());
    }
    
};

#endif // CALLAPI_H
