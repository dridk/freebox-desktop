#include "fstaskbutton.h"
#include <QPainter>
FSTaskButton::FSTaskButton(QWidget *parent) :
    QToolButton(parent)
{
//    setText("test");
    mMovie.setFileName(":loading.gif");
    mMovie.start();
}

void FSTaskButton::paintEvent(QPaintEvent *event)
{


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawPixmap(0,0,mMovie.currentPixmap());


    QToolButton::paintEvent(event);


}
