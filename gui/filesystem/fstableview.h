#ifndef FSTABLEVIEW_H
#define FSTABLEVIEW_H

#include <QTableView>
#include <QContextMenuEvent>
#include "fsmenu.h"
class FSTableView : public QTableView
{
    Q_OBJECT
public:
    explicit FSTableView(QWidget *parent = 0);
    
   virtual void contextMenuEvent(QContextMenuEvent *);

signals:
    
public slots:

private:
    QMenu * mItemMenu;
    QMenu * mMenu;
};

#endif // FSTABLEVIEW_H
