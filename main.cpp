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
    QCoreApplication::setApplicationVersion("beta");

//    DLMainWindow  * downloadWindow ;
    LauncherWidget launcherWindow ;


    if (QCoreApplication::arguments().count() > 1)
    {

//        QString path = QCoreApplication::arguments().value(1);
//        downloadWindow->addFile(path);
//        downloadWindow->show();

    }

    else {
//         LauncherWidget *  launcherWindow ;
//        launcherWindow->show();

        launcherWindow.show();

    }



    
    return a.exec();
}
