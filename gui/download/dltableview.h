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
    

    void contextMenuEvent(QContextMenuEvent *);
public slots:
    void showPropertyDialog();
    void setStatusFilter(const QString& status);

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
};

#endif // DLTABLEVIEW_H
