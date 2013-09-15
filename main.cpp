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

    LauncherWidget launcherWindow ;
    DLMainWindow   downloadWindow ;

    if (QCoreApplication::arguments().count() > 1)
    {
        QString path = QCoreApplication::arguments().value(1);

        downloadWindow.addFile(path);
        downloadWindow.show();

    }

    else
        launcherWindow.show();




    
    return a.exec();
}
