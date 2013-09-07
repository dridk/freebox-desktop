#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QListWidget>
#include <QList>
#include "abstractmainwindow.h"
class LauncherWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit LauncherWidget(QWidget *parent = 0);
    
signals:
    
public slots:

protected slots:
    void launch(const QModelIndex& index);

private:
    void addView(AbstractMainWindow* view);
    QList<AbstractMainWindow*> mViews;
    
};

#endif // LAUNCHERWIDGET_H
