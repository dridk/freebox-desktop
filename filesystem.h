#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include "mafreebox.h"
class FileSystem;
class MaFreeBox;


struct File {
    QString path;
    int fileCount;
    bool link;
    QDateTime modified;
    int folderCount;
    QString name;
    int index;
    QString mimetype;
    bool hidden;
    QString type;
    int size;

};

class FileSystem : public QObject
{
    Q_OBJECT
public:
     FileSystem(MaFreeBox * parent);

     void requestFileList(const QString& path = QString());

protected slots:
     void requestFileListFinished();
    
signals:
     void fileListReceived(const QList<File>& list);
    
public slots:

private:
     MaFreeBox * mSource;
    
};

#endif // FILESYSTEM_H
