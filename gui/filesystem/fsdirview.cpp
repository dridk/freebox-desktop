#include "fsdirview.h"

FSDirView::FSDirView(FbxAPI *fbx, QWidget *parent) :
    QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::EditKeyPressed);

    mModel = new FSModel(fbx);
    mFilterModel = new QSortFilterProxyModel;
    mFilterModel->setSourceModel(mModel);
    mFilterModel->setFilterKeyColumn(0);
    mFilterModel->setFilterRole(FSModel::IsDirRole);
    mFilterModel->setFilterFixedString("true");

    setModel(mFilterModel);
    setAnimated(true);

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);
    setCurrentIndex(QModelIndex());
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(setCurrentIndex(QModelIndex)));

}

QString FSDirView::currentPath()
{
    if (currentIndex().isValid())
        return mModel->currentPath(mFilterModel->mapToSource(currentIndex()));
    else
        return QString();

}
