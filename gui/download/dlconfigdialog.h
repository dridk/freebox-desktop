#ifndef DLCONFIGDIALOG_H
#define DLCONFIGDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "fbxapi.h"
#include "dlfeedconfigwidget.h"
#include "dlbtconfigwidget.h"
#include "dlgeneralconfigwidget.h"
#include "dlblocklistconfigwidget.h"
#include "dlthrottlingconfigwidget.h"
class DLConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DLConfigDialog(FbxAPI * fbx,QWidget *parent = 0);
    ~DLConfigDialog();
signals:
    
public slots:
    void setConfiguration(const DownloadConfiguration& configuration);


protected:
    void addTab(QWidget * widget);

private:
    QTabWidget* mTabWidget;
    QDialogButtonBox * mButtonBox;
    DLFeedConfigWidget * mFeedWidget;
    DLBtConfigWidget * mBtWidget;
    DLGeneralConfigWidget * mGeneralWidget;
    DLBlocklistConfigWidget * mBlocklistWidget;
    DLThrottlingConfigWidget * mThrottlingWidget;
    FbxAPI * mFbx;

    
};

#endif // DLCONFIGDIALOG_H
