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
    if (rootIndex().isValid() && event->mimeData()->hasUrls()) {
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
    Q_UNUSED(event);
    viewport()->setStyleSheet(QString());
    showColumn(0);
    showColumn(1);
    showColumn(2);
}

void FSTableView::dropEvent(QDropEvent *event)
{
    QStringList list;
    foreach (QUrl url, event->mimeData()->urls())
        list.append(url.toLocalFile());

    qDebug()<<list;
    emit filesAdded(list);

    viewport()->setStyleSheet(QString());
    showColumn(0);
    showColumn(1);
    showColumn(2);


}

void FSTableView::remove()
{
    QMessageBox box;
    box.setWindowTitle("Suppression");
    box.setText("Etes-vous sûr de vouloir supprimer ce(s) fichier(s) ?");
    box.setInformativeText("Les fichiers seront definitevement effacer de la freebox, sans possibilité de récuperation");
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    box.setIcon(QMessageBox::Warning);
    if (box.exec() == QMessageBox::Yes) {
        qDebug()<<"Yes;";
        QModelIndexList list = selectionModel()->selectedRows();
        fsModel()->remove(list);
    }
}

void FSTableView::mkdir()
{
    QInputDialog dialog;
    dialog.setLabelText("Nom du nouveau dossier:");
    dialog.setWindowTitle("Nouveau dossier");
    dialog.setInputMode(QInputDialog::TextInput);

    if (dialog.exec() == QDialog::Accepted) {
        fsModel()->mkdir(dialog.textValue(), rootIndex());
    }
}



void FSTableView::download()
{
    QFileDialog dialog;
    dialog.setWindowTitle("Télécharger");
    QString dirPath = dialog.getExistingDirectory(this);
    if (!dirPath.isEmpty())
        fsModel()->download(dirPath,currentIndex());
}

void FSTableView::rename()
{
        edit(currentIndex());
}

QMenu* FSTableView::createItemMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":disk.png"),"Télécharger",this,SLOT(download()));
    menu->addSeparator();
    menu->addAction(QIcon(":folder_edit.png"),"Renommer",this,SLOT(rename()));
    menu->addSeparator();
    menu->addAction(QIcon(":folder.png"),"Nouveau sous-dosser",this,SLOT(mkdir()));
    menu->addAction(QIcon(":folder_delete.png"),"Supprimer",this,SLOT(remove()));
    menu->addSeparator();
    menu->addAction(QIcon(":page_copy.png"),"Copier");
    menu->addAction(QIcon(":cut.png"),"Couper");
    return menu;
}

QMenu* FSTableView::createMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":folder.png"),"Nouveau sous-dosser",this,SLOT(mkdir()));

    return menu;
}

QMenu* FSTableView::createSelectionMenu()
{
    QMenu * menu = new QMenu;
    menu->addAction(QIcon(":folder_delete.png"),"Supprimer",this,SLOT(remove()));
    menu->addSeparator();
    menu->addAction(QIcon(":page_copy.png"),"Copier");
    menu->addAction(QIcon(":cut.png"),"Couper");
    return menu;
}

void FSTableView::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Delete)
        remove();

    QTableView::keyPressEvent(event);

}

