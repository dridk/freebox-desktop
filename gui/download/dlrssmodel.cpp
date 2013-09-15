#include "dlrssmodel.h"

DLRssModel::DLRssModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int DLRssModel::rowCount(const QModelIndex &parent) const
{
     Q_UNUSED(parent)
    return 0;
}

int DLRssModel::columnCount(const QModelIndex &parent) const
{
     Q_UNUSED(parent)
     return 0;
}

QVariant DLRssModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    if (role == Qt::DisplayRole)
        return "test";
    return QVariant();
}
