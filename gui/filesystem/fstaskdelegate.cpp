#include "fstaskdelegate.h"
#include <QApplication>
#include <QStylePainter>
#include <QCommonStyle>
FSTaskDelegate::FSTaskDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void FSTaskDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() == 1) {
        painter->setBrush(QBrush(Qt::red));

        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = index.data().toInt();
        progressBarOption.text = QString::number(index.data().toInt()) + "%";
        progressBarOption.textVisible = true;
        progressBarOption.textAlignment = Qt::AlignCenter;

        qApp->style()->drawControl(QStyle::CE_ProgressBar,
                                   &progressBarOption, painter);


    }

    else
        QStyledItemDelegate::paint(painter,option,index);
    //    stylePainter.drawControl(QStyle::CE_ProgressBar,);




}

QSize FSTaskDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    //    return QSize(60, option.rect.width());
    return QStyledItemDelegate::sizeHint(option,index);
}
