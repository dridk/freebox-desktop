#include "dlmodel.h"

DLModel::DLModel(QObject *parent) :
    QAbstractTableModel(parent)
{


}

int DLModel::rowCount(const QModelIndex &parent) const
{
    return 5;
}

int DLModel::columnCount(const QModelIndex &parent) const
{
    return 9;
}

QVariant DLModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return "test";

    return QVariant();
}

QVariant DLModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();

}
