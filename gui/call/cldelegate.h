#ifndef CLDELEGATE_H
#define CLDELEGATE_H

#include <QItemDelegate>

class CLDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CLDelegate(QObject *parent = 0);
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    
public slots:
    
};

#endif // CLDELEGATE_H
