#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include "mafreebox.h"
#include <QFile>
#include <QMimeDatabase>

class MaFreeBox;
class FileSystem;
struct FileUpload;

class FileInfo { // class et pas une struct pour etre utilisé dans le treeview
public:
    FileInfo() {
        isDir = false;
        size = 0;
        index = 0;
        link = false;
        hidden = false;
        folderCount = 0;
        fileCount = 0;
    }

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



    Q_ENUMS(ConflictMode)

    explicit FileSystem(MaFreeBox *parent = 0);
    ~FileSystem();

public slots:
    void requestList(const QString& path = QString(),
                     bool onlyFolder   =false,
                     bool countSubFolder=false,
                     bool removeHidden =true

            );

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
    void requestUpload(const QString& dirPath, const QString& fileName);
    void requestUploadList();
    void requestUploadInfo(int id);
    void requestDeleteUpload(int id);
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
    void uploadFinished(const QString& fileName);
    void uploadListReceived(const QList<FileUpload>& list);
    void uploadInfoReceived(const FileUpload& file);
    void deleteUploadFinished();
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
    void requestStartUpload();
    void requestUploadListFinished();
    void requestUploadInfoFinished();
    void requestDeleteUploadFinished();
    void requestCleanUploadsFinished();


    MaFreeBox * fbx() {
        return qobject_cast<MaFreeBox*>(parent());
    }
    

private:
    QMap <QNetworkReply*, QFile*> mDownloads;
    QMap <QNetworkReply*, QFile*> mUploads;
    QMimeDatabase mMimeDatabase;


    
};


//===== must be at end cause by forward declaration error with FileSystem::UploadStatus
struct FileUpload {

    QString id;
    unsigned int size;
    unsigned int uploaded;
    //    FileSystem::UploadStatus status;
    QString status;
    QDateTime startDate;
    QDateTime lastUpdate;
    QString dirName;
    QString uploadName;


};


#endif // FILESYSTEM_H
