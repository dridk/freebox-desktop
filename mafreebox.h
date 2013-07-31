#ifndef MAFREEBOX_H
#define MAFREEBOX_H

#include <QObject>
#include <QtNetwork>



struct ApiServer
{
    QString deviceName;
    QString version;
    QString baseUrl;
    QString deviceType;
    QString mHostName;
    int port;
};

class MaFreeBox : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit MaFreeBox(QObject *parent = 0);

    //set
    void setHostName(const QString& host, int port = 80) ;
    void setPort(int port) ;
    void setApplicationToken(const QString& token);
    bool saveApplicationToken();
    bool loadApplicationToken(const QString& appId);

    //get
    const QString& hostName() const;
    int port() const;
    const QString& applicationToken() const;
    const QString& sessionToken() const;
    const QString& version() const;
    const QString& challenge() const;
    const QString& baseUrl() const;
    const QString& challenge() const;

    //request
    void requestVersion(bool asynchronous = false);
    void requestAuthorize(const QString& appId, const QString& appName,
                          const QString& appVersion, const QString& deviceName, bool asynchronous = false);
    void requestAuthorizeStatus(int trackId);
    void requestLogin(bool asynchronous = false);
    void requestSession(bool asynchronous = false);



signals:
    void error();
    void sessionExpired();



protected:
    void setBaseUrl(const QString& base);
    void setVersion(const QString& version);
    void setSessionToken(const QString& token);
    void setChallenge(const QString& challenge);

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
    QString mApiBaseUrl;
    QString mApiVersion;
    QString mApplicationToken;
    QString mSessionToken;
    QString mChallenge;


    
};

#endif // MAFREEBOX_H
