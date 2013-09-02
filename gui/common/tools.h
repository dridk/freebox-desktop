#ifndef TOOLS_H
#define TOOLS_H
#include <QtCore>
class Tools
{
public:
    Tools();

    static QString humanSize(double size);
    static QString pathFrom64(const QString& base64);

};

#endif // TOOLS_H
