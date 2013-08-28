#ifndef FSTASKBUTTON_H
#define FSTASKBUTTON_H

#include <QToolButton>
#include <QPaintEvent>
#include <QMovie>
class FSTaskButton : public QToolButton
{
    Q_OBJECT
public:
    explicit FSTaskButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:
    
public slots:
    
private:
    QMovie mMovie;
};

#endif // FSTASKBUTTON_H
