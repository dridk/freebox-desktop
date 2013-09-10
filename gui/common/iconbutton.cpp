#include "iconbutton.h"

IconButton::IconButton(QWidget *parent) :
    QToolButton(parent)
{

    setFixedSize(64,64);
    setIcon(QIcon(":main_hp.png"));


    connect(this,SIGNAL(clicked()),this,SLOT(showListWidget()));



}

void IconButton::showListWidget()
{

    QDialog dialog(this);
    QListWidget * listWidget = new QListWidget;
    listWidget->setViewMode(QListView::IconMode);
    listWidget->addItem(new QListWidgetItem(QIcon(":main_hp.png"),""));
    listWidget->addItem(new QListWidgetItem(QIcon(":main_pc.png"),""));
    listWidget->addItem(new QListWidgetItem(QIcon(":main_nt.png"),""));
    listWidget->addItem(new QListWidgetItem(QIcon(":main_hp.png"),""));
    listWidget->addItem(new QListWidgetItem(QIcon(":main_hp.png"),""));

    dialog.setLayout(new QVBoxLayout);
    dialog.layout()->addWidget(listWidget);

    connect(listWidget,SIGNAL(clicked(QModelIndex)),
            &dialog,SLOT(close()));
    dialog.exec();


    setIcon(listWidget->currentItem()->icon());


}

