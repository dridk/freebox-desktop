#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractListModel>
#include <QMimeDatabase>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "mafreebox.h"


class FileSystemItem {
public:
    FileSystemItem(const QString& name ="root", FileSystemItem * parent = 0);
    ~FileSystemItem();
    void appendChild(FileSystemItem * child);
    int childCount() const;
    FileSystemItem * parent();
    FileSystemItem * child(int row);
    const QList<FileSystemItem*>&  children();
    void setParent(FileSystemItem * item);

    void clear();
//    const FileInfo& fileInfo() const {return mFileInfo;}
//    void setFileInfo(const FileInfo& info);

    bool isLoading() {return mIsLoading;}
    void setLoading(bool loading) {mIsLoading = loading;}

    QString mName;

private:
    FileSystemItem * mParent;
    QList<FileSystemItem* > mChilds;
    bool mIsLoading;



};

class FileSystemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    FileSystemModel(MaFreeBox * parent );
    ~FileSystemModel();
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool canFetchMore(const QModelIndex &parent) const;
    bool hasChildren(const QModelIndex &parent) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    FileSystemItem * toItem(const QModelIndex& index) const;

public slots:
    void fetchMore(const QModelIndex &parent = QModelIndex());
    void refresh();
protected slots:
    void load(const QList<FileInfo>& data);


protected:



    MaFreeBox * fbx() {
        return qobject_cast<MaFreeBox*>(QObject::parent());
    }

    QString sizeHuman(int size) const;

private:
    FileSystemItem * mRootItem;
    QMimeDatabase mMimeDB;
    QModelIndex mCurrentIndex;
    bool mIsDirFilter ;

};


// =============== On filtre les dossier uniquement pour le TreeView...


class FolderFilterProxyModel : public QSortFilterProxyModel
{
public:

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);
    bool hasChildren(const QModelIndex &parent) const;

};




#endif // FILESYSTEMMODEL_H
