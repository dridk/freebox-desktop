#ifndef FSUPLOADMODEL_H
#define FSUPLOADMODEL_H

#include <QAbstractListModel>
#include <QNetworkReply>
#include "fsabstracttaskmodel.h"
#include "fbxapi.h"

class FSUploadItem {
public:
    FSUploadItem () {
        reply = NULL;
        bytes = 0;
        progress = 0;
    }

    QNetworkReply * reply ;
    QString title;
    QString subTitle;
    double progress;
    double bytes;
    QString mimeIconPath;
    QTime time;

};

class FSUploadTaskModel : public FSAbstractTaskModel
{
    Q_OBJECT
public:
    explicit FSUploadTaskModel(FbxAPI * fbx, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    virtual int count() ;

public slots:
    void add(QNetworkReply * reply);
    void rem(QNetworkReply * reply);
    virtual void clearFinished();
    virtual void removeTask(const QModelIndex &index);
protected slots:
    void uploadProgress(qint64,qint64);



private:
    FbxAPI * mFbx;
    QHash<QNetworkReply*, FSUploadItem> mDatas;
    
};

#endif // FSUPLOADMODEL_H
