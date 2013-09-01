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




    if (index.column() ==4)
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

    else
    {

     QStyledItemDelegate::paint(painter,option,index);
    }
        //    painter->setPen(QPen(Qt::black));
        //    painter->setBrush(QBrush(Qt::red));
        //    painter->drawRect(option.rect);

}

