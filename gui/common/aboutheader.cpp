#include "aboutheader.h"
#include <QPainter>
#include <QApplication>
AboutHeader::AboutHeader(QWidget *parent) :
    QWidget(parent)
{

    setFixedSize( QPixmap(":fbx_header.png").size());

}

void AboutHeader::paintEvent(QPaintEvent *)
{

    QPainter painter;
    painter.begin(this);


    painter.drawPixmap(0,0, QPixmap(":fbx_header.png"));
    painter.setPen(QPen(Qt::lightGray));
    painter.drawText(rect().adjusted(5,5,-5,-5),Qt::AlignRight|Qt::AlignBottom,
                     qApp->applicationVersion()+"\n"
                     "Copyright 2013 " + qApp->organizationName());
    painter.end();



}
