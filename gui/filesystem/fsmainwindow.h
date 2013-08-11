#ifndef FSMAINWINDOW_H
#define FSMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mafreebox.h"
#include "headerpathwidget.h"
#include "stdmodel.h"
#include "abstractmainwindow.h"

class FSMainWindow : public AbstractMainWindow
{
    Q_OBJECT
public:
    explicit FSMainWindow(QWidget *parent = 0);
    ~FSMainWindow();
    
signals:
    
public slots:
    void refresh();


protected slots:
    void setRootIndex(const QModelIndex& index);


    

private:
    QTreeView * mTreeView;
    QTableView * mTableView;
    HeaderPathWidget * mHeaderWidget;
    QSplitter * mSplitter;
    QToolBar * mToolBar;
    FileSystemModel * model;
    QSortFilterProxyModel * mFolderModel;





};



#endif // FSMAINWINDOW_H
