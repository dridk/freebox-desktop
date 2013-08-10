#ifndef STDMODEL_H
#define STDMODEL_H

#include <QStandardItemModel>
#include "mafreebox.h"
class StdModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit StdModel(MaFreeBox * fbx, QObject *parent = 0);

    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);
    bool hasChildren(const QModelIndex &parent) const;
    
signals:
    
public slots:
    void init();
    void load(const QList<FileInfo>& list);
private:
    MaFreeBox * mFbx;
    QModelIndex mCurrentIndex;
};

#endif // STDMODEL_H
