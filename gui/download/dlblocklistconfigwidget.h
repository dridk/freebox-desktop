#ifndef DLBLOCKLISTCONFIGWIDGET_H
#define DLBLOCKLISTCONFIGWIDGET_H

#include <QtWidgets>
#include "fbxapi.h"
class DLBlocklistConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLBlocklistConfigWidget(QWidget *parent = 0);
    ~DLBlocklistConfigWidget();
signals:
    
public slots:
    void setConfig(const DlBlockListConfig& cfg);
    const DlBlockListConfig& config();
private:
    DlBlockListConfig mCfg;
    QPlainTextEdit * mTextEdit;
    QLabel * mLabel;
    QLabel * mNoteLabel;
    
};

#endif // DLBLOCKLISTCONFIGWIDGET_H
