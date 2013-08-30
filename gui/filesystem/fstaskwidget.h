#ifndef FSTASKWIDGET_H
#define FSTASKWIDGET_H

#include <QWidget>
#include <QListView>
#include <QTimer>
#include <QTabWidget>
#include <QtWidgets>
#include <QMainWindow>
#include "mafreebox.h"
#include "fstaskdelegate.h"

#include "fsactiontaskmodel.h"
#include "fsdownloadtaskmodel.h"
#include "fsuploadtaskmodel.h"

class FSTaskWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit FSTaskWidget(MaFreeBox * fbx, QWidget *parent = 0);

    void setUpdateDelay(int ms);
    void start();
    void stop();
    int count();

protected slots:
  void clearTasks();
 void removeSelectedTasks();
 void computeTasksCount();

signals:
    void countChanged(int count);

private:
    QTimer * mTimer;
    QListView * mActionView;
    QListView * mDownloadView;
    QListView * mUploadView;
    FSActionTaskModel * mActionModel;
    FSDownloadTaskModel * mDownloadModel;
    FSUploadTaskModel * mUploadModel;
    FSTaskDelegate * mDelegate;
    MaFreeBox * mFbx;
    QTabWidget * mTabWidget;
    int updateDelay;

    
};

#endif // FSTASKWIDGET_H
