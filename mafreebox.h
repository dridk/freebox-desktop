#ifndef MAFREEBOX_H
#define MAFREEBOX_H

#include <QObject>
#include <QtNetwork>
class MaFreeBox : public QObject
{
    Q_OBJECT
public:
    explicit MaFreeBox(QObject *parent = 0);

    void setHostName(const QString& host) ;
    void setPort(int port) ;
    const QString& appToken() const;

    //request methods
public slots:
    void init();
    void authorize(const QString& appId, const QString& appName,
                   const QString& appVersion, const QString& deviceName);
    void authorizeProgress();

    void login();
    void session(const QString& appId);

    static QString hmacSha1(QByteArray key, QByteArray baseString);

    void test();

signals:
    void ready();
    void authorizedReceived(const QString& appToken,int trackId);
    void authorizeProgressReceived(const QString& challenge, const QString& status);
    void sessionReceived();
    void loginReceived();

protected slots:
    void initFinished();
    void authorizeFinished();
    void authorizeProgressFinished();
    void loginFinished();
    void sessionFinished();

protected:
     QNetworkRequest createRequest(const QString& uri) const;

private:
    QString mHost;
    int mPort;
    QString mBaseUrl;
    QString mApiVersion;
    QString mDeviceType;
    QString mDeviceName;
    QString mSessionToken;

    QString mAppToken;
    double mTrackId;
    QString mChallenge;
    QString mAuthorizeStatus;
    QNetworkAccessManager * mNetManager;
    
};

#endif // MAFREEBOX_H
