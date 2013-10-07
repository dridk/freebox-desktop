#include "aboutdialog.h"
#include <QKeyEvent>
#include <QMessageBox>
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{

    mTabWidget = new QTabWidget;
    mAboutHeader= new AboutHeader;
    mContributorTextEdit = new QTextBrowser;
    mLicenceTextEdit = new QTextBrowser;
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    mLicenceTextEdit->setReadOnly(true);
    mContributorTextEdit->setReadOnly(true);

    mContributorTextEdit->setOpenExternalLinks(true);

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


    setLayout(layout);
    setWindowTitle("A propos...");
    mKonamiValid = 0;
    mKonamiCodes.append(Qt::Key_Up);
    mKonamiCodes.append(Qt::Key_Up);
    mKonamiCodes.append(Qt::Key_Down);
    mKonamiCodes.append(Qt::Key_Down);
    mKonamiCodes.append(Qt::Key_Left);
    mKonamiCodes.append(Qt::Key_Right);
    mKonamiCodes.append(Qt::Key_Left);
    mKonamiCodes.append(Qt::Key_Right);
    mKonamiCodes.append(Qt::Key_B);
    mKonamiCodes.append(Qt::Key_A);

    mTabWidget->setFocusPolicy(Qt::NoFocus);
    setFocus();

    setFixedWidth(mAboutHeader->width());

}

void AboutDialog::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == mKonamiCodes.at(mKonamiValid))
        mKonamiValid++;

    else
        mKonamiValid = 0;


    qDebug()<<mKonamiValid;
    if (mKonamiValid >= mKonamiCodes.count())
    {

        mKonamiValid = 0;
        QMessageBox::information(this,"konami", "Konami code activé");
    }

}
