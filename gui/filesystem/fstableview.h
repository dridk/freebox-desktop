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

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);


public slots:
    void remove();
    void mkdir();
    void download();



signals:
    void filesAdded(const QStringList& list);
protected:
    QMenu * createItemMenu();
    QMenu * createMenu();
    QMenu * createSelectionMenu();
    void keyPressEvent(QKeyEvent *event);

    
public slots:
    void itemActionTriggered(QAction * action);

private:

    QModelIndexList mCopyIndexes;
    QModelIndexList mCutIndexes;
};

#endif // FSTABLEVIEW_H
