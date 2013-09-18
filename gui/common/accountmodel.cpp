#include "accountmodel.h"
#include <QStringList>
#include <QFont>
#include <QApplication>
AccountModel::AccountModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    mSettings.beginGroup("accounts");
    qDebug()<<mSettings.fileName();
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mSettings.childGroups().count();

}

int AccountModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {

        QString key = mSettings.childGroups().at(index.row());
        if (index.column() == 0)
            return key;

        if (index.column() == 1) {
            QString host = mSettings.value(key+"/hostname").toString();
            int ip       = mSettings.value(key+"/port").toInt();
            return QString("%1:%2").arg(host).arg(ip);

        }

    }

    if (role == Qt::DecorationRole && index.column() == 0)
    {

        QString key = mSettings.childGroups().at(index.row());
        return mSettings.value(key+"/icon");

    }


    return QVariant();
}

QVariant AccountModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
            return "Nom";
        if (section == 1)
            return "Adresse";
    }
    return QVariant();
}

QStringList AccountModel::names() const
{
    return mSettings.childGroups();

}

QString AccountModel::name(int row) const
{
    return mSettings.childGroups().value(row,QString());

}

bool AccountModel::addAccount(const QString &name, const QString &hostname, int port,const QIcon &icon)
{

    if (mSettings.childGroups().contains(name))
        return false;

    mSettings.beginGroup(name);
    mSettings.setValue("name", name);
    mSettings.setValue("hostname", hostname);
    mSettings.setValue("port", port);
    mSettings.setValue("token", QString());
    mSettings.setValue("icon", icon);
    mSettings.setValue("isDefault",false);
    mSettings.endGroup();

    emit layoutChanged();
    return true;
}

bool AccountModel::updateAccount(const QString &name, const QString &hostname, int port, const QIcon &icon)
{
    if (!mSettings.childGroups().contains(name))
        return false;

    mSettings.beginGroup(name);
    mSettings.setValue("name", name);
    mSettings.setValue("hostname", hostname);
    mSettings.setValue("port", port);
    mSettings.setValue("icon", icon);
    mSettings.endGroup();

    qDebug()<<"updated";
    emit layoutChanged();
    return true;

}
bool AccountModel::removeAccount(const QString &name)
{

    if (!mSettings.childGroups().contains(name))
        return false;

    mSettings.remove(name);
    emit layoutChanged();
    return true;
}

bool AccountModel::removeAccount(int row)
{
    if (row >= mSettings.childGroups().count())
        return false;
    removeAccount(mSettings.childGroups().value(row));
    return true;
}

QString AccountModel::applicationToken(const QString &name) const
{
    if (!mSettings.childGroups().contains(name))
        return QString();

    return mSettings.value(QString("%1/token").arg(name)).toString();

}

QString AccountModel::hostName(const QString &name) const
{
    if (!mSettings.childGroups().contains(name))
        return QString();

    return mSettings.value(QString("%1/hostname").arg(name)).toString();

}

int AccountModel::port(const QString &name) const
{
    if (!mSettings.childGroups().contains(name))
        return 80;

    return mSettings.value(QString("%1/port").arg(name)).toInt();
}

void AccountModel::setApplicationToken(const QString &name, const QString &token)
{
    mSettings.beginGroup(name);
    mSettings.setValue("token", token);
    mSettings.endGroup();
}

void AccountModel::setHostName(const QString &name, const QString &host)
{
    mSettings.beginGroup(name);
    mSettings.setValue("hostname", host);
    mSettings.endGroup();
}

void AccountModel::setPort(const QString &name, int port)
{
    mSettings.beginGroup(name);
    mSettings.setValue("port", port);
    mSettings.endGroup();
}
