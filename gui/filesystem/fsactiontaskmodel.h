#ifndef FSTASKMODEL_H
#define FSTASKMODEL_H

#include <QAbstractListModel>
#include "filesystem.h"
#include "fsabstracttaskmodel.h"
class FSActionTaskModel : public FSAbstractTaskModel
{
    Q_OBJECT
public:
    explicit FSActionTaskModel(MaFreeBox * fbx, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void load();
    virtual void clearFinished(){}
    virtual void removeTask(const QModelIndex &index){}
    virtual int count(){return 0;}

protected slots:
    void dataReceived(const QList<FileTask>& list);



private:
    QList<FileTask> mDatas;
    MaFreeBox * mFbx;


    
};

#endif // FSTASKMODEL_H
