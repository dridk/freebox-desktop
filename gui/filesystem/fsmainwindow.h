#ifndef FSMAINWINDOW_H
#define FSMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "fbxapi.h"
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
    void init();


protected slots:
    void setRootIndex(const QModelIndex& index = QModelIndex());
    void showTaskWidget(bool show);
    void setTaskCount(int count = 0);


    

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

    //statusBar


};



#endif // FSMAINWINDOW_H
