#ifndef FSMAINWINDOW_H
#define FSMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mafreebox.h"
#include "headerpathwidget.h"
#include "filesystemmodel.h"
class FSMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FSMainWindow(QWidget *parent = 0);
    ~FSMainWindow();
    
signals:
    
public slots:
    void login();
    void showError();
    void authorize();
    void setRootIndex(const QModelIndex& index);


protected slots:
    void authorizeReceived(const QString& token ,int trackId);

    

private:
    QTreeView * mTreeView;
    QTableView * mTableView;
    HeaderPathWidget * mHeaderWidget;
    QSplitter * mSplitter;
    QToolBar * mToolBar;
    MaFreeBox * mFbx;
    FileSystemModel * mModel;
    FolderFilterProxyModel * mFolderModel;





};



#endif // FSMAINWINDOW_H
