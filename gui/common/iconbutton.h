#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QToolButton>
#include <QListWidget>
#include <QDialog>
#include <QVBoxLayout>
class IconButton : public QToolButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = 0);
    
signals:
    
public slots:
    void showListWidget();

private:
    
};

#endif // ICONBUTTON_H
