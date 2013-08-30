#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{

    mPixLabel = new QLabel;
    mTextLabel= new QLabel;
    mCreditsButton = new QPushButton("Contributeurs");
    mLicenceButton = new QPushButton("Licence");
    mPixLabel->setPixmap(QPixmap(":about.png"));

    mPixLabel->setFrameShape(QFrame::Box);
    mPixLabel->setFrameShadow(QFrame::Sunken);

    QHBoxLayout * layoutBox = new QHBoxLayout;
    layoutBox->addWidget(mCreditsButton);
    layoutBox->addStretch();
    layoutBox->addWidget(mLicenceButton);

    QVBoxLayout * layout = new QVBoxLayout;
//    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(mPixLabel);

    layout->addWidget(mTextLabel);

    layout->addStretch();
    layout->addLayout(layoutBox);
//    layout->setSpacing(0);
    setLayout(layout);


    mTextLabel->setAlignment(Qt::AlignCenter);
    mTextLabel->setText(QString("%1\n\nversion: %2\nbuild: %3")
                        .arg(qApp->applicationName(),
                             qApp->applicationVersion(),
                             "crée par Sacha Schutz"
                             "f0cdc42116"
                             ));


    setWindowTitle("A propos...");


}
