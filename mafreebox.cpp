#include "mafreebox.h"
#include <QDebug>
#include <QJsonDocument>
#include <QSettings>
#include <QCryptographicHash>
#include <QInputDialog>



MaFreeBox::MaFreeBox(QObject *parent) :
    QNetworkAccessManager(parent)
{
    mHostName = "mafreebox.free.fr";
    mPort = 80;
    //    mAppToken = "Cw0MVrumznvfZxn3xnGbKeg6afjVp+XTqptWeSraESzfxp/SAdZ9ML+zAvwNoPro";

    mApiInfo.version = "1.0";
    mApiInfo.baseUrl = "/api/";
    mRequestLoginAttempt = 0;

    // == alloc module
    mFileSystem = new FileSystem(this);


}

MaFreeBox::~MaFreeBox()
{
    delete mFileSystem;
}

void MaFreeBox::setHostName(const QString &host, int port)
{
    mHostName = host;
    mPort     = port;
}

void MaFreeBox::setApplicationToken(const QString &token)
{
    mApplicationToken = token;
}

void MaFreeBox::setApplicationId(const QString &id)
{
    mApplicationId = id;
}

bool MaFreeBox::saveApplicationToken()
{
    QSettings settings;
    settings.setValue(mApplicationId, qCompress(mApplicationToken.toUtf8()));
    return settings.contains(mApplicationId);
}

bool MaFreeBox::loadApplicationToken()
{
    QSettings settings;
    mApplicationToken = qUncompress(settings.value(mApplicationId).toByteArray());
    return settings.contains(mApplicationId);
}

void MaFreeBox::setBaseUrl(const QString &base)
{
    mApiInfo.baseUrl = base;
}

const QString &MaFreeBox::hostName() const
{
    return mHostName;
}

int MaFreeBox::port() const
{
    return mPort;
}

const QString &MaFreeBox::applicationToken() const
{
    return mApplicationToken;
}

const QString &MaFreeBox::sessionToken() const
{
    return mSessionToken;
}

const QString &MaFreeBox::baseUrl() const
{
    return mApiInfo.baseUrl;
}

const QString &MaFreeBox::challenge() const
{
    return mChallenge;
}

const QString &MaFreeBox::deviceName() const
{
    return mApiInfo.deviceName;
}

const QString &MaFreeBox::deviceType() const
{
    return mApiInfo.deviceType;
}

const QString &MaFreeBox::errorString() const
{
    return mErrorString;
}

const MaFreeBox::Error &MaFreeBox::error() const
{
    return mError;
}

const QStringList &MaFreeBox::permissions() const
{
    return mPermissions;
}


