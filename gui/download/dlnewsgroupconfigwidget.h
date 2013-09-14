#ifndef DLNEWSGROUPCONFIGWIDGET_H
#define DLNEWSGROUPCONFIGWIDGET_H

#include <QtWidgets>
#include "download.h"
class DLNewsGroupConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLNewsGroupConfigWidget(QWidget *parent = 0);
    ~DLNewsGroupConfigWidget();
    void setConfig(const DlNewsConfig& cfg);
    const DlNewsConfig& config();

signals:
    
private:
    DlNewsConfig mCfg;
    QLineEdit* mServerEdit;
    QSpinBox*  mPortSpinBox;
    QCheckBox* mSslCheckBox;
    QSpinBox * mNThtreadsSpinBox;
    QLineEdit* mUserEdit;
    QLineEdit* mPasswordEdit;
    QCheckBox* mLazyPar2CheckBox;
    QCheckBox* mAutoRepairCheckBox;
    QCheckBox* mAutoExtractCheckBox;
    QCheckBox* mEraseTmpCheckBox;



    
};

#endif // DLNEWSGROUPCONFIGWIDGET_H
