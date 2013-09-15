#include "accountmodel.h"
#include <QStringList>
#include <QFont>
#include <QApplication>
AccountModel::AccountModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    QSettings settings;
    settings.beginGroup("accounts");
    return settings.childGroups().count();
    settings.endGroup();

}

int AccountModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    QSettings settings;
    settings.beginGroup("accounts");

    if (role == Qt::DisplayRole)
    {

        QString key = settings.childGroups().at(index.row());
        if (index.column() == 0)
            return key;

        if (index.column() == 1)
            return settings.value(key+"/hostname").toString();


    }

    if (role == Qt::FontRole)
    {
        QString key = settings.childGroups().at(index.row());
        QFont font = QApplication::font();
        if(settings.value(key+"/isDefault").toBool())
            font.setBold(true);
        else font.setBold(false);
        return font;
    }

    if (role == Qt::DecorationRole && index.column() == 0)
    {

        QString key = settings.childGroups().at(index.row());
        return settings.value(key+"/icon");

    }

    settings.endGroup(); // end accounts

    return QVariant();
}

QString AccountModel::nameOf(int row) const
{
    QSettings settings;
    settings.beginGroup("accounts");
    return settings.childGroups().at(row);

}

bool AccountModel::addAccount(const QString &name, const QString &hostname, int port, const QIcon &icon)
{
    QSettings settings;
    settings.beginGroup("accounts");
    if (settings.childGroups().contains(name))
    {
        qDebug()<<name<<" account already exist";
        return false;
    }

    qDebug()<<"add"<<icon.name();
    beginResetModel();
    settings.beginGroup(name);
    settings.setValue("hostname", hostname);
    settings.setValue("port", port);
    settings.setValue("icon", icon);
    settings.setValue("isDefault", false);
    settings.endGroup(); // end keys
    endResetModel();

    settings.endGroup(); //end accounts
    return true;

}

bool AccountModel::updateAccount(const QString &name, const QString &hostname, int port, const QIcon &icon)
{
    QSettings settings;
    settings.beginGroup("accounts");
    if (!settings.childGroups().contains(name))
    {
        qDebug()<<name<<" account cannot be updated";
        return false;
    }

    beginResetModel();
    settings.beginGroup(name);
    settings.setValue("hostname", hostname);
    settings.setValue("port", port);
    settings.setValue("icon", icon);
    settings.setValue("isDefault", false);
    settings.endGroup(); // end keys
    endResetModel();

    settings.endGroup(); //end accounts
    return true;
}

bool AccountModel::removeAccount(const QString &name)
{
    beginResetModel();
    QSettings settings;
    settings.beginGroup("accounts");
    settings.remove(name);
    settings.endGroup();
    endResetModel();
    return true;
}

void AccountModel::setDefaultAccount(const QString &name)
{
    beginResetModel();
    QSettings settings;
    settings.beginGroup("accounts");

    foreach (QString key, settings.childGroups())
        settings.setValue(key+"/isDefault", (key == name));

    settings.endGroup(); //end accounts
    endResetModel();

}

void AccountModel::setApplicationToken(const QString &name, const QString &token)
{
    QSettings settings;
    settings.beginGroup("accounts");

    settings.setValue(name+"/token", token);

    settings.endGroup();
}