void MaFreeBox::requestApiInfo()
{
    // doesn't follow API url syntax
    QNetworkRequest request ;
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json; charset=utf-8"));
    request.setUrl(QUrl(QString("http://%1:%2/api_version").arg(mHostName).arg(mPort)));

    QNetworkReply * reply = get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestApiInfoFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void MaFreeBox::requestAuthorize(const QString &appId, const QString &appName, const QString &appVersion, const QString &deviceName)
{
    QJsonObject json;
    json.insert("app_id", appId);
    json.insert("app_name",appName);
    json.insert("app_version",appVersion);
    json.insert("device_name",deviceName);

    QNetworkRequest request = createRequest("login/authorize");
    QNetworkReply * reply = post(request,QJsonDocument(json).toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestAuthorizeFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void MaFreeBox::requestAuthorizeStatus(int trackId)
{
    QNetworkReply * reply = get(createRequest(QString("login/authorize/%1").arg(trackId)));
    connect(reply,SIGNAL(finished()),this,SLOT(requestAuthorizeStatusFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void MaFreeBox::requestLogin()
{
    qDebug()<<"request Login";
    QNetworkReply * reply = get(createRequest("login"));
    connect(reply,SIGNAL(finished()),this,SLOT(requestLoginFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void MaFreeBox::requestSession()
{
    QJsonObject json;
    json.insert("app_id", mApplicationId);
    json.insert("app_version",mApiInfo.version);
    json.insert("password",hmacSha1(mApplicationToken.toUtf8(),
                                    mChallenge.toUtf8()));
    QJsonDocument doc(json);

    QNetworkReply * reply = post(createRequest("login/session"), doc.toJson());

    connect(reply,SIGNAL(finished()),this,SLOT(requestSessionFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(errorReceived(QNetworkReply::NetworkError)));

    qDebug()<<"app Id " <<mApplicationId;
    qDebug()<<"challenge "<<mChallenge;
    qDebug()<<reply->url();
    qDebug()<<doc.toJson();



}
void MaFreeBox::requestApiInfoFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    mApiInfo.baseUrl = doc.object().value("api_base_url").toString();
    mApiInfo.deviceName = doc.object().value("device_name").toString();
    mApiInfo.version = doc.object().value("api_version").toString();
    mApiInfo.deviceType = doc.object().value("device_type").toString();

    emit apiInfoChanged();


}

void MaFreeBox::requestAuthorizeFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc =  QJsonDocument::fromJson(reply->readAll());
    if (parseResult(doc))
    {
        QString appToken     = doc.object().value("result").toObject().value("app_token").toString();
        int trackId      = doc.object().value("result").toObject().value("track_id").toDouble();

        emit authorizeReceived(appToken, trackId);
    }
}

void MaFreeBox::requestAuthorizeStatusFinished()
{
}

void MaFreeBox::requestLoginFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(parseResult(doc)) {
        requestSession();
    }


}

void MaFreeBox::requestSessionFinished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if (parseResult(doc))
    {
        mRequestLoginAttempt = 0;
        mSessionToken = doc.object().value("result").toObject().value("session_token").toString();
        mPermissions = doc.object().value("result").toObject().value("permissions").toObject().keys();

        emit sessionReceived();
    }
}
QString MaFreeBox::hmacSha1(QByteArray key, QByteArray baseString)
{
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
    return hashed.toHex();
}

QNetworkRequest MaFreeBox:: createRequest(const QString &uri) const
{
    //convertion du string 1.0 en v1. Soit "v" + integer. Ca suppose que 1.1 => v1
    int version = qRound(mApiInfo.version.toDouble());

    QString url = QString("http://%1:%2%3v%4/%5")
            .arg(mHostName).arg(mPort).arg(mApiInfo.baseUrl)
            .arg(version).arg(uri);

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("X-Fbx-App-Auth", mSessionToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json; charset=utf-8"));

    qDebug()<<request.url();

    return request;
}

bool MaFreeBox::parseResult(const QJsonDocument &doc)
{

    if (!doc.object().value("success").toBool()){

        if (doc.object().contains("error_code")) {
            QString code = doc.object().value("error_code").toString();
            QString msg  = doc.object().value("msg").toString();
            sendError(msg, UnknownError);
        }
        return false;
    }

    QJsonObject result = doc.object().value("result").toObject();

    if (result.contains("challenge"))
        mChallenge = result.value("challenge").toString();
    return true;

}

void MaFreeBox::sendError(const QString &message, MaFreeBox::Error code)
{
    mError = code;
    mErrorString = message;
    emit error(mErrorString, mError);

}


void MaFreeBox::errorReceived(QNetworkReply::NetworkError errCode)
{
    qDebug()<<"ERROR "<< errCode;
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    if (reply)
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QString code = doc.object().value("error_code").toString();
        mErrorString = doc.object().value("msg").toString();
        mError = UnknownError; // need to be compute

        if ( code == "invalid_token") {
            mRequestLoginAttempt++;
            qDebug()<<mRequestLoginAttempt;

            if (mRequestLoginAttempt < 5)
                requestLogin();
            else {
                mRequestLoginAttempt = 0;
                sendError(mErrorString, mError);

            }

        }

        else
            sendError(mErrorString, mError);




    }

}



