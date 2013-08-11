#include "headerpathwidget.h"
#include <QHBoxLayout>
HeaderPathWidget::HeaderPathWidget(QWidget *parent) :
    QToolBar(parent)
{

//    mLayout = new QHBoxLayout;
//    //    setStyleSheet("QFrame{background:#3a3a3a;}");


//    setLayout(mLayout);
//    mLayout->addStretch();
//    mLayout->setContentsMargins(0,0,0,0);

    layout()->setContentsMargins(0,0,0,0);

}

void HeaderPathWidget::addButton(const QString &name, const QString &path)
{

//    QToolButton * button = new QToolButton;
//    button->setText(name);
//    button->setObjectName(path);
//    button->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
//    button->setAutoRaise(true);


//    mLayout->insertWidget(0, button);
//    mButtonList.append(button);

}

void HeaderPathWidget::setPath(const QStringList &list)
{
    clear();
    qDebug()<<list;
    foreach (QString txt, list)
    {

        addAction(txt)->setEnabled(txt != list.last());
        addSeparator();

    }



}
