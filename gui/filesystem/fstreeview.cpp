#include "fstreeview.h"

FSTreeView::FSTreeView(QWidget *parent) :
    QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::EditKeyPressed);
}
