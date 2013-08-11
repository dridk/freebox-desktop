#ifndef FSTABLEVIEW_H
#define FSTABLEVIEW_H

#include <QTableView>
#include <QContextMenuEvent>
#include "fsmenu.h"
#include "fsmodel.h"
#include <QList>
class FSTableView : public QTableView
{
    Q_OBJECT
public:
    explicit FSTableView(QWidget *parent = 0);
    
   virtual void contextMenuEvent(QContextMenuEvent *);

    FSModel * fsModel();

protected:
    QMenu * createItemMenu();
    QMenu * createMenu();
    QMenu * createSelectionMenu();

    
public slots:
    void itemActionTriggered(QAction * action);

private:
    QMenu * mItemMenu;
    QMenu * mMenu;
    QModelIndexList mCopyIndexes;
    QModelIndexList mCutIndexes;
};

#endif // FSTABLEVIEW_H
