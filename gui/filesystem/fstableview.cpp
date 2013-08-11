#include "fstableview.h"
#include <QDebug>
FSTableView::FSTableView(QWidget *parent) :
    QTableView(parent)
{
    setContextMenuPolicy(Qt::DefaultContextMenu);


}

void FSTableView::contextMenuEvent(QContextMenuEvent * event)
{
    qDebug()<<"show";

//    if (indexAt(event->pos())) {
//            QMenu menu;
//            menu.addAction(QIcon(),"Télécharger");
//            menu.addSeparator();
//            menu.addAction(QIcon(),"Renommer");
//            menu.addSeparator();
//            menu.addAction(QIcon(),"Nouveau sous-dosser");
//            menu.addAction(QIcon(),"Supprimer");
//            menu.addSeparator();
//            menu.addAction(QIcon(),"Copier");
//            menu.addAction(QIcon(),"Couper");
//            //    menu.addSeparator();

//            menu.move(event->globalPos());
//            menu.exec();
//}


}

