#ifndef FSTASKWIDGET_H
#define FSTASKWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QTimer>
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

private:
    QTimer * mTimer;
    QTableView * mView;
    FSTaskModel * mModel;
    FSDownloadModel * mDownloadModel;
    FSTaskDelegate * mDelegate;
    MaFreeBox * mFbx;
    int updateDelay;

    
};

#endif // FSTASKWIDGET_H
