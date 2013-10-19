#include "cldelegate.h"
#include <QPainter>
#include <QDateTime>
CLDelegate::CLDelegate(QObject *parent) :
    QItemDelegate(parent)
{




}

void CLDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    if ( index.column() == 0)
        QItemDelegate::paint(painter,option,index);

    if (index.column() == 1)
    {
        if(option.state & QStyle::State_Selected ) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        QString date  = index.data().toDateTime().toString("dddd dd MMM à hh:mm");
        int duree = index.data(Qt::UserRole).toInt();

        QTime time(0,0,0);
        time = time.addSecs(duree);
        QString sub;
        if (duree<=60)
            sub = QString("Durée de l'appel: %1 ").arg(time.toString("s 's'"));

        if (duree > 60)
            sub = QString("Durée de l'appel: %1 ").arg(time.toString("m 'mins' s 's'"));

        if (duree > 3600)
            sub = QString("Durée de l'appel: %1 ").arg(time.toString("h 'heure' m 'mins' s 's'"));


        QRect zone = option.rect.adjusted(0,5,0,-5);

        QFont font;
        font.setItalic(false);
        painter->setFont(font);
        painter->setPen(QPen(Qt::black));

        painter->drawText(zone, Qt::AlignTop|Qt::AlignHCenter,date);

        font.setItalic(true);
        painter->setFont(font);
        painter->setPen(QPen(Qt::darkGray));
        painter->drawText(zone, Qt::AlignBottom|Qt::AlignHCenter,sub);



    }






}
