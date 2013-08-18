#ifndef FSTASKDELEGATE_H
#define FSTASKDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
class FSTaskDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FSTaskDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    
public slots:
    
};

#endif // FSTASKDELEGATE_H
