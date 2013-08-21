#include "fstaskdelegate.h"
#include <QApplication>
#include <QStylePainter>
#include <QCommonStyle>
#include <QDebug>
#include <QFontMetrics>
FSTaskDelegate::FSTaskDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void FSTaskDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QString title         = index.data(Qt::DisplayRole).toString();
    QString subTitle      = index.data(Qt::WhatsThisRole).toString();
    int progress          = index.data(Qt::UserRole).toInt();
    QString mimeIconPath  = index.data(Qt::DecorationRole).toString();
    QString actionIconPath= index.data(Qt::StatusTipRole).toString();


    if (option.state & QStyle::State_Selected)
    {
        painter->setBrush(QBrush(QColor("#316AC5")));
        painter->drawRect(option.rect);
    }

    painter->setPen(QPen(Qt::black));


    QPixmap icon (mimeIconPath);

    painter->drawPixmap(5, option.rect.center().y()-icon.height()/2, icon);

    QRect progressRect = option.rect;
    progressRect.setX(40);
    progressRect.setY(option.rect.center().y() - 7);
    progressRect.setRight(option.rect.right() - 30);

    progressRect.setHeight(progress < 100 ? 14 : 1);

    if (progress <100) {
    QStyleOptionProgressBar progressBarOption;
    progressBarOption.rect = progressRect;

    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.progress = progress;
    progressBarOption.text = QString::number(progress) + "%";
    progressBarOption.textVisible = true;
    progressBarOption.textAlignment = Qt::AlignCenter;

    qApp->style()->drawControl(QStyle::CE_ProgressBar,
                               &progressBarOption, painter);
    }

    QFontMetrics metrics(painter->font());

    if ((option.state & QStyle::State_Selected))
        painter->setPen(QPen(Qt::white));
    else
        painter->setPen(QPen(Qt::black));

    painter->setFont(QFont(painter->font().family(),10));
    painter->drawText(progressRect.topLeft()-QPoint(-5,5),title);
    painter->setFont(QFont(painter->font().family(),8));
    painter->drawText(progressRect.bottomLeft()+QPoint(5,5+metrics.height()),
                      subTitle);


   QPixmap rightPixmap(actionIconPath);
//    if (mClicked.contains(index))
//        painter->setOpacity(0.4);
//    else
//        painter->setOpacity(1);


    painter->drawPixmap(option.rect.right() -20,  option.rect.center().y()-8,
                        rightPixmap);


}

QSize FSTaskDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //    qDebug()<<"sizeHint"<<QStyledItemDelegate::sizeHint(option,index);
    return QSize(0, 65);
}

bool FSTaskDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{

    if (event->type() == QEvent::MouseButtonPress || QEvent::MouseButtonRelease)
    {

        QMouseEvent * mouseEvent  = static_cast<QMouseEvent*>(event);

        QRect buttonRect;
        buttonRect.setTopLeft(QPoint(option.rect.right() -20,  option.rect.center().y()-8));
        buttonRect.setWidth(16);
        buttonRect.setHeight(16);

        if (buttonRect.contains(mouseEvent->pos()) && event->type() == QEvent::MouseButtonPress )
            mClicked.append(index);

        if (buttonRect.contains(mouseEvent->pos()) && event->type() == QEvent::MouseButtonRelease )
            mClicked.removeAll(index);
        return QStyledItemDelegate::editorEvent(event,model,option,index);

    }

    return QStyledItemDelegate::editorEvent(event,model,option,index);

}
