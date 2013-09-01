#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFrame>
#include "fbxapi.h"

class FbxAPI;
class Download;
class DownloadTask;
class DownloadStats;

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
    void requestAdd(const QString& url, const QString& destination, bool recursive=true,
                    const QString& username = QString(),
                    const QString& password = QString(),
                    const QString archivePassword = QString());

    void requestAddList(const QStringList& url, const QString& destination, bool recursive=true,
                    const QString& username = QString(),
                    const QString& password = QString(),
                    const QString archivePassword = QString());


signals:
    void listReceived(const QList<DownloadTask>& list);
    void downloadReceived(const DownloadTask& item);
    void removeFinished();
    void eraseFinished();
    void updateFinished();
    void logReceived(const QString& result);
    void statsReceived(const DownloadStats& stat);
    void addFinished();



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



protected:
    FbxAPI * fbx() {
        return qobject_cast<FbxAPI*>(parent());
    }
    
};




#endif // DOWNLOAD_H
