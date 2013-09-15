#include "dldetailwidget.h"

DLDetailWidget::DLDetailWidget(QWidget *parent) :
    QTabWidget(parent)
{

    addTab(new QListView,"Fichiers");
    addTab(new QListView,"Journal");
    addTab(new QListView,"Traqueurs");
    addTab(new QListView,"Pairs");


}
