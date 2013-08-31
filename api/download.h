#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include "fbxapi.h"
class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(FbxAPI *parent = 0);
    
signals:
    
public slots:
    
};

#endif // DOWNLOAD_H
