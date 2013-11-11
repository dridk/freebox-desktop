#include "ctdetailview.h"

CTDetailView::CTDetailView(QWindow *parent) :
    QQuickView(parent)
{

    setWidth(600);
    rootContext()->setContextProperty("window",this);

    setSource(QUrl("qrc:///qml/contact/CTDetailView.qml"));


//    mDisplayNameLabel = new QLabel;
//    mFirstNameLabel   = new QLabel;
//    mLastNameLabel    = new QLabel;
//    mCompanyLabel     = new QLabel;
//    mAvatarLabel      = new QLabel;


//    mAvatarLabel->setFixedSize(128,128);
//    mAvatarLabel->setPixmap(QPixmap(":unknown.jpg"));




//    mDisplayNameLabel->setText("sacha schutz");
//    mFirstNameLabel->setText("schutz");
//    mLastNameLabel->setText("Schutz");
//    mCompanyLabel->setText("Labsquare");


//    QVBoxLayout * mainLayout = new QVBoxLayout;


//    QFormLayout * layout = new QFormLayout;

//    layout->addRow("<b>Nom d'affichage:</b>", mDisplayNameLabel);
//    QHBoxLayout * nameLayout = new QHBoxLayout;
//    nameLayout->setContentsMargins(0,0,0,0);
//    nameLayout->addWidget(mFirstNameLabel);
//    nameLayout->addWidget(mLastNameLabel);
//    layout->addRow("<b>Nom, Prenom:</b>", nameLayout);

//    layout->addRow("<b>Société:</b>", mCompanyLabel);


//    mainLayout->addLayout(layout);
//    setLayout(mainLayout);

//    setAutoFillBackground(true);
//    QPalette p( palette() );
//    p.setColor( QPalette::Window, Qt::white );
//    setPalette( p );
}
