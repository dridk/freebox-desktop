#include "fsmodel.h"
#include <QDebug>
#include <QStandardItem>
#include <QMimeDatabase>
#include <QResource>

FSModel::FSModel(MaFreeBox *fbx, QObject *parent) :
    QStandardItemModel(parent)
{
    mFbx = fbx;
    setHorizontalHeaderLabels(QStringList()<<"Nom"<<"Taille"<<"Date de modification");

    setColumnCount(3);
}

bool FSModel::canFetchMore(const QModelIndex &parent) const
{
    int t = parent.data(FolderCountRole).toInt() +
            parent.data(FileCountRole).toInt();

    if (t > 0 && itemFromIndex(parent)->rowCount() == 0)
        return true;

    return QStandardItemModel::canFetchMore(parent);
}

void FSModel::fetchMore(const QModelIndex &parent)
{
    QString path = parent.data(PathRole).toString();

    if (itemFromIndex(parent)->rowCount()>0)
        return ;

    mCurrentIndex = parent;
    if (!mIsLoading) {
        mFbx->fileSystem()->requestList(path,false,true,true);
        mIsLoading = true;
    }
}

bool FSModel::hasChildren(const QModelIndex &parent) const
{
    int t = parent.data(FolderCountRole).toInt();

    if (t > 0 )
        return true;

    else
        return QStandardItemModel::hasChildren(parent);


}

void FSModel::init()
{
    mCurrentIndex = QModelIndex();
    mFbx->fileSystem()->requestList(QString(),false,true,true);
    connect(mFbx->fileSystem(),SIGNAL(listReceived(QList<FileInfo>)),
            this,SLOT(load(QList<FileInfo>)));
}

void FSModel::load(const QList<FileInfo> &list)
{

    mIsLoading = false;
    QStandardItem * rootItem ;

    if (!mCurrentIndex.isValid())
        rootItem = invisibleRootItem();
    else
        rootItem = itemFromIndex(mCurrentIndex);

    foreach (FileInfo i, list)
    {
        QList<QStandardItem*> lines;


        QStandardItem * firstItem  = new QStandardItem;
        firstItem->setText(i.name);
        firstItem->setColumnCount(3);
        QString iconUrl = QString(":/mime/%1.png").arg(i.mimetype.replace("/", "_").replace("-","_"));

        if(!QFile::exists(iconUrl))
            firstItem->setIcon(QIcon(":mime/application_octet_stream.png"));
        else
            firstItem->setIcon(QIcon(iconUrl));

        QStandardItem * secondItem = new QStandardItem;
        secondItem->setColumnCount(3);
        if (i.isDir)
            secondItem->setText(QString("%1 élément").arg(i.folderCount+i.fileCount));
        else
            secondItem->setText(sizeHuman(i.size));

        secondItem->setEditable(false);

        QStandardItem * thirdItem = new QStandardItem;
        thirdItem->setText(i.modified.toString("dd/MM/yyyy hh:mm"));
        thirdItem->setEditable(false);
        thirdItem->setColumnCount(3);

        firstItem->setData(i.folderCount, FolderCountRole);
        firstItem->setData(i.fileCount, FileCountRole);
        firstItem->setData(i.path, PathRole);
        firstItem->setData(i.mimetype, MimeTypeRole);
        firstItem->setData(i.isDir, IsDirRole);
        firstItem->setData(i.size, SizeRole);
        firstItem->setData(i.modified, ModifiedRole);
        firstItem->setData(i.index, IndexRole);
        firstItem->setData(i.link, IsLinkRole);
        firstItem->setData(i.hidden, IsHiddenRole);
        firstItem->setEditable(false);

        lines.append(firstItem);
        lines.append(secondItem);
        lines.append(thirdItem);
        rootItem->appendRow(lines);

        emit dataChanged(indexFromItem(firstItem), indexFromItem(firstItem));
  }




}
QString FSModel::sizeHuman(int size) const
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



QByteArray FSModel::currentPath(const QModelIndex &index)
{
    return index.data(PathRole).toString().toUtf8();
}



//=====================================================================
//================FilterModel

bool FolderFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_row);

    return true;



}
