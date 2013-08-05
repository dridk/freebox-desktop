#include "filesystemmodel.h"
#include <QIcon>
FileSystemModel::FileSystemModel(MaFreeBox *parent) :
    QAbstractTableModel(parent)
{

    connect(fbx()->fileSystem(),SIGNAL(listReceived(QList<FileInfo>)),
            this,SLOT(load(QList<FileInfo>)));

}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    return mData.count();

}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    return 3;

}


QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole && index.column() == 0 )
        return mData.at(index.row()).name;

    if (role == Qt::DecorationRole && index.column() == 0)
    {

        if (mData.at(index.row()).isDir)
            return QIcon(":folder.png");
        QString fileName = mData.at(index.row()).name;
        QString iconPath = mMimeDB.mimeTypeForUrl(QUrl(fileName)).iconName()+".png";
        iconPath.replace("-", "_");
        iconPath = QString("mime")+QDir::separator()+iconPath;
        if (QFile::exists(iconPath))
            return QIcon(iconPath);
        else
            return QIcon(QString("mime")+QDir::separator()+QString("application_octet_stream.png"));

    }

    if (role == Qt::DisplayRole && index.column() == 1 )
    {
        FileInfo file =  mData.at(index.row());

        if (file.isDir)
            return QString::number(file.fileCount) + " éléments";
        else
            return sizeHuman(file.size);

    }


    if (role == Qt::DisplayRole && index.column() == 2 )
    {
        return mData.at(index.row()).modified.toString("dd/MM/yyyy hh:mm:ss");

    }

    return QVariant();
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {

        switch (section)
        {
        case 0: return "Nom"; break;
        case 1: return "Taille"; break;
        case 2: return "Date de modification"; break;


        }



    }

    return QVariant();
}


void FileSystemModel::setPath(const QString &path)
{

    fbx()->fileSystem()->requestList(path);
}

void FileSystemModel::setPath(const QModelIndex &index)
{
    if (mData.value(index.row()).isDir)
        setPath(mData.at(index.row()).path);



}

void FileSystemModel::load(const QList<FileInfo> &data)
{

    mData.clear();
    mData = data;

    emit layoutChanged();





}

QString FileSystemModel::sizeHuman(int size) const
{

    float num = size;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(num >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        num /= 1024.0;
    }
    return QString().setNum(num,'f',2)+" "+unit;

}
