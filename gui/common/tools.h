#ifndef TOOLS_H
#define TOOLS_H
#include <QtCore>
class Tools
{
public:
    Tools();

    static QString humanSize(double size);
    static QString pathFrom64(const QString& base64);
    static QString pathTo64(const QString& path);
    static QString fileIcon(const QString& filename);
};

#endif // TOOLS_H
