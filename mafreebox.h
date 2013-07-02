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
    void init();
    void authorize(const QString& appId, const QString& appName,
                   const QString& appVersion, const QString& deviceName);

    void login(const QString& appId, const QString& appVersion, const QString& password);

signals:
    void ready();
    void authorizedReceived(const QString& appToken);

protected slots:
    void initFinished();
    void authorizeFinished();

protected:
     QNetworkRequest createRequest(const QString& uri) const;

private:
    QString mHost;
    int mPort;
    QString mBaseUrl;
    QString mApiVersion;
    QString mDeviceType;
    QString mDeviceName;
    QString mAppToken;
    QString mTrackId;
    QNetworkAccessManager * mNetManager;
    
};

#endif // MAFREEBOX_H
