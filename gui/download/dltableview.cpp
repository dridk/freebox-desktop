#include "dltableview.h"
#include <QDebug>
#include <QActionGroup>
#include <QHeaderView>
DLTableView::DLTableView(FbxAPI *fbx, QWidget *parent) :
    QTableView(parent)
{
    mModel = new DLModel(fbx);
    mDelegate = new DLDelegate;
    mPropertyWidget = new DLPropertyWidget;
    mPropertyWidget->setModel(mModel);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setModel(mModel);
    setItemDelegate(mDelegate);
    verticalHeader()->setDefaultSectionSize(20);
    setColumnWidth(2, 300);
    setColumnWidth(4, 200);
    hideColumn(10);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(2,QHeaderView::Interactive);
    horizontalHeader()->setSectionResizeMode(9,QHeaderView::Stretch);
    setAlternatingRowColors(true);

    connect(fbx,SIGNAL(loginSuccess()),mModel,SLOT(start()));


}

void DLTableView::contextMenuEvent(QContextMenuEvent * event)
{
    if (selectionModel()->selectedRows().isEmpty())
        return;


    QMenu menu;
    QFont font;font.setBold(true);
    menu.addAction(QIcon(),"Propriétés",this,SLOT(showPropertyDialog()))->setFont(font);
    menu.addSeparator();
    menu.addAction(QIcon(),"Reprendre");
    menu.addAction(QIcon(),"Réessayer");
    menu.addAction(QIcon(),"Pause");
    QAction * supprAction = menu.addAction(QIcon(),"Supprimer");
    QMenu supprMenu;
    supprMenu.addAction(QIcon(),"En conservant les fichiers");
    supprMenu.addAction(QIcon(),"En effacant les fichiers");
    supprAction->setMenu(&supprMenu);
    menu.addAction(supprAction);
    menu.addSeparator();

    QAction * priorAction = menu.addAction(QIcon(),"Changer la priorité réseau");
    QMenu priorMenu;

    QActionGroup priorityGroup(this);
    QAction *a = priorityGroup.addAction(QIcon(),"Haute");
    QAction *b = priorityGroup.addAction(QIcon(),"Normale");
    QAction *c = priorityGroup.addAction(QIcon(),"Faible");

    a->setCheckable(true);
    b->setCheckable(true);
    c->setCheckable(true);

    QModelIndex firstIndex = selectionModel()->selectedRows(5).first();
    qDebug()<<firstIndex.data().toString();
    if (firstIndex.data().toString() == "high")
        a->setChecked(true);
    if (firstIndex.data().toString() == "normal")
        b->setChecked(true);
    if (firstIndex.data().toString() == "low")
        c->setChecked(true);


    priorMenu.addActions(priorityGroup.actions());

    priorAction->setMenu(&priorMenu);
    menu.addAction(priorAction);


    menu.move(event->globalPos());
    menu.exec();

}

void DLTableView::showPropertyDialog()
{


    qDebug()<<"set data";
    mPropertyWidget->setModel(mModel);
    mPropertyWidget->setCurrentIndex(currentIndex());
    mPropertyWidget->show();



}

void DLTableView::setPropertyDialog()
{




}
