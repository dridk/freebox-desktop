#ifndef DLPLOTWIDGET_H
#define DLPLOTWIDGET_H

#include <QtWidgets>
#include "qcustomplot.h"
class DLPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLPlotWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
QCustomPlot * mPlot;
    
};

#endif // DLPLOTWIDGET_H
