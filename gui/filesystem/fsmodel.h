#ifndef STDMODEL_H
#define STDMODEL_H

#include <QStandardItemModel>
#include "mafreebox.h"
class FSModel : public QStandardItemModel
{
    Q_OBJECT
public:
  enum FileInfoRole {
      PathRole = Qt::UserRole+1,
      MimeTypeRole,
      IsDirRole,
      SizeRole,
      ModifiedRole,
      IndexRole,
      IsLinkRole,
      IsHiddenRole,
      FolderCountRole,
      FileCountRole
  };


    explicit FSModel(MaFreeBox * fbx, QObject *parent = 0);

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);
    bool hasChildren(const QModelIndex &parent) const;
    QString sizeHuman(int size) const;
    QByteArray currentPath(const QModelIndex& index);

signals:
    
public slots:
    void init();
    void load(const QList<FileInfo>& list);
private:
    MaFreeBox * mFbx;
    QModelIndex mCurrentIndex;
    bool mIsLoading;
};



class FolderFilterProxyModel : public QSortFilterProxyModel
{
public:
bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;


};


#endif // STDMODEL_H
