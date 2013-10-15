#ifndef DLGENERALCONFIGWIDGET_H
#define DLGENERALCONFIGWIDGET_H

#include <QtWidgets>
#include "fbxapi.h"
class DLGeneralConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLGeneralConfigWidget(FbxAPI * fbx,QWidget *parent = 0);
    ~DLGeneralConfigWidget();
signals:
    
public slots:
    void setConfig(const DownloadConfiguration& cfg);
    const DownloadConfiguration& config();
protected slots:
    void getWatchDir();
    void getDownloadDir();

private:
    DownloadConfiguration mCfg;
    QSpinBox  * mMaxDownloadingTasksSpinBox;
    QLineEdit * mDownloadDirEdit;
    QCheckBox * mUseWatchDirCheckBox;
    QLineEdit * mWatchDirEdit;
    QPushButton * mDownloadDirButton;
    QPushButton * mWatchDirButton;
    FbxAPI * mFbx;

    
};

#endif // DLGENERALCONFIGWIDGET_H
