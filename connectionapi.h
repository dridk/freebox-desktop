#ifndef CONNECTIONAPI_H
#define CONNECTIONAPI_H

#include <QObject>
#include "fbxapi.h"

/*! ConnectionStatus Object */
class ConnectionStatus{
public:
    enum State{GoingUp, Up,GoingDown, Down  };
    enum Type{ Ethernet,  Rfc2684, PPPoAtm};
    enum Media { Ftth,  XDsl};



    static QString stateToString(State state){
        switch (state){
        case GoingUp: return "going_up";
        case GoingDown: return "going_down";
        case Up: return "up";
        case Down: return "down";
        }
        return "down";
    }

    static QString typeToString(Type type){
        switch (type){
        case Ethernet: return "ethernet";
        case Rfc2684: return "rfc2684";
        case PPPoAtm: return "pppoatm";
        }
        return "unknown";
    }

    static QString mediaToString(Media media){
        switch (media){
        case Ftth:return "ftth";
        case XDsl:return "xdsl";
        }
        return "unknown";
    }

    static Media mediaFromString(const QString& string){
        if (string == "ftth")
            return Ftth;
        if (string == "xdsl")
            return XDsl;
        return Ftth;
    }

    static Type typeFromString(const QString& string){
        if (string == "ethernet")
            return Ethernet;
        if (string == "rfc2684")
            return Rfc2684;
        if (string == "pppoatm")
            return PPPoAtm;
        return Ethernet;
    }

    static State stateFromString(const QString& string){

        if (string == "going_up")
            return GoingUp;

        if (string == "going_down")
            return GoingDown;

        if (string == "up")
            return Up;

        if (string == "down")
            return Down;

        return GoingDown;
    }


    QString ipv4;
    QString ipv6;
    int rateUp;
    int rateDown;
    int rateUpPriv;
    int rateDownPriv;
    int bandwidthUp;
    int bandwidthDown;
    int bytesUp;
    int bytesDown;
    int bytesUpPriv;
    int bytesDownPriv;
    State state;
    Type type;
    Media media;

};

/*! ConnectionConfiguration Object */

class ConnectionConfiguration{
public:
    bool ping;
    bool isSecurePass; //ronly
    bool remoteAccess;
    int remoteAccessPort;
    QString remoteAccessIp;//ronly
    bool apiRemoteAccess;//ronly
    bool wol;
    bool adblock;
    bool adblockNotSet;//ronly
    bool allowTokenRequest;
};

/*! ConnectionIpv6Delegation Object */

class ConnectionIpv6Delegation{
public:
    QString prefix;
    QString nextHop; // next_hop ipv6  the next hop for the prefix.. Bizarre le type

};

class ConnectionIpv6Configuration{
public:
    bool ipv6Enabled;
    QList<ConnectionIpv6Delegation> delegations;
};





class ConnectionApi : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionApi(QObject *parent = 0);
    void requestStatus();
    void requestConfiguration();
    void requestUpdateConfigurationFinished(bool ping,
                                            bool remoteAccess,
                                            int remoteAccessPort,
                                            bool wool,
                                            bool adblock,
                                            bool allowTokenRequest);


    
signals:
    void statusReceived(const ConnectionStatus& status);
    void configurationReceived(const ConnectionConfiguration& config);
    void updateConfigurationFinished();

protected slots:
    void requestStatusFinished();
    void requestConfigurationFinished();
    void requestUpdateConfigurationFinished();


protected:
    FbxAPI * fbx() {
        return qobject_cast<FbxAPI*>(parent());
    }

};

#endif // CONNECTIONAPI_H
