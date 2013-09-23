#ifndef ABOUTHEADER_H
#define ABOUTHEADER_H

#include <QWidget>

class AboutHeader : public QWidget
{
    Q_OBJECT
public:
    explicit AboutHeader(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *);
    
signals:
    
public slots:
    
};

#endif // ABOUTHEADER_H
