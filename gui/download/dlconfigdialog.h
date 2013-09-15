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
#include "dlnewsgroupconfigwidget.h"
class DLConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DLConfigDialog(FbxAPI * fbx,QWidget *parent = 0);
    ~DLConfigDialog();
signals:
    
public slots:
    void setConfiguration(const DownloadConfiguration& configuration);

protected slots:
    void addTab(QWidget * widget);
    void acceptClicked(QAbstractButton * button);
private:
    QTabWidget* mTabWidget;
    QDialogButtonBox * mButtonBox;
    DLFeedConfigWidget * mFeedWidget;
    DLBtConfigWidget * mBtWidget;
    DLGeneralConfigWidget * mGeneralWidget;
    DLBlocklistConfigWidget * mBlocklistWidget;
    DLThrottlingConfigWidget * mThrottlingWidget;
    DLNewsGroupConfigWidget * mNewGroupWidget;
    FbxAPI * mFbx;

    
};

#endif // DLCONFIGDIALOG_H
