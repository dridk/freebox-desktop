#include "tools.h"

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
