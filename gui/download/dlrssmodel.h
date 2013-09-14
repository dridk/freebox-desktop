#ifndef DLRSSMODEL_H
#define DLRSSMODEL_H

#include <QAbstractTableModel>

class DLRssModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DLRssModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    
signals:
    
public slots:
    
};

#endif // DLRSSMODEL_H
