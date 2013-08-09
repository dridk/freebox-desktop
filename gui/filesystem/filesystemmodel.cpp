#include "filesystemmodel.h"
#include <QIcon>


FileSystemItem::FileSystemItem(FileSystemItem *parent)
{
    mParent = parent;
    mFileInfo.name = "root";
    mIsLoading = false;

}

FileSystemItem::~FileSystemItem()
{
    qDeleteAll(mChilds);
}

void FileSystemItem::appendChild(FileSystemItem *child)
{
    child->setParent(this);
    mChilds.append(child);

}

int FileSystemItem::childCount() const
{
    return mChilds.count();
}

FileSystemItem *FileSystemItem::parent()
{
    return mParent;
}

FileSystemItem *FileSystemItem::child(int row)
{
    return mChilds.at(row);
}

const QList<FileSystemItem *>&  FileSystemItem::children()
{
    return mChilds;
}

void FileSystemItem::setParent(FileSystemItem *item)
{
    mParent = item;
}

void FileSystemItem::setFileInfo(const FileInfo &info)
{
    mFileInfo = info;
}





////=============== TreeModel =========================

FileSystemModel::FileSystemModel(MaFreeBox *parent) :
    QAbstractItemModel(parent)
{

    mRootItem = new FileSystemItem;


    connect(fbx()->fileSystem(),SIGNAL(listReceived(QList<FileInfo>)),
            this,SLOT(load(QList<FileInfo>)));




}

FileSystemModel::~FileSystemModel()
{
    delete mRootItem;
}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return mRootItem->childCount();


    FileSystemItem * item = static_cast<FileSystemItem*>(parent.internalPointer());
    return item->childCount();

}

int FileSystemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;

}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row,column,parent))
        return QModelIndex();

    FileSystemItem * parentItem;
    if (!parent.isValid())
        parentItem = mRootItem;

    else
        parentItem = static_cast<FileSystemItem*>(parent.internalPointer());

    FileSystemItem * childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row,column, childItem);
    else
        return QModelIndex();
}

QModelIndex FileSystemModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    FileSystemItem * childItem = static_cast<FileSystemItem*>(child.internalPointer());
    FileSystemItem * parentItem = childItem->parent();

    if ( parentItem == mRootItem)
        return QModelIndex();

    int row = parentItem->children().indexOf(childItem);

    return createIndex(row,0, parentItem);

}

bool FileSystemModel::canFetchMore(const QModelIndex &parent) const
{
    FileSystemItem * childItem = toItem(parent);

    if (childItem) {
        if (rowCount(parent) == 0 && childItem->fileInfo().folderCount + childItem->fileInfo().fileCount  )
            return true;
    }


    return false;

}

void FileSystemModel::fetchMore(const QModelIndex &parent)
{
    mCurrentIndex = parent;

    if (!parent.isValid()){
        fbx()->fileSystem()->requestList(QString(),false,true,true);
        return;
    }

    else {

        FileSystemItem * item = toItem(parent);
        item->setLoading(true);
        fbx()->fileSystem()->requestList(item->fileInfo().path,false,true,true);
    }
}

bool FileSystemModel::hasChildren(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return true;

    FileSystemItem * item = toItem(parent);

    if (item->fileInfo().folderCount > 0)
        return true;

    return false;



}

void FileSystemModel::load(const QList<FileInfo> &data)
{
    FileSystemItem * parentItem = toItem(mCurrentIndex);

        if (!data.count() || rowCount(mCurrentIndex) > 0)
            return;




    qDebug()<<"load";

    QModelIndex begin = index(0,0,mCurrentIndex);
    QModelIndex end =  index(data.count()-1,0,mCurrentIndex);

    foreach (FileInfo info, data)
    {
        FileSystemItem * child = new FileSystemItem(parentItem);
        child->setFileInfo(info);
        parentItem->appendChild(child);


    }

}
QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if (role == Qt::UserRole && index.column() == 0) {

    return toItem(index)->fileInfo().isDir;

    }


    if (role == Qt::DisplayRole && index.column() == 0 )
        return toItem(index)->fileInfo().name;

    if (role == Qt::DecorationRole && index.column() == 0)
    {
        if (toItem(index)->isLoading())
            return QIcon(":arrow_refresh.png");


        if (toItem(index)->fileInfo().isDir)
            return QIcon(":folder.png");
        QString fileName = toItem(index)->fileInfo().name;
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
        FileInfo file =  toItem(index)->fileInfo();

        if (file.isDir)
            return QString::number(file.fileCount) + " éléments";
        else
            return sizeHuman(file.size);

    }


    if (role == Qt::DisplayRole && index.column() == 2 )
    {
        return toItem(index)->fileInfo().modified.toString("dd/MM/yyyy hh:mm:ss");

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


FileSystemItem *FileSystemModel::toItem(const QModelIndex &index) const
{
    if (!index.isValid())
        return mRootItem;

    return  static_cast<FileSystemItem*>(index.internalPointer());

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

//=================== FILTER =============================


bool FolderFilterProxyModel::canFetchMore(const QModelIndex &parent) const
{

    return sourceModel()->canFetchMore(mapToSource(parent));



}

void FolderFilterProxyModel::fetchMore(const QModelIndex &parent)
{
    sourceModel()->fetchMore(mapToSource(parent));
}

