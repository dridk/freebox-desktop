#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractListModel>
#include <QMimeDatabase>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "mafreebox.h"


class FileSystemItem {
public:
    FileSystemItem(FileSystemItem * parent = 0);
    ~FileSystemItem();
    void appendChild(FileSystemItem * child);
    int childCount() const;
    FileSystemItem * parent();
    FileSystemItem * child(int row);
    const QList<FileSystemItem*>&  children();
    void setParent(FileSystemItem * item);

    const FileInfo& fileInfo() const {return mFileInfo;}
    void setFileInfo(const FileInfo& info);

private:
    FileInfo mFileInfo;
    FileSystemItem * mParent;
    QList<FileSystemItem* > mChilds;

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


    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void fetchMore(const QModelIndex &parent = QModelIndex());

protected slots:
    void load(const QList<FileInfo>& data);

protected:


    FileSystemItem * toItem(const QModelIndex& index) const;

    MaFreeBox * fbx() {
        return qobject_cast<MaFreeBox*>(QObject::parent());
    }

    QString sizeHuman(int size) const;

private:
    FileSystemItem * mRootItem;
    QMimeDatabase mMimeDB;
    QModelIndex mCurrentIndex;

};


// =============== On filtre les dossier uniquement pour le TreeView...


class FolderFilterProxyModel : public QSortFilterProxyModel
{
public:

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
        return true;
    }

    virtual bool canFetchMore(const QModelIndex &parent) const{
        return sourceModel() != NULL && sourceModel()->canFetchMore(parent);
    }
    virtual void fetchMore(const QModelIndex& parent) {
          sourceModel()->fetchMore(parent);
      }


};




#endif // FILESYSTEMMODEL_H
