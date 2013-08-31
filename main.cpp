#include <QApplication>
#include "fsmainwindow.h"
#include "fstableview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("labsquare");
    QCoreApplication::setOrganizationDomain("labsquare.org");
    QCoreApplication::setApplicationName("Freebox");
    QCoreApplication::setApplicationVersion("beta");


    FSMainWindow w ;
    w.show();


//    FSTableView view;
//    view.show();
    
    return a.exec();
}
