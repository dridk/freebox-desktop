#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QSystemTrayIcon>
#include <QMenu>
class MainApplication : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit MainApplication(QObject *parent = 0);
    

private:
    QMenu * mMenu;
    
};

#endif // MAINAPPLICATION_H
