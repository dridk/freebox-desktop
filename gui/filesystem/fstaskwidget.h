#ifndef FSTASKWIDGET_H
#define FSTASKWIDGET_H

#include <QWidget>
#include <QListView>
#include <QTimer>
#include <QTabWidget>
#include "mafreebox.h"
#include "fstaskmodel.h"
#include "fstaskdelegate.h"
#include "fsdownloadmodel.h"

class FSTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FSTaskWidget(MaFreeBox * fbx, QWidget *parent = 0);

    void setUpdateDelay(int ms);
    void start();
    void stop();
    int count();

signals:
    void countChanged();

private:
    QTimer * mTimer;
    QListView * mView;
    FSTaskModel * mModel;
    FSDownloadModel * mDownloadModel;
    FSTaskDelegate * mDelegate;
    MaFreeBox * mFbx;
    QTabWidget * mTabWidget;
    int updateDelay;

    
};

#endif // FSTASKWIDGET_H
