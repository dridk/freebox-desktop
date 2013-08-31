#ifndef DLMODEL_H
#define DLMODEL_H

#include <QAbstractTableModel>

class DLModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DLModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
signals:
    
public slots:
    
};

#endif // DLMODEL_H
