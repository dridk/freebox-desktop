#ifndef FSMAINWINDOW_H
#define FSMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mafreebox.h"
#include "headerpathwidget.h"
#include "filesystemmodel.h"
#include "stdmodel.h"
class FSMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FSMainWindow(QWidget *parent = 0);
    ~FSMainWindow();
    
signals:
    
public slots:
    void login();
    void authorize();
    void refresh();


protected slots:
    void authorizeReceived(const QString& token ,int trackId);
    void setRootIndex(const QModelIndex& index);
    void showError();

    

private:
    QTreeView * mTreeView;
    QTableView * mTableView;
    HeaderPathWidget * mHeaderWidget;
    QSplitter * mSplitter;
    QToolBar * mToolBar;
    MaFreeBox * mFbx;
     StdModel * model;
    FolderFilterProxyModel * mFolderModel;





};



#endif // FSMAINWINDOW_H
