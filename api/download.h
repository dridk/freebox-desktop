#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFrame>
#include <QList>
#include "fbxapi.h"

class FbxAPI;
class Download;
class DownloadTask;
class DownloadStats;
class DlRate;
class DlNewsConfig;
class DlBtConfig;
class DlFeedConfig;
class DlBlockListConfig;
class DownloadConfiguration;

class DownloadTask{
public:
    int id;
    QString type; // need enum
    QString name;
    QString status;// need enum
    double size;
    int queuePos;
    QString ioPriority;// need enum
    double txBytes;
    double rxBytes;
    double txRate;
    double rxRate;
    double txPct;
    double rxPct;
    QString error;
    QDateTime createdTs;
    QDateTime eta;
    QString downloadDir;
    int stopRatio;
    QString archivePassword;
};

class DownloadStats{
public:
    int nbTasks;
    int nbTasksStopped;
    int nbTasksChecking;
    int nbTasksQueued;
    int nbTasksExtracting;
    int nbTasksDone;
    int nbTasksRepairing;
    int nbTasksSeeding;
    int nbTasksDownloading;
    int nbTasksError;
    int nbTasksStopping;
    int nbTasksActive;
    int nbRss;
    int nbRssItemsUnread;
    int rxRate;
    int txRate;
    // pas encore fait le throtting...
};
class DlRate {
public:
    int txRate;
    int rxRate;
};

class DlThrottlingConfig {
public:
    enum Type {NormalType,  SlowType, HibernateType };
    enum Mode {NormalMode, SlowMode, HibernateMode, ScheduleMode};
    static Type typeFromString(const QString& string) {
        if (string == "normal")
            return NormalType;
        if (string == "slow")
            return SlowType;
        if (string == "hibernate")
            return HibernateType;
    }

    static Mode modeFromString(const QString& string){
        if (string == "normal")
            return NormalMode;
        if (string == "slow")
            return SlowMode;
        if (string == "hibernate")
            return HibernateMode;
        if (string == "schedule")
            return ScheduleMode;
        return NormalMode;
    }

    DlRate normal;
    DlRate slow;
    QList<Type> schedule;
    Mode mode;
};

class DlNewsConfig {
public:
    QString server;
    int port;
    bool ssl;
    QString user;
    QString password;
    int nthreads;
    bool autoRepair;
    bool lazyPar2;
    bool autoExtract;
    bool eraseTmp;
};

class DlBtConfig {
public:
    enum Type {UnsupportedType, AllowedType, PreferredType, RequiredType };
    static  Type typeFromString(const QString& string){
        if (string == "allowed")
            return AllowedType;
        if (string == "unsupported")
            return UnsupportedType;
        if (string == "preferred")
            return PreferredType;
        if (string == "required")
            return RequiredType;
        return UnsupportedType;

    }

    int maxPeers;
    int stopRatio;
    Type cryptoSupport;
    bool enableDht;
    bool enablePex;
    int announceTimeout;

};

class DlFeedConfig {
public:
    int fetchInterval;
    int maxItems;
};

class DlBlockListConfig {
public:
    QStringList sources;
};

class DownloadConfiguration {
public:
    int maxDownloadingTasks;
    QString downloadDir;
    QString watchDir;
    bool useWatchDir;
    DlThrottlingConfig throttling;
    DlNewsConfig news;
    DlBtConfig bt;
    DlFeedConfig feed;
    DlBlockListConfig blocklist;
};


class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(FbxAPI *parent = 0);
public slots:
    void requestList();
    void requestDownload(int id);
    void requestRemove(int id);
    void requestErase(int id);
    void requestUpdate(int id, const QString& p, const QString& s );
    void requestLog(int id);
    void requestStats();
    void requestAdd(const QString& url, const QString& destination = QString(),
                    const QString& username = QString(),
                    const QString& password = QString(),
                    const QString archivePassword = QString());

    void requestAddList(const QStringList& urls, const QString& destination=QString(),
                        bool recursive=false,
                        const QString& username = QString(),
                        const QString& password = QString(),
                        const QString archivePassword = QString());

    void requestConfig();


signals:
    void listReceived(const QList<DownloadTask>& list);
    void downloadReceived(const DownloadTask& item);
    void removeFinished();
    void eraseFinished();
    void updateFinished();
    void logReceived(const QString& result);
    void statsReceived(const DownloadStats& stat);
    void addFinished();
    void configReceived(const DownloadConfiguration& configuration);



protected slots:
    void requestListFinished();
    void requestDownloadFinished();
    void requestRemoveFinished();
    void requestEraseFinished();
    void requestUpdateFinished();
    void requestLogFinished();
    void requestStatsFinished();
    void requestAddFinished();
    void requestAddListFinished();
    void requestConfigFinished();



protected:
    FbxAPI * fbx() {
        return qobject_cast<FbxAPI*>(parent());
    }
    
};




#endif // DOWNLOAD_H
