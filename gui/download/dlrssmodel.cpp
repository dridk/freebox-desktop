#include "dlrssmodel.h"

DLRssModel::DLRssModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int DLRssModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int DLRssModel::columnCount(const QModelIndex &parent) const
{
     return 0;
}

QVariant DLRssModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
