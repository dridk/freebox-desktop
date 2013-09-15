#ifndef FSDIRVIEW_H
#define FSDIRVIEW_H

#include <QTreeView>
#include <QSortFilterProxyModel>
#include "fbxapi.h"
#include "fsmodel.h"
class FSDirView : public QTreeView
{
    Q_OBJECT
public:
    explicit FSDirView(FbxAPI * fbx,QWidget *parent = 0);
     QString currentPath();
public slots:
    void init(){mModel->init();}

private:
    QSortFilterProxyModel * mFilterModel;
    FSModel * mModel;
    
};

#endif // FSDIRVIEW_H
