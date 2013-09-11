#ifndef DLMAINWINDOW_H
#define DLMAINWINDOW_H
#include "abstractmainwindow.h"
#include "dlmodel.h"
#include "dltableview.h"
#include "dlcategorywidget.h"
#include "dldetailwidget.h"
#include "dldelegate.h"
#include "dladddialog.h"
#include "dlconfigdialog.h"
#include "dlplotwidget.h"
#include <QTimer>s
class DLMainWindow : public AbstractMainWindow
{
    Q_OBJECT
public:
    explicit DLMainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void addUrl();
    void addFile();
    void addAdvancedUrl();
    void addDirectUrl();
    void showConfigDialog();

protected slots:
    void setStats(const DownloadStats& stats);
private:
    DLTableView * mView;
    DLCategoryWidget * mCategoryWidget;
    DLDetailWidget * mDetailWidget;
    QLineEdit * mDirectUrlEdit;
    DLPlotWidget * mPlotWidget;
    QTimer * mStatusTimer;

    
};

#endif // DLMAINWINDOW_H
