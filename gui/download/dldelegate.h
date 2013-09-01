#ifndef DLDELEGATE_H
#define DLDELEGATE_H

#include <QStyledItemDelegate>

class DLDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DLDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    
};

#endif // DLDELEGATE_H
