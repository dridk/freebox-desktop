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
    void fetchMore(const QModelIndex &parent);
    bool canFetchMore(const QModelIndex &parent) const;
    bool hasChildren(const QModelIndex &parent) const;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);


    QString sizeHuman(int size) const;
    QByteArray currentPath(const QModelIndex& index);




signals:
    //Quand ca telecharge, on disable la vue, pour eviter des erreurs
    void enableChanged(bool enable);

public slots:
    void init();
    void dataReceived(const QList<FileInfo>& list);
    void mkdir(const QString& name, const QModelIndex& parent);
    void remove(const QModelIndexList& indexes);
    void upload(const QString& filename, const QModelIndex& parent);
    void upload(const QStringList& list, const QModelIndex& parent);
    void download(const QString& destination, const QModelIndex& index);
    void refresh(const QModelIndex& parent = QModelIndex());

protected slots:
    void refreshCurrentIndex();
    void itemToBeRenamed(QStandardItem * item);



private:
    MaFreeBox * mFbx;
    QModelIndex mCurrentIndex;
    bool mIsLoading;

    QMap<QNetworkReply*, QModelIndex> mReplyIndexes;
};






#endif // STDMODEL_H
