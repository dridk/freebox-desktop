#include "dlscheduletablewidget.h"
#include <QFontMetrics>
DLScheduleTableWidget::DLScheduleTableWidget(QWidget *parent) :
    QWidget(parent)
{
    //Draw array 24h * 7day
    mSquareSize = 24;
    setFixedSize(mSquareSize*(24+3),mSquareSize*(7+1));

    //    enum Type {NormalType,  SlowType, HibernateType };
    mTypeColors.append(QColor("#00AA00"));
    mTypeColors.append(QColor("#0000AA"));
    mTypeColors.append(QColor("#AA0000"));
    mCurrentType = DlThrottlingConfig::NormalType;


    for ( int i=0; i<24*7; ++i)
        mTypes.append(DlThrottlingConfig::NormalType);

    setMouseTracking(true);
}

void DLScheduleTableWidget::setSchedule(const QList<DlThrottlingConfig::Type> &list)
{
    mTypes = list;
    repaint();
}

void DLScheduleTableWidget::setCurrentType(const DlThrottlingConfig::Type &type)
{
    mCurrentType = type;
}

void DLScheduleTableWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
  //-----------------------Draw Labels hours
    int counter = 0;
    for (int x= gridRect().left(); x<=gridRect().right(); x+=mSquareSize)
    {
        QString txt =QString::number(counter);
        QFontMetrics metrics(painter.font());
        QPoint pos;
        pos.setX(x+(0.5*(mSquareSize-metrics.width(txt))));
        pos.setY(gridRect().top()-4);
         painter.drawText(pos,txt);
        ++counter;

    }
    //-----------------------Draw Labels Days
    int dateCounter = 1;
    for (int y=gridRect().top();y<=gridRect().bottom(); y+= mSquareSize)
    {
        QFontMetrics metrics(painter.font());
        QPoint pos;
        pos.setX(rect().left());
        pos.setY(y + metrics.height());
        QDate date;
        date.setDate(2013,4,dateCounter);  // this date start by Monday
        painter.drawText(pos, date.toString("dddd"));
        ++dateCounter;
    }

    //-----------------------Draw Box

    for (int id = 0; id< mTypes.count(); ++id)
    {
        QPoint pos;
        pos.setY(id/24);
        pos.setX(id%24);
        QRect square( pos.x()*mSquareSize + gridRect().left(),
                      pos.y()*mSquareSize + gridRect().top(),
                      mSquareSize,mSquareSize);
        painter.setPen(isEnabled() ? Qt::darkGray : Qt::lightGray);
        QColor color = mTypeColors.at(mTypes.at(id));
        painter.setBrush(QBrush(color));
        painter.drawRect(square);
    }

    //----------------------Set Disable...
    if (!isEnabled()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255,255,255,200));
        painter.drawRect(gridRect());
    }
}

void DLScheduleTableWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton )
        addSquare(event->pos());
}

void DLScheduleTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
        addSquare(event->pos());
}

QRect DLScheduleTableWidget::gridRect()
{
    QRect gridRect = rect().adjusted(24*3,24,0,0);
    gridRect.moveBottomRight(rect().bottomRight() - QPoint(1,1));
    return gridRect;
}

void DLScheduleTableWidget::addSquare(const QPoint &mousePos)
{
    //get grid coord in pixel
    QPoint p = mousePos - QPoint(24*3, 24);
    QPoint tp;
    tp.setX(p.x() * 24 / gridRect().width());
    tp.setY(p.y() * 7  / gridRect().height());

    if (tp.x() < 0  || tp.x() >= 24)
        return;
    if (tp.y() < 0 || tp.y() >= 7)
        return;

    int index = 24 * tp.y() + tp.x();
    if (index < mTypes.count())
    {
        mTypes[index] = mCurrentType;
        repaint();
    }
}
