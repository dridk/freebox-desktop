#ifndef DLTHROTTLINGCONFIGWIDGET_H
#define DLTHROTTLINGCONFIGWIDGET_H

#include <QtWidgets>
#include "dlscheduletablewidget.h"
#include "fbxapi.h"
class DLThrottlingConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLThrottlingConfigWidget(QWidget *parent = 0);

    void setConfig(const DlThrottlingConfig& cfg);
    const DlThrottlingConfig& config();
    


protected slots:
    void setCurrentScheduleType(int id);

private:
    DlThrottlingConfig mCfg;
    QSpinBox* mNormalDLSpinBox;
    QSpinBox* mNormalULSpinBox;
    QSpinBox* mSlowDLSpinBox;
    QSpinBox* mSlowULSpinBox;
    QRadioButton * mNormalModeButton;
    QRadioButton * mSlowModeButton;
    QRadioButton * mHibernateModeButton;
    QRadioButton * mScheduleModeButton;
    DLScheduleTableWidget * mScheduleTableWidget;
    QLabel * mLabel;
    QPushButton * mHibernateButton;
    QPushButton * mSlowButton;
    QPushButton * mNormalButton;
    QButtonGroup * mButtonsGroup;





};

#endif // DLTHROTTLINGCONFIGWIDGET_H
