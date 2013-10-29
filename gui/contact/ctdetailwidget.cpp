#include "ctdetailwidget.h"

CTDetailWidget::CTDetailWidget(QWidget *parent) :
    QWidget(parent)
{
    mDisplayNameLabel = new QLabel;
    mFirstNameLabel   = new QLabel;
    mLastNameLabel    = new QLabel;
    mCompanyLabel     = new QLabel;


    mDisplayNameLabel->setText("sacha schutz");
    mFirstNameLabel->setText("schutz");
    mLastNameLabel->setText("Schutz");
    mCompanyLabel->setText("Labsquare");


    QFormLayout * layout = new QFormLayout;

    layout->addRow("<b>Nom d'affichage:</b>", mDisplayNameLabel);
    QHBoxLayout * nameLayout = new QHBoxLayout;
    nameLayout->setContentsMargins(0,0,0,0);
    nameLayout->addWidget(mFirstNameLabel);
    nameLayout->addWidget(mLastNameLabel);
    layout->addRow("<b>Nom, Prenom:</b>", nameLayout);

    layout->addRow("<b>Société:</b>", mCompanyLabel);

    setLayout(layout);

    setAutoFillBackground(true);
    QPalette p( palette() );
    p.setColor( QPalette::Window, Qt::white );
    setPalette( p );
}
