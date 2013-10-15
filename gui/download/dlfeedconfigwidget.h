#ifndef DLFEEDCONFIGWIDGET_H
#define DLFEEDCONFIGWIDGET_H

#include <QtWidgets>
#include "fbxapi.h"
class DLFeedConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLFeedConfigWidget(QWidget *parent = 0);
    ~DLFeedConfigWidget();
    
signals:
    
public slots:
    void setConfig(const DlFeedConfig& cfg);
    const DlFeedConfig& config();
private:
    DlFeedConfig mCfg;
    QSpinBox* mFetchIntervalBox;
    QSpinBox* mMaxItemsBox;
    
};

#endif // DLFEEDCONFIGWIDGET_H
