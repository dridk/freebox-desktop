#ifndef CTMODEL_H
#define CTMODEL_H

#include <QAbstractListModel>
#include "fbxapi.h"

class CtModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CtModel(FbxAPI * fbx, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

protected slots:
    void load(const QList<ContactEntry>& list);

private:
FbxAPI * mFbx;
QList<ContactEntry> mContacts;


};

#endif // CTMODEL_H
