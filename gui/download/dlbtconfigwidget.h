#ifndef DLBTCONFIGWIDGET_H
#define DLBTCONFIGWIDGET_H

#include <QtWidgets>
#include "download.h" // DlBtConfig
class DLBtConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLBtConfigWidget(QWidget *parent = 0);
    ~DLBtConfigWidget();
signals:
    
public slots:
    void setConfig(const DlBtConfig& cfg);
    const DlBtConfig& config() ;


private:
    DlBtConfig mCfg;
    QSpinBox * mMaxPeersSpinBox;
    QDoubleSpinBox * mStopRatioSpinBox;
    QComboBox * mCryptoSupportComboBox;
    QCheckBox * mEnableDhtCheckBox;
    QCheckBox * mEnablePexCheckBox;
    QSpinBox * mAnnounceTimeoutSpinBox;

    
};

#endif // DLBTCONFIGWIDGET_H
