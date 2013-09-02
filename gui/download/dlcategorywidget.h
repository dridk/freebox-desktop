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

signals:
    void statusClicked(const QString& status);
protected slots:
    void itemClicked(const QModelIndex& index);

private:
    QTreeWidget * mCateogryView;

};

#endif // DLCATEGORYWIDGET_H
