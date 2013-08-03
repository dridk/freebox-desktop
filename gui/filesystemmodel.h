#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractListModel>
#include "mafreebox.h"
class FileSystemModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileSystemModel(MaFreeBox * parent );
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void setPath(const QString& path = QString());
    void setPath(const QModelIndex& index);

protected slots:
    void load(const QList<FileInfo>& data);

protected:
    MaFreeBox * fbx() {
        return qobject_cast<MaFreeBox*>(QObject::parent());
    }

private:
    QList<FileInfo> mData;

};

#endif // FILESYSTEMMODEL_H
