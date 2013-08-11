#include "fstableview.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
FSTableView::FSTableView(QWidget *parent) :
    QTableView(parent)
{
    setContextMenuPolicy(Qt::DefaultContextMenu);

    mItemMenu = new QMenu(this);
    mMenu = new QMenu(this);
    mItemMenu->addAction(QIcon(":disk.png"),"Télécharger")->setObjectName("dl");
    mItemMenu->addSeparator();
    mItemMenu->addAction(QIcon(":folder_edit.png"),"Renommer")->setObjectName("rename");
    mItemMenu->addSeparator();
    mItemMenu->addAction(QIcon(":folder_add.png"),"Nouveau sous-dosser")->setObjectName("mkdir");
    mItemMenu->addAction(QIcon(":folder_delete.png"),"Supprimer")->setObjectName("delete");
    mItemMenu->addSeparator();
    mItemMenu->addAction(QIcon(":page_copy.png"),"Copier")->setObjectName("copy");
    mItemMenu->addAction(QIcon(":cut.png"),"Couper")->setObjectName("cut");

    connect(mItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(itemActionTriggered(QAction*)));


}

void FSTableView::contextMenuEvent(QContextMenuEvent * event)
{
    QModelIndex index = indexAt(event->pos());
    QMenu * menu = 0;
    if (index.isValid())
    {
        if (selectionModel()->selectedRows().count() > 1)
            menu = createSelectionMenu();
        else
            menu = createItemMenu();

    }
    else
        menu = createMenu();

    menu->move(event->globalPos());
    menu->exec();
    delete menu;

}

FSModel *FSTableView::fsModel()
{
    return qobject_cast<FSModel*>(model());
}

QMenu* FSTableView::createItemMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":disk.png"),"Télécharger")->setObjectName("dl");
    menu->addSeparator();
    menu->addAction(QIcon(":folder_edit.png"),"Renommer")->setObjectName("rename");
    menu->addSeparator();
    menu->addAction(QIcon(":folder.png"),"Nouveau sous-dosser")->setObjectName("mkdir");
    menu->addAction(QIcon(":folder_delete.png"),"Supprimer")->setObjectName("delete");
    menu->addSeparator();
    menu->addAction(QIcon(":page_copy.png"),"Copier")->setObjectName("copy");
    menu->addAction(QIcon(":cut.png"),"Couper")->setObjectName("move");

    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(itemActionTriggered(QAction*)));

    return menu;
}

QMenu* FSTableView::createMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":folder.png"),"Nouveau sous-dosser")->setObjectName("mkdir");
    menu->addSeparator();
    menu->addAction(QIcon(":folder_add.png"),"Uploader un fichier dans ce dossier")->setObjectName("upload");

    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(itemActionTriggered(QAction*)));

    return menu;
}

QMenu* FSTableView::createSelectionMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":folder_delete.png"),"Supprimer")->setObjectName("delete");
    menu->addSeparator();
    menu->addAction(QIcon(":page_copy.png"),"Copier")->setObjectName("copy");
    menu->addAction(QIcon(":cut.png"),"Couper")->setObjectName("move");

    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(itemActionTriggered(QAction*)));

    return menu;
}


void FSTableView::itemActionTriggered(QAction *action)
{

    if (action->objectName() == QString("mkdir"))
    {
        QInputDialog dialog;
        dialog.setLabelText("Nom du nouveau dossier:");
        dialog.setWindowTitle("Nouveau dossier");
        dialog.setInputMode(QInputDialog::TextInput);

        if (dialog.exec() == QDialog::Accepted) {
            fsModel()->mkdir(dialog.textValue(), currentIndex());
        }
    }
    //--------------------------------------------------------------------
    if (action->objectName() == QString("delete"))
    {
        qDebug()<<"receive from "<<sender()->objectName();
        QMessageBox box;
        box.setWindowTitle("Suppression");
        box.setText("Etes-vous sûr de vouloir supprimer ce(s) fichier(s) ?");
        box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);


        if (box.exec() == QMessageBox::Yes) {
            qDebug()<<"Yes;";
            QModelIndexList list = selectionModel()->selectedRows();
            fsModel()->remove(list);

        }

    }


    //--------------------------------------------------------------------
    if (action->objectName() == QString("copy"))
    {


    }
    //--------------------------------------------------------------------
    if (action->objectName() == QString("past"))
    {


    }

}
