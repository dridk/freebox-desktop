#include "fstableview.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
FSTableView::FSTableView(QWidget *parent) :
    QTableView(parent)
{
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setEditTriggers(QAbstractItemView::EditKeyPressed);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
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

void FSTableView::dragEnterEvent(QDragEnterEvent *event)
{
    if (rootIndex().isValid()) {

    event->acceptProposedAction();
    viewport()->setStyleSheet("background-color:#ededed;background-image: url( :/drop.png);background-repeat:no-repeat;background-position:center center");
    hideColumn(0);
    hideColumn(1);
    hideColumn(2);
}


}

void FSTableView::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();





}

void FSTableView::dragLeaveEvent(QDragLeaveEvent *event)
{
    viewport()->setStyleSheet(QString());
    showColumn(0);
    showColumn(1);
    showColumn(2);
}

void FSTableView::dropEvent(QDropEvent *event)
{
    QStringList list;
    foreach (QUrl url, event->mimeData()->urls())
        list.append(url.path());

    emit filesAdded(list);


}



QMenu* FSTableView::createItemMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":disk.png"),"Télécharger")->setObjectName("download");
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
            fsModel()->mkdir(dialog.textValue(), rootIndex());
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
    //--------------------------------------------------------------------

    if (action->objectName() == QString("rename"))
    {

        edit(currentIndex());

    }
    //--------------------------------------------------------------------

    if (action->objectName() == QString("download"))
    {

        QFileDialog dialog;
        dialog.setWindowTitle("Télécharger");
        QString dirPath = dialog.getExistingDirectory(this);
        if (!dirPath.isEmpty()) {


            fsModel()->download(dirPath,currentIndex());

        }
    }
}
