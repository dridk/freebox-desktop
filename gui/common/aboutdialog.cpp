#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{

    mTabWidget = new QTabWidget;
    mAboutHeader= new AboutHeader;
    mContributorTextEdit = new QTextEdit;
    mLicenceTextEdit = new QTextEdit;
    mView = new QWebView;
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    mLicenceTextEdit->setReadOnly(true);
    mContributorTextEdit->setReadOnly(true);

    QFile file(":license.html");
    file.open(QIODevice::ReadOnly);
    mLicenceTextEdit->setText(file.readAll());
    file.close();

    QFile file2(":contributor.html");
    file2.open(QIODevice::ReadOnly);
    mContributorTextEdit->setText(file2.readAll());
    file2.close();


    layout->addWidget(mAboutHeader);
    layout->addWidget(mTabWidget);

    mTabWidget->addTab(mContributorTextEdit,"Contributeur");
    mTabWidget->addTab(mLicenceTextEdit,"Licence");
//    mTabWidget->addTab(mView, "Aidez-nous");


//    mView->setHtml("<center><form action='https://www.paypal.com/cgi-bin/webscr' method='post' target='_top'>"
//                   "<input type='hidden' name='cmd' value='_s-xclick'>"
//            "<input type='hidden' name='hosted_button_id' value='LRAN676KXATJY'>"
//            "<input type='image' src='https://www.paypalobjects.com/fr_FR/FR/i/btn/btn_donateCC_LG.gif' border='0' name='submit' alt='PayPal - la solution de paiement en ligne la plus simple et la plus sécurisée !'>"
//            "<img alt='' border='0' src='https://www.paypalobjects.com/fr_FR/i/scr/pixel.gif' width='1' height='1'>"
//                   "</form></center>");





    setLayout(layout);

    //    mPixLabel = new QLabel;
    //    mTextLabel= new QLabel;
    //    mCreditsButton = new QPushButton("Contributeurs");
    //    mLicenceButton = new QPushButton("Licence");
    //    mPixLabel->setPixmap(QPixmap(":about.png"));

    //    mPixLabel->setFrameShape(QFrame::Box);
    //    mPixLabel->setFrameShadow(QFrame::Sunken);

    //    QHBoxLayout * layoutBox = new QHBoxLayout;
    //    layoutBox->addWidget(mCreditsButton);
    //    layoutBox->addStretch();
    //    layoutBox->addWidget(mLicenceButton);

    //    QVBoxLayout * layout = new QVBoxLayout;
    ////    layout->setContentsMargins(0,0,0,0);
    //    layout->addWidget(mPixLabel);

    //    layout->addWidget(mTextLabel);

    //    layout->addStretch();
    //    layout->addLayout(layoutBox);
    ////    layout->setSpacing(0);
    //    setLayout(layout);


    //    mTextLabel->setAlignment(Qt::AlignCenter);
    //    mTextLabel->setText(QString("%1\n\nversion: %2\nbuild: %3\n Crée par Sacha Schutz")
    //                        .arg(qApp->applicationName(),
    //                             qApp->applicationVersion(),
    //                             "f0cdc42116"
    //                             ));


    setWindowTitle("A propos...");


}
