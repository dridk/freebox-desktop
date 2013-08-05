#include <QApplication>
#include "fsmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setApplicationName("Freebox");


    FSMainWindow w ;

    w.show();


    
    return a.exec();
}
