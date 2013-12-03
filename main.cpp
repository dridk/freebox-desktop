#include <QApplication>
#include <QMessageBox>
#include <QWindow>
#include "fsmainwindow.h"
#include "fstableview.h"
#include "dlmainwindow.h"
#include "clmainwindow.h"
#include "ctmainwindow.h"
#include "launcherwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setOrganizationDomain("org.labsquare");
    QCoreApplication::setApplicationName("Freebox Desktop");
    QCoreApplication::setApplicationVersion("beta 0.1.1");




    if (QCoreApplication::arguments().count() > 1)
    {

        QString path = QCoreApplication::arguments().value(1);
        DLMainWindow downloadWindow ;
        downloadWindow.addFile(path);
        downloadWindow.show();
        return a.exec();

    }

    else {
        LauncherWidget w;
        w.show();
        return a.exec();

    }


//    CTMainWindow w;
//    w.show();

    return a.exec();

//    DLMainWindow m;
//    m.show();

//    DLMainWindow f;
//    f.show();

    
}
