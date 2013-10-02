#include "tools.h"
#include <QMimeDatabase>
Tools::Tools()
{
}

QString Tools::humanSize(double size)
{
    float num = size;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(num >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        num /= 1024.0;
    }
    return QString().setNum(num,'f',2)+" "+unit;

}

QString Tools::pathFrom64(const QString &base64)
{

    return QString(QByteArray::fromBase64(base64.toUtf8()));

}

QString Tools::pathTo64(const QString &path)
{
    return QString(path.toUtf8().toBase64());
}

QString Tools::fileIcon(const QString &filename)
{
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForUrl(filename);
    //récupere l'icone.
    QString icon = mime.iconName().replace("-","_").replace("/","_");
    return QString(":mime/%1.png").arg(icon);
}
