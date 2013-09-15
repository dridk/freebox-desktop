#include "download.h"

Download::Download(FbxAPI *parent) :
    QObject(parent)
{
}

void Download::requestList()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest("downloads/"));

    connect(reply,SIGNAL(finished()),this,SLOT(requestListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestDownload(int id)
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/%1").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestDownloadFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestRemove(int id)
{
    QNetworkReply * reply = fbx()->deleteResource(fbx()->myCreateRequest(QString("downloads/%1").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestRemoveFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestErase(int id)
{
    QNetworkReply * reply = fbx()->deleteResource(fbx()->myCreateRequest(QString("downloads/%1/erase").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestEraseFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestUpdate(int id,const QString &p, const QString &s)
{
    QJsonObject json;
    json.insert("io_priority",p);
    json.insert("status",s);
    QJsonDocument doc(json);

    QNetworkReply * reply = fbx()->put(fbx()->myCreateRequest(QString("downloads/%1").arg(id)),
                                       doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestLog(int id)
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/%1/log").arg(id)));

    connect(reply,SIGNAL(finished()),this,SLOT(requestLogFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestStats()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/stats")));

    connect(reply,SIGNAL(finished()),this,SLOT(requestStatsFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestAdd(const QString &url, const QString &destination, const QString &username, const QString &password, const QString archivePassword)
{

    QStringList dataList;
    QString encodedUrl =QUrl::toPercentEncoding(url);
    dataList.append("download_url="+encodedUrl);

    if (!destination.isEmpty())
        dataList.append(QString("download_dir=%1").arg(destination));

    if (!username.isEmpty())
        dataList.append(QString("username=%1").arg(username));

    if (!password.isEmpty())
        dataList.append(QString("password=%1").arg(password));

    if (!archivePassword.isEmpty())
        dataList.append(QString("archive_password=%1").arg(archivePassword));


    QByteArray data = dataList.join("&").toUtf8();

    qDebug()<<data;

    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/add"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QNetworkReply * reply = fbx()->post(request,data);
    connect(reply,SIGNAL(finished()),this,SLOT(requestAddFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));




}

void Download::requestAddFile(const QString &path, const QString &destination, const QString &archivePassword)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QNetworkRequest request = fbx()->myCreateRequest(QString("downloads/add"));

    QFile * file = new QFile(path);
    if (!file->open(QIODevice::ReadOnly)){
        qDebug()<<"cannot open file";
        delete file;
        return;
    }

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                       "application/x-bittorrent");

    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"download_dir\"")
                       .arg(destination));

    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"archive_password\"")
                       .arg(archivePassword));

    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"download_file\";filename=\"%1\"")
                       .arg(QFileInfo(path).fileName()));

    filePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
    multiPart->append(filePart);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data; boundary=" + multiPart->boundary());

    QNetworkReply *reply = fbx()->post(request, multiPart);
    connect(reply,SIGNAL(finished()),this,SLOT(requestAddFileFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

    multiPart->setParent(reply);

}

void Download::requestAddList(const QStringList &urls, const QString &destination, bool recursive, const QString &username, const QString &password, const QString archivePassword)
{

    QStringList dataList;
    QStringList encodedUrl;
    foreach (QString url, urls )
        encodedUrl.append(QUrl::toPercentEncoding(url));

    dataList.append("download_url="+encodedUrl.join("%0A"));

    if (!destination.isEmpty())
        dataList.append(QString("download_dir=%1").arg(destination));


    if (recursive)
        dataList.append(QString("recursive=%1").arg(recursive));

    if (!username.isEmpty())
        dataList.append(QString("username=%1").arg(username));

    if (!password.isEmpty())
        dataList.append(QString("password=%1").arg(password));

    if (!archivePassword.isEmpty())
        dataList.append(QString("archive_password=%1").arg(archivePassword));

    QByteArray data = dataList.join("&").toUtf8();


    qDebug()<<"ADD "<<data;

    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/add"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QNetworkReply * reply = fbx()->post(request,data);
    connect(reply,SIGNAL(finished()),this,SLOT(requestAddListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void Download::requestConfig()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/config/")));
    connect(reply,SIGNAL(finished()),this,SLOT(requestConfigFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void Download::requestUpdateConfig(const DownloadConfiguration &cfg)
{
    QJsonObject data;
    //-----------------------------------------------------------
    //--------general Settings
    data.insert("max_downloading_tasks", cfg.maxDownloadingTasks);
    data.insert("download_dir", cfg.downloadDir);
    data.insert("use_watch_dir", cfg.useWatchDir);
    data.insert("watch_dir", cfg.watchDir);
    //-----------------------------------------------------------
    //--------throttling Settings
    QJsonObject throttling;
    QJsonObject normal;
    normal.insert("rx_rate", cfg.throttling.normal.rxRate);
    normal.insert("tx_rate", cfg.throttling.normal.txRate);
    QJsonObject slow;
    slow.insert("rx_rate", cfg.throttling.slow.rxRate);
    slow.insert("tx_rate", cfg.throttling.slow.txRate);

    throttling.insert("normal", normal);
    throttling.insert("slow",slow );

    throttling.insert("mode", DlThrottlingConfig::modeToString(cfg.throttling.mode));

    QJsonArray schendule;
    foreach (DlThrottlingConfig::Type type, cfg.throttling.schedule)
        schendule.append(DlThrottlingConfig::typeToString(type));

    throttling.insert("schedule", schendule);
    data.insert("throttling", throttling);

    //----------------------------------------------------------
    //--------News Settings
    QJsonObject news;
    news.insert("server", cfg.news.server);
    news.insert("port", cfg.news.port);
    news.insert("ssl", cfg.news.ssl);
    news.insert("nthreads", cfg.news.nthreads);
    news.insert("user", cfg.news.user);
    news.insert("password", cfg.news.password);
    news.insert("lazy_par2", cfg.news.lazyPar2);
    news.insert("auto_repair", cfg.news.autoRepair);
    news.insert("auto_extract", cfg.news.autoExtract);
    news.insert("erase_tmp", cfg.news.eraseTmp);
    data.insert("news", news);
    //----------------------------------------------------------
    //--------BlockList Settings
    QJsonObject blocklist;
    blocklist.insert("sources", QJsonValue::fromVariant(cfg.blocklist.sources));
    data.insert("blocklist",blocklist);



    //----------------------------------------------------------
    //--------Bt Settings
    QJsonObject bt;
    bt.insert("max_peers", cfg.bt.maxPeers);
    bt.insert("stop_ratio", cfg.bt.stopRatio);
    bt.insert("crypto_support", DlBtConfig::typeToString(cfg.bt.cryptoSupport));
    bt.insert("enable_dht", cfg.bt.enableDht);
    bt.insert("enable_pex", cfg.bt.enablePex);
    bt.insert("announce_timeout", cfg.bt.announceTimeout);
    //----------------------------------------------------------
    //--------feed feed
    QJsonObject feed;
    feed.insert("fetch_interval", cfg.feed.fetchInterval);
    feed.insert("max_items",  cfg.feed.maxItems);
    data.insert("feed", feed);
    //----------------------------------------------------------
    //--------CREATE REQUEST

    QJsonDocument json;
    json.setObject(data);

    qDebug()<<json.toJson();

    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/config/"));
    QNetworkReply * reply = fbx()->put(request,json.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestFeedListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));


}

void Download::requestFeedList()
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/feeds/")));
    connect(reply,SIGNAL(finished()),this,SLOT(requestFeedListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void Download::requestFeed(int id)
{
    QNetworkReply * reply = fbx()->get(fbx()->myCreateRequest(QString("downloads/feeds/%1").arg(id)));
    connect(reply,SIGNAL(finished()),this,SLOT(requestFeedFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void Download::requestAddFeed(const QString &url)
{
    QJsonObject json;
    json.insert("url", url);
    QJsonDocument doc(json);

    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/feeds/"));

    QNetworkReply * reply = fbx()->post(request, doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestAddFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void Download::requestDeleteFeed(int id)
{
    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/feeds/%1").arg(id));

    QNetworkReply * reply = fbx()->deleteResource(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestDeleteFeedFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestUpdateFeed(int id, bool autoDownload)
{

    QJsonObject json;
    json.insert("auto_download", autoDownload);
    QJsonDocument doc(json);

    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/feeds/%1").arg(id));

    QNetworkReply * reply = fbx()->put(request,doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateFeedItemFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestRefreshFeed(int id)
{
    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/feeds/%1/fetch").arg(id));

    QNetworkReply * reply = fbx()->post(request, QByteArray());
    connect(reply,SIGNAL(finished()),this,SLOT(requestRefreshFeedFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestRefreshAllFeed()
{
    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/feeds/fetch"));

    QNetworkReply * reply = fbx()->post(request, QByteArray());
    connect(reply,SIGNAL(finished()),this,SLOT(requestRefreshAllFeedFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));
}

void Download::requestFeedItemList(int feedId)
{
    QNetworkRequest request =fbx()->myCreateRequest(QString("downloads/feeds/%1/items/").arg(feedId));

    QNetworkReply * reply = fbx()->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(requestFeedItemListFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestUpdateFeedItem(int id, int feedId, bool isRead)
{
    QJsonObject json;
    json.insert("is_read", isRead);
    QJsonDocument doc(json);

    QNetworkRequest request =
            fbx()->myCreateRequest(QString("downloads/feeds/%1/items/%2").arg(feedId).arg(id));

    QNetworkReply * reply = fbx()->put(request,doc.toJson());
    connect(reply,SIGNAL(finished()),this,SLOT(requestUpdateFeedItemFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}

void Download::requestDownloadFeedItem(int id, int feedId)
{
    QNetworkRequest request =
            fbx()->myCreateRequest(QString("downloads/feeds/%1/items/%2").arg(feedId).arg(id));

    QNetworkReply * reply = fbx()->post(request,QByteArray());
    connect(reply,SIGNAL(finished()),this,SLOT(requestDownloadFeedItemFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));



}

void Download::requestMarkAllFeedRead(int feedId)
{

    QNetworkRequest request =
            fbx()->myCreateRequest(QString("downloads/feeds/%1/items/mark_all_as_read").arg(feedId));

    QNetworkReply * reply = fbx()->post(request,QByteArray());
    connect(reply,SIGNAL(finished()),this,SLOT(requestMarkAllFeedReadFinished()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),fbx(),SLOT(errorReceived(QNetworkReply::NetworkError)));

}


//======================== SLOT FINISHED ==============================


void Download::requestListFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    if(fbx()->parseResult(doc))
    {

        QList<DownloadTask> list;

        foreach (QJsonValue item,  doc.object().value("result").toArray())
        {
            DownloadTask task;
            task.rxBytes = item.toObject().value("rx_bytes").toDouble();
            task.txBytes = item.toObject().value("tx_bytes").toDouble();
            task.downloadDir = item.toObject().value("download_dir").toString();
            task.archivePassword = item.toObject().value("archive_password").toString();
            task.eta = QDateTime::fromTime_t(item.toObject().value("eta").toDouble());
            task.status = item.toObject().value("status").toString();
            task.ioPriority = item.toObject().value("io_priority").toString();
            task.size = item.toObject().value("size").toDouble();
            task.type = item.toObject().value("type").toString();
            task.error = item.toObject().value("error").toString();
            task.queuePos = item.toObject().value("queue_pos").toVariant().toInt();
            task.id = item.toObject().value("id").toVariant().toInt();
            task.createdTs = QDateTime::fromTime_t(item.toObject().value("created_ts").toDouble());
            task.txRate = item.toObject().value("tx_rate").toDouble();
            task.name = item.toObject().value("name").toString();
            task.rxPct = item.toObject().value("rx_pct").toDouble();
            task.rxRate = item.toObject().value("rx_rate").toDouble();
            task.txPct = item.toObject().value("tx_pct").toDouble();

            list.append(task);

        }


        emit listReceived(list);

    }



}

void Download::requestDownloadFinished()
{
}

void Download::requestRemoveFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        emit removeFinished();

    }
}

void Download::requestEraseFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        emit eraseFinished();

    }
}

void Download::requestUpdateFinished()
{
}

void Download::requestLogFinished()
{
}

void Download::requestStatsFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");

        qDebug()<<"CONFIGURATION "<<doc.toJson();

        DownloadStats cfg;

        cfg.throttlingRate.rxRate = item.toObject().value("rx_rate").toDouble();
        cfg.throttlingRate.txRate = item.toObject().value("tx_rate").toDouble();
        cfg.nbTasksStopped = item.toObject().value("nb_tasks_stopped").toDouble();
        cfg.nbTasksChecking = item.toObject().value("nb_tasks_checking").toDouble();
        cfg.nbTasksQueued = item.toObject().value("nb_tasks_queued").toDouble();
        cfg.nbTasksExtracting = item.toObject().value("nb_tasks_extracting").toDouble();
        cfg.nbTasksDone = item.toObject().value("nb_tasks_done").toDouble();
        cfg.nbTasksRepairing = item.toObject().value("nb_tasks_repairing").toDouble();
        cfg.throttlingMode = DlThrottlingConfig::modeFromString(item.toObject().value("throttling_is_scheduled").toString());

        cfg.nbTasksActive = item.toObject().value("nb_tasks_active").toDouble();
        cfg.nbTasksDownloading = item.toObject().value("nb_tasks_downloading").toDouble();
        cfg.nbTasks= item.toObject().value("nb_tasks").toDouble();
        cfg.nbTasksError = item.toObject().value("nb_tasks_error").toDouble();
        cfg.nbTasksStopping = item.toObject().value("nb_tasks_stopping").toDouble();
        cfg.nbRssItemsUnread = item.toObject().value("nb_rss_items_unread").toDouble();
        cfg.rxRate = item.toObject().value("rx_rate").toDouble();
        cfg.txRate= item.toObject().value("tx_rate").toDouble();
        cfg.nbRss= item.toObject().value("nb_rss").toDouble();

        emit statsReceived(cfg);

    }


}

void Download::requestAddFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        emit addFinished();

    }
}

void Download::requestAddFileFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        emit addFileFinished();
    }
}

void Download::requestAddListFinished()
{
}

void Download::requestConfigFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        QJsonValue item = doc.object().value("result");

        qDebug()<<"CONFIGURATION "<<doc.toJson();

        DownloadConfiguration cfg;

        cfg.useWatchDir = item.toObject().value("use_watch_dir").toBool();
        cfg.watchDir    = item.toObject().value("watch_dir").toString();
        cfg.downloadDir = item.toObject().value("download_dir").toString();
        cfg.maxDownloadingTasks = item.toObject().value("max_downloading_tasks").toVariant().toInt();


        cfg.feed.maxItems = item.toObject().value("feed").toObject().value("max_items").toDouble();
        cfg.feed.fetchInterval = item.toObject().value("feed").toObject().value("fetch_interval").toDouble();

        cfg.news.user = item.toObject().value("news").toObject().value("user").toString();
        //password is WRITE ONLY
        //cfg.news.password = item.toObject().value("news").toObject().value("password").toString();
        cfg.news.eraseTmp = item.toObject().value("news").toObject().value("erase_tmp").toBool();
        cfg.news.port = item.toObject().value("news").toObject().value("port").toDouble();
        cfg.news.nthreads = item.toObject().value("news").toObject().value("nthreads").toDouble();
        cfg.news.autoRepair = item.toObject().value("news").toObject().value("auto_repair").toBool();
        cfg.news.ssl = item.toObject().value("news").toObject().value("ssl").toBool();
        cfg.news.autoExtract = item.toObject().value("news").toObject().value("auto_extract").toBool();
        cfg.news.lazyPar2 = item.toObject().value("news").toObject().value("lazy_par2").toBool();
        cfg.news.server = item.toObject().value("news").toObject().value("server").toString();

        cfg.bt.maxPeers  = item.toObject().value("bt").toObject().value("max_peers").toDouble();
        cfg.bt.stopRatio = item.toObject().value("bt").toObject().value("stop_ratio").toDouble();
        cfg.bt.cryptoSupport = DlBtConfig::typeFromString(item.toObject().value("bt").toObject().value("crypto_support").toString());
        cfg.bt.announceTimeout = item.toObject().value("bt").toObject().value("announce_timeout").toDouble();
        cfg.bt.enableDht = item.toObject().value("bt").toObject().value("enable_dht").toBool();
        cfg.bt.enablePex = item.toObject().value("bt").toObject().value("enable_pex").toBool();



        cfg.throttling.normal.rxRate = item.toObject().value("throttling")
                .toObject().value("normal")
                .toObject().value("rx_rate").toDouble();

        cfg.throttling.normal.txRate = item.toObject().value("throttling")
                .toObject().value("normal")
                .toObject().value("tx_rate").toDouble();

        cfg.throttling.slow.rxRate = item.toObject().value("throttling")
                .toObject().value("slow")
                .toObject().value("rx_rate").toDouble();

        cfg.throttling.slow.txRate = item.toObject().value("throttling")
                .toObject().value("slow")
                .toObject().value("tx_rate").toDouble();


        cfg.throttling.mode = DlThrottlingConfig::modeFromString(item.toObject().value("throttling")
                                                                 .toObject().value("mode").toString());


        foreach(QJsonValue sc, item.toObject().value("throttling")
                .toObject().value("schedule").toArray())
        {

            cfg.throttling.schedule.append(DlThrottlingConfig::typeFromString(sc.toString()));

        }


        cfg.blocklist.sources = item.toObject().value("blocklist")
                .toObject().value("sources")
                .toVariant().toStringList();


        emit configReceived(cfg);

    }
}

void Download::requestUpdateConfigFinished()
{
    QNetworkReply * reply  = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if(fbx()->parseResult(doc))
    {
        emit updateConfigFinished();

    }

}

void Download::requestFeedListFinished()
{
}

void Download::requestFeedFinished()
{
}

void Download::requestAddFeedFinished()
{
}

void Download::requestDeleteFeedFinished()
{
}

void Download::requestUpdateFeedFinished()
{
}

void Download::requestRefreshFeedFinished()
{
}

void Download::requestRefreshAllFeedFinished()
{
}

void Download::requestFeedItemListFinished()
{
}

void Download::requestUpdateFeedItemFinished()
{
}

void Download::requestDownloadFeedItemFinished()
{
}

void Download::requestMarkAllFeedReadFinished()
{
}
