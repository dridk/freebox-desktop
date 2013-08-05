#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include "mafreebox.h"
class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(MaFreeBox *parent = 0);
    
signals:
    
public slots:
    
};

#endif // DOWNLOAD_H
