#include <QApplication>
#include <QMessageBox>
#include "fsmainwindow.h"
#include "fstableview.h"
#include "dlmainwindow.h"
#include "launcherwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setOrganizationDomain("org.labsquare");
    QCoreApplication::setApplicationName("Freebox Desktop");
    QCoreApplication::setApplicationVersion("alpha test");

    FSMainWindow launcherWindow ;
    launcherWindow.show();

//    if (QCoreApplication::arguments().count() > 1)
//    {

//        QString path = QCoreApplication::arguments().value(1);
//        DLMainWindow downloadWindow ;

//        downloadWindow.addFile(path);
//        downloadWindow.show();

//    }

//    else {
////         LauncherWidget *  launcherWindow ;
////        launcherWindow->show();

//        launcherWindow.show();

//    }


//    DLMainWindow m;
//    m.show();

//    DLMainWindow f;
//    f.show();

    
    return a.exec();
}
