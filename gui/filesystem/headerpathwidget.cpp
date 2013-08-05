#include "headerpathwidget.h"
#include <QHBoxLayout>
HeaderPathWidget::HeaderPathWidget(QWidget *parent) :
    QFrame(parent)
{

    mLayout = new QHBoxLayout;
//    setStyleSheet("QFrame{background:#3a3a3a;}");


    setLayout(mLayout);
    mLayout->addStretch();
    mLayout->setContentsMargins(0,0,0,0);

}

void HeaderPathWidget::addButton(const QString &name, const QString &path)
{

    QToolButton * button = new QToolButton;
    button->setText(name);
    button->setObjectName(path);
    button->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    button->setAutoRaise(true);

    mLayout->insertWidget(mLayout->count()-1, button);
    mLayout->insertWidget(mLayout->count()-1, new QLabel("/"));


}
