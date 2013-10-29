#include "ctmodel.h"
#include <QDebug>
CtModel::CtModel(FbxAPI * fbx, QObject * parent) :
    QAbstractListModel(parent)
{
    mFbx = fbx;

    connect(mFbx->contact(),
            SIGNAL(listReceived(QList<ContactEntry>)),
            this,SLOT(load(QList<ContactEntry>)));
}
int CtModel::rowCount(const QModelIndex &parent) const
{
    return mContacts.count();


}

QVariant CtModel::data(const QModelIndex &index, int role) const
{

    if ( role == Qt::DisplayRole)
        return "test";

    return QVariant();

}

void CtModel::load(const QList<ContactEntry> &list)
{
    qDebug()<<"load contact";
    beginResetModel();
    mContacts = list;
    endResetModel();

}
