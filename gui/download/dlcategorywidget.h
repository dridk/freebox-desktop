#ifndef DLCATEGORYWIDGET_H
#define DLCATEGORYWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QtWidgets>
class DLCategoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLCategoryWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QListWidget * mCateogryView;
    QListWidget * mRssView;
    
};

#endif // DLCATEGORYWIDGET_H
