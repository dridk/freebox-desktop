#ifndef CLMODEL_H
#define CLMODEL_H

#include <QAbstractTableModel>
#include "fbxapi.h"
class CLModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CLModel(FbxAPI * fbx, QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void refresh();


protected slots:
    void load(const QList<CallEntry>& list);

private:
    FbxAPI * mFbx;
    QList<CallEntry> mDatas;
};

#endif // CLMODEL_H
