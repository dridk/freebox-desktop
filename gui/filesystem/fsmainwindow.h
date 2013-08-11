#ifndef FSMAINWINDOW_H
#define FSMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mafreebox.h"
#include "fspathtoolbar.h"
#include "fstableview.h"
#include "fstreeview.h"
#include "abstractmainwindow.h"
#include "fsmodel.h"

class FSMainWindow : public AbstractMainWindow
{
    Q_OBJECT
public:
    explicit FSMainWindow(QWidget *parent = 0);
    ~FSMainWindow();
    
signals:
    
public slots:
    void refresh();
    void mkdir();
    void upload();


protected slots:
    void setRootIndex(const QModelIndex& index);


    

private:
    FSTreeView * mTreeView;
    FSTableView * mTableView;
    FSPathToolBar * mHeaderWidget;
    QSplitter * mSplitter;
    QToolBar * mToolBar;
    QSortFilterProxyModel * mFolderModel;
    FSModel * mModel;



};



#endif // FSMAINWINDOW_H
