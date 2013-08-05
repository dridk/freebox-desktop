#ifndef HEADERPATHWIDGET_H
#define HEADERPATHWIDGET_H

#include <QFrame>
#include <QtWidgets>
class HeaderPathWidget : public QFrame
{
    Q_OBJECT
public:
    explicit HeaderPathWidget(QWidget *parent = 0);
    void addButton(const QString& name, const QString& path);
    
signals:
    
public slots:

private:
    QHBoxLayout * mLayout;
    QList<QPushButton*> mButtonList;
    
};

#endif // HEADERPATHWIDGET_H
