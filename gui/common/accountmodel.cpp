#include "accountmodel.h"
#include <QStringList>
#include <QFont>
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
        QFont font;
        if(settings.value(key+"/isDefault").toBool())
            font.setBold(true);
        else font.setBold(false);
        return font;
    }

    settings.endGroup(); // end accounts

    return QVariant();
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

bool AccountModel::removeAccount(int row)
{
    beginResetModel();
    QSettings settings;
    settings.beginGroup("accounts");
    settings.remove(settings.childGroups().at(row));
    settings.endGroup();
    endResetModel();
    return true;
}

void AccountModel::setDefaultAccount(int row)
{
    beginResetModel();
    QSettings settings;
    settings.beginGroup("accounts");
    QString defaultKey = settings.childGroups().at(row);

    foreach (QString key, settings.childGroups())
        settings.setValue(key+"/isDefault", (key == defaultKey));

    settings.endGroup(); //end accounts
    endResetModel();

}
