#include "mafreebox.h"
#include <QDebug>
#include <QJsonDocument>
#include <QSettings>
#include <QCryptographicHash>
MaFreeBox::MaFreeBox(QObject *parent) :
    QObject(parent)
{
    mNetManager = new QNetworkAccessManager(this);
    mHost = "mafreebox.free.fr";
    mPort = 80;

    QSettings settings;
    mAppToken   = settings.value("app_token").toString();
    mTrackId    = settings.value("track_id").toDouble();
    mChallenge  = settings.value("challenge").toString();

    qDebug()<<"app token "<<mAppToken;
    qDebug()<<"track ID  "<<mTrackId;
    qDebug()<<"challenge  "<<mChallenge;

}

void MaFreeBox::init()
{

    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://%1:%2/api_version").arg(mHost).arg(mPort)));
    connect(mNetManager->get(request),SIGNAL(finished()),this,SLOT(initFinished()));


}

void MaFreeBox::authorize(const QString &appId, const QString &appName, const QString &appVersion, const QString &deviceName)
{

    QJsonObject json;
    json.insert("app_id", appId);
    json.insert("app_name",appName);
    json.insert("app_version",appVersion);
    json.insert("device_name",deviceName);

    QNetworkRequest request = createRequest("login/authorize");

    QNetworkReply * reply = mNetManager->post(request,QJsonDocument(json).toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(authorizeFinished()));

}

void MaFreeBox::authorizeProgress()
{

    QNetworkRequest request = createRequest(QString("login/authorize/%1").arg(mTrackId));
    connect(mNetManager->get(request),SIGNAL(finished()),this,SLOT(authorizeProgressFinished()));

}

void MaFreeBox::login(const QString &appId, const QString &appVersion, const QString &password)
{

    qDebug()<<"login";


    QNetworkRequest request = createRequest("login");
    QNetworkReply * reply = mNetManager->get(request);

    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));

    loop.exec();

    mChallenge = QJsonDocument::fromJson(reply->readAll()).object().value("result").toObject().value("challenge").toString();

    qDebug()<<mChallenge;
    QJsonObject json;
    json.insert("app_id", appId);
    json.insert("app_version",appVersion);
    json.insert("password",hmacSha1(mAppToken.toUtf8(),mChallenge.toUtf8()));

    QJsonDocument doc(json);

    QNetworkReply * replySession =
            mNetManager->post(createRequest("login/session"),doc.toJson());

    connect(replySession,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();


    qDebug()<<replySession->readAll();




}

void MaFreeBox::setHostName(const QString &host)
{
    mHost = host;
}

void MaFreeBox::setPort(int port)
{
    mPort = port;
}

const QString &MaFreeBox::appToken() const
{
    return mAppToken;
}

void MaFreeBox::initFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply->error()) {

        QJsonDocument doc =  QJsonDocument::fromJson(reply->readAll());

        mApiVersion =  doc.object().value("api_version").toString();
        mDeviceType =  doc.object().value("device_type").toString();
        mBaseUrl    =  doc.object().value("api_base_url").toString();
        mDeviceName =  doc.object().value("device_name").toString();
        emit ready();
    }
}

void MaFreeBox::authorizeFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());


        QJsonDocument doc =  QJsonDocument::fromJson(reply->readAll());
        mAppToken = doc.object().value("result").toObject().value("app_token").toString();
        mTrackId  =  doc.object().value("result").toObject().value("track_id").toDouble();
        QSettings settings; // save token as settings file ...
        settings.setValue("app_token", mAppToken);
        settings.setValue("track_id", mTrackId);

       // qDebug()<<doc.toJson();
        qDebug()<<"app token "<<mAppToken;
        qDebug()<<"track id  "<<mTrackId;

        emit authorizedReceived(mAppToken,mTrackId);


}

void MaFreeBox::authorizeProgressFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

        QJsonDocument doc =  QJsonDocument::fromJson(reply->readAll());
        mChallenge       = doc.object().value("result").toObject().value("challenge").toString();
        mAuthorizeStatus = doc.object().value("result").toObject().value("status").toString();

        QSettings settings; // save token as settings file ...
        settings.setValue("challenge", mChallenge);
        settings.setValue("status", mAuthorizeStatus);

        qDebug()<<"challenge "<<mChallenge;
        qDebug()<<" status "<<mAuthorizeStatus;

}

QNetworkRequest MaFreeBox::createRequest(const QString& uri) const
{


    //convertion du string 1.0 en v1. Soit "v" + integer. Ca suppose que 1.1 => v1
    int version = qRound(mApiVersion.toDouble());

    QString url = QString("http://%1:%2%3v%4/%5")
            .arg(mHost).arg(mPort).arg(mBaseUrl).arg(version).arg(uri);



    return QNetworkRequest(QUrl(url));

}

QString MaFreeBox::hmacSha1(QByteArray key, QByteArray baseString)
{
    qDebug()<<"key "<<key;
    qDebug()<<"val "<<baseString;

    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "\"
    // ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }

    // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed.toBase64();
}
