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
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QStringList names() const;


    bool addAccount(const QString& name,
                    const QString& hostname,
                    int port = 80,
                    const QIcon& icon = QIcon());

    bool updateAccount(const QString& name,
                       const QString& hostname,
                       int port = 80,
                       const QIcon& icon = QIcon());

    bool removeAccount(const QString& name);
    bool removeAccount(int row);

    QString name(int row) const;
    QString applicationToken(const QString& name) const;
    QString hostName(const QString& name) const;
    int port(const QString& name) const;

    void setApplicationToken(const QString& name, const QString& token);
    void setHostName(const QString& name, const QString& host);
    void setPort(const QString& name, int port);


private:
    QSettings mSettings;

    
};

#endif // ACCOUNTMODEL_H
