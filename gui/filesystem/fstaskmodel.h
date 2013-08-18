#ifndef FSTASKMODEL_H
#define FSTASKMODEL_H

#include <QAbstractListModel>
#include "filesystem.h"
class FSTaskModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FSTaskModel(MaFreeBox * fbx, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void load();

protected slots:
    void dataReceived(const QList<FileTask>& list);



private:
    QList<FileTask> mDatas;
    MaFreeBox * mFbx;


    
};

#endif // FSTASKMODEL_H
