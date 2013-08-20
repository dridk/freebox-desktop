#ifndef FSDOWNLOADMODEL_H
#define FSDOWNLOADMODEL_H

#include <QAbstractListModel>
#include <QNetworkReply>
#include "mafreebox.h"

class FSDownloadItem {
public:
    FSDownloadItem () {
        reply = NULL;
        bytes = 0;
        total = 0;
        progress = 0;
    }

    QNetworkReply * reply ;
    QString filename;
    qint64 bytes;
    qint64 total;
    double progress;

};

class FSDownloadModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FSDownloadModel(MaFreeBox * fbx, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    int count() const;

public slots:
    void add(QNetworkReply* reply);
    void rem(QNetworkReply* reply);

protected slots:
    void downloadProgress(qint64 bytes,qint64 total);

signals:
    void countChanged();


private:
    MaFreeBox * mFbx;
    QHash<QNetworkReply*, FSDownloadItem> mDatas;

};

#endif // FSDOWNLOADMODEL_H
