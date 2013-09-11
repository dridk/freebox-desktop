#ifndef DLSCHEDULETABLEWIDGET_H
#define DLSCHEDULETABLEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDate>
#include <QList>
#include <QMouseEvent>
#include "download.h"
class DLScheduleTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLScheduleTableWidget(QWidget *parent = 0);
    void setSchedule(const QList<DlThrottlingConfig::Type>& list);
    const QList<QColor>& typeColors(){return mTypeColors;}
    void setCurrentType(const DlThrottlingConfig::Type& type);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    QRect gridRect();
    void addSquare(const QPoint& mousePos);
    




private:
    int mSquareSize;
    QList<DlThrottlingConfig::Type> mTypes;
    QList<QColor> mTypeColors;
    DlThrottlingConfig::Type mCurrentType;
    
};

#endif // DLSCHEDULETABLEWIDGET_H
