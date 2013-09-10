#include "dlfeedconfigwidget.h"
DLFeedConfigWidget::DLFeedConfigWidget(QWidget *parent) :
    QWidget(parent)
{

    QFormLayout * mainLayout = new QFormLayout;
    mFetchIntervalBox = new QSpinBox;
    mMaxItemsBox      = new QSpinBox;

    mFetchIntervalBox->setRange(0,10000);
    mFetchIntervalBox->setToolTip("Période de mise à jour automatique des flux RSS");

    mMaxItemsBox->setRange(0,120);
    mMaxItemsBox->setToolTip("Nombre maximum d'entrées à conserver pour chaque flux RSS");

    mainLayout->addRow("Période de mise à jour (minutes) :", mFetchIntervalBox);
    mainLayout->addRow("Nombre d'éléments à conserver :", mMaxItemsBox);


    setWindowTitle("Feeds");
    setLayout(mainLayout);
}

DLFeedConfigWidget::~DLFeedConfigWidget()
{
    delete mFetchIntervalBox;
    delete mMaxItemsBox;
}

void DLFeedConfigWidget::setFetchInterval(int interval)
{
    mFetchIntervalBox->setValue(interval);
}

void DLFeedConfigWidget::setMaxItems(int max)
{
    mMaxItemsBox->setValue(max);
}
