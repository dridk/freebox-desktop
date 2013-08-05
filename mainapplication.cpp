#include "mainapplication.h"

MainApplication::MainApplication(QObject *parent) :
    QSystemTrayIcon(parent)
{

    setIcon(QIcon(":logo.png"));

    mMenu = new QMenu();


    mMenu->addAction("File System");
    mMenu->addAction("Configuration");
    mMenu->addAction("Exit");


    setContextMenu(mMenu);



}
