#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include "mafreebox.h"
#include <QFile>

class MaFreeBox;
struct FileInfo {
    QString path;
    QString name;
    QString mimetype;
    bool isDir;
    int size;
    QDateTime modified;
    int index;
    bool link;
    bool hidden;
    int folderCount;
    int fileCount;
};

struct FileUpload {

    QString id;
    int size;
    int uploaded;

};



class FileSystem : public QObject
{
    Q_OBJECT
public:
    enum ConflictMode {
        OverwriteMode,
        BothMode,
        RecentMode,
        SkipMode
    };

    enum UploadStatus {
        AuthorizedStatus,
        InProgressStatus,
        DoneStatus,
        FailedStatus,
        ConflictStatus,
        TimeoutStatus,
        CancelledStatus
    };

    Q_ENUMS(ConflictMode)
    Q_ENUMS(UploadStatus)
    explicit FileSystem(MaFreeBox *parent = 0);
    ~FileSystem();

public slots:
    void requestList(const QString& path = QString());
    void requestInfo(const QString& path);
    void requestMove(const QStringList& paths, const QString& dest,
                     ConflictMode mode = OverwriteMode);

    void requestCopy(const QStringList& paths, const QString& dest,
                     ConflictMode mode = OverwriteMode);


    void requestRemove(const QStringList& paths);
    void requestArchive(const QStringList& paths, const QString& dest);
    void requestExtract(const QString& source,
                        const QString& dest,
                        const QString& password = QString(),
                        bool deleteArchive = false,
                        bool overwrite = false);

    void requestMkdir(const QString& path, const QString& dirName);
    void requestRename(const QString& source, const QString& newName);
    void requestDownload(const QString& path, const QString& localPath);
    void requestUpload(const QString& file, const QString& destPath);
    void requestUploadList();
    void requestUploadInfo(int id);
    void requestRemoveUpload(int id);
    void requestCleanUploads();



signals:
    void listReceived(const QList<FileInfo>& list);
    void infoReceived(const FileInfo& fileInfo);
    void moveFinished();
    void copyFinished();
    void removeFinished();
    void archiveFinished();
    void extractFinished();
    void mkdirFinished();
    void renameFinished();
    void downloadFinished(const QString& fileName);
    void uploadFinished();
    void uploadListReceived(const QList<FileUpload>& list);
    void uploadReceived(const FileUpload& file);
    void removeUploadFinished();
    void cleanUploadFinished();



protected slots:
    void requestListFinished();
    void requestInfoFinished();
    void requestMoveFinished();
    void requestCopyFinished();
    void requestRemoveFinished();
    void requestArchiveFinished();
    void requestExtractFinished();
    void requestMkdirFinished();
    void requestRenameFinished();
    void requestDownloadFinished();
    void requestDownloadReadyRead();
    void requestDownloadError();
    void requestUploadFinished();
    void requestUploadListFinished();
    void requestUploadInfoFinished();
    void requestRemoveUploadFinished();
    void requestCleanUploadsFinished();


    MaFreeBox * fbx() {
        return qobject_cast<MaFreeBox*>(parent());
    }
    

private:
QMap <QNetworkReply*, QFile*> mDownloads;

    
};

#endif // FILESYSTEM_H
