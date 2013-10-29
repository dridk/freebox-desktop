#ifndef CTDETAILWIDGET_H
#define CTDETAILWIDGET_H

#include <QtWidgets>

class CTDetailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CTDetailWidget(QWidget *parent = 0);

signals:

public slots:

private:
QLabel * mDisplayNameLabel;
QLabel * mFirstNameLabel;
QLabel * mLastNameLabel;
QLabel * mCompanyLabel;




};

#endif // CTDETAILWIDGET_H
