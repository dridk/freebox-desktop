#include <QApplication>
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


    LauncherWidget w ;
    w.show();


    
    return a.exec();
}
