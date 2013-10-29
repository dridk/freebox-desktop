#include "ctmodel.h"
#include <QDebug>
CTModel::CTModel(FbxAPI * fbx, QObject * parent) :
    QAbstractListModel(parent)
{
    mFbx = fbx;

    connect(mFbx->contact(),
            SIGNAL(listReceived(QList<ContactEntry>)),
            this,SLOT(load(QList<ContactEntry>)));
}
int CTModel::rowCount(const QModelIndex &parent) const
{
    return mContacts.count();


}

QVariant CTModel::data(const QModelIndex &index, int role) const
{

    if ( role == Qt::DisplayRole)
        return mContacts.at(index.row()).displayName;

    return QVariant();

}

const ContactEntry &CTModel::contactEntry(int row)
{
    return mContacts[row];
}

void CTModel::load(const QList<ContactEntry> &list)
{
    qDebug()<<"load contact";
    beginResetModel();
    mContacts = list;
    endResetModel();

}
