#ifndef DLMODEL_H
#define DLMODEL_H

#include <QAbstractTableModel>
#include "fbxapi.h"
#include "download.h"
#include <QTimer>
class DLModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DLModel(FbxAPI * fbx, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent= QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:
    void updated();

public slots:
    void start(){mTimer->start();}
protected slots:
    void setData(const QList<DownloadTask>& data);
private:
    QList<DownloadTask> mDatas;
    FbxAPI * mFbx;
    QTimer * mTimer;

};

#endif // DLMODEL_H
