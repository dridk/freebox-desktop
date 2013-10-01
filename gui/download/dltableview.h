#ifndef DLTABLEVIEW_H
#define DLTABLEVIEW_H

#include <QTableView>
#include <QContextMenuEvent>
#include <QMenu>
#include <QSortFilterProxyModel>

#include "fbxapi.h"
#include "dlmodel.h"
#include "dldelegate.h"
#include "dlpropertywidget.h"
class DLTableView : public QTableView
{
    Q_OBJECT
public:
    explicit DLTableView(FbxAPI * fbx,QWidget *parent = 0);
    
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent * event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *);
public slots:
    void showPropertyDialog();
    void setStatusFilter(const QString& status);
    void setAutoUpdate(bool enable);
    void suspendAll();
    void revivalAll();



protected slots:
    void setPropertyDialog();

    void setCurrentPause();
    void setCurrentRestart();
    void setCurrentRetry();
    void setCurrentRemove();
    void setCurrentErase();
    void setCurrentPriorityLow();
    void setCurrentPriorityNormal();
    void setCurrentPriorityHigh();


signals:

private:
    DLModel * mModel;
    DLDelegate * mDelegate;
    DLPropertyWidget * mPropertyWidget;
    QSortFilterProxyModel * mFilterModel;
    FbxAPI * mFbx;
    QStringList mDropUrls;

};

#endif // DLTABLEVIEW_H
