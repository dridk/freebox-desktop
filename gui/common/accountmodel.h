#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractListModel>
#include <QSettings>
#include <QIcon>
#include <QDebug>
class AccountModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AccountModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    bool addAccount(const QString& name,
                    const QString& hostname,
                    int port = 80,
                    const QIcon& icon = QIcon());

    bool removeAccount(int row);
    void setDefaultAccount(int row);

private:

    
};

#endif // ACCOUNTMODEL_H
