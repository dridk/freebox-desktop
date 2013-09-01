#include "dldelegate.h"
#include <QPainter>
#include <QApplication>
#include <QStyle>
DLDelegate::DLDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void DLDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() == 0 ||index.column() == 8 )
        return QStyledItemDelegate::paint(painter,option,index);


    if (index.column() == 2)
    {
     QFont font;
     font.setBold(true);
     painter->setFont(font);
     painter->drawText(option.rect,index.data().toString());


    }

    if (index.column() == 3)
    {

        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = index.data().toDouble()/ 100;
        progressBarOption.text = QString::number(progressBarOption.progress) + "%";
        progressBarOption.textVisible = true;
        progressBarOption.textAlignment = Qt::AlignCenter;

        qApp->style()->drawControl(QStyle::CE_ProgressBar,
                                   &progressBarOption, painter);


    }
        //    painter->setPen(QPen(Qt::black));
        //    painter->setBrush(QBrush(Qt::red));
        //    painter->drawRect(option.rect);

}

