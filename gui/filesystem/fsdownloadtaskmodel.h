#ifndef FSDOWNLOADMODEL_H
#define FSDOWNLOADMODEL_H

#include <QAbstractListModel>
#include <QNetworkReply>
#include "mafreebox.h"
#include "fsmodel.h"  // pour utilise sizeHuman....
#include "fsabstracttaskmodel.h"

class FSDownloadItem {
public:
    FSDownloadItem () {
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

class FSDownloadTaskModel : public FSAbstractTaskModel
{
    Q_OBJECT
public:
    explicit FSDownloadTaskModel(MaFreeBox * fbx, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    int count() const;
    const FSDownloadItem& item(const QModelIndex& index);
    Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void add(QNetworkReply* reply);
    void rem(QNetworkReply* reply);
    virtual void clearFinished();
    virtual void removeTask(const QModelIndex &index);

protected slots:
    void downloadProgress(qint64 bytes,qint64 total);

signals:
    void countChanged();


private:
    MaFreeBox * mFbx;
    QHash<QNetworkReply*, FSDownloadItem> mDatas;
    QMimeDatabase mMimeDb;
};

#endif // FSDOWNLOADMODEL_H
