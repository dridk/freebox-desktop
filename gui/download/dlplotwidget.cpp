#include "dlplotwidget.h"
#include <QVBoxLayout>
DLPlotWidget::DLPlotWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout * layout = new QVBoxLayout;
    mPlot = new QCustomPlot;
    mPlot->addGraph();
    mPlot->plotLayout()->setVisible(false);
    layout->addWidget(mPlot);

    setLayout(layout);

}
