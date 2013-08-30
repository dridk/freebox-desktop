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
#include "fstaskwidget.h"

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
    void uploads(const QStringList& list);


protected slots:
    void setRootIndex(const QModelIndex& index);
    void showTaskWidget(bool show);
    void setTaskCount();


    

private:
    FSTreeView * mTreeView;
    FSTableView * mTableView;
    FSPathToolBar * mHeaderWidget;
    QSplitter * mSplitter;
    QToolBar * mToolBar;
    QSortFilterProxyModel * mFolderModel;
    FSModel * mModel;
    FSTaskWidget * mTaskWidget;
    QDockWidget * mTaskDockWidget;
    QAction * mMkdirAction;
    QAction * mUploadAction;
    QAction * mRefreshAction;
    QAction * mTaskAction;


};



#endif // FSMAINWINDOW_H
