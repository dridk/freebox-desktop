#include "filesystemmodel.h"

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
    return 4;

}


QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole && index.column() == 1 )
        return mData.at(index.row()).name;

    if (role == Qt::DisplayRole && index.column() == 2 )
    {
     FileInfo file =  mData.at(index.row());
     qDebug()<<file.name <<" = > "<<file.path;

     if (file.isDir)
         return QString::number(file.fileCount) + " éléments";
     else
         return QString::number(file.size) + " octect";

    }


    if (role == Qt::DisplayRole && index.column() == 3 )
    {
        return mData.at(index.row()).modified.toString("dd/MM/yyyy hh:mm:ss");

    }

    return QVariant();
}


void FileSystemModel::setPath(const QString &path)
{

    fbx()->fileSystem()->requestList(path);
}

void FileSystemModel::setPath(const QModelIndex &index)
{
    setPath(mData.at(index.row()).path);



}

void FileSystemModel::load(const QList<FileInfo> &data)
{

    mData.clear();
    mData = data;

   emit layoutChanged();




}
