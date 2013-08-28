#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{

    mLabel = new QLabel;
    mLabel->setPixmap(QPixmap(":about.png"));

    QFrame * line = new QFrame;
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(mLabel);
    layout->addWidget(line);


    setLayout(layout);


}
