#ifndef DLPROPERTYWIDGET_H
#define DLPROPERTYWIDGET_H

#include <QDialog>
#include <QtWidgets>
#include <QDialogButtonBox>
#include <QDataWidgetMapper>
#include "download.h"
class DLPropertyWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DLPropertyWidget(QWidget *parent = 0);
    void setCurrentIndex(const QModelIndex& index);
    void setModel(QAbstractItemModel * model);
    QDataWidgetMapper * mapper() {return mMapper;}

private:
    QDataWidgetMapper * mMapper;
    QLabel * mNameLabel;
    QLabel * mStatusLabel;
    QLabel * mCreatedTsLabel;
    QLabel * mSizeLabel;
    QLabel * mIoPriorityLabel;
    QLabel * mDownloadDirLabel;
    QLabel * mTxBytesLabel;
    QLabel * mRxBytesLabel;
    QLabel * mTxRateLabel;
    QLabel * mRxRateLabel;
    QLabel * mErrorLabel;
    QDialogButtonBox * mToolButton;

};

#endif // DLPROPERTYWIDGET_H
