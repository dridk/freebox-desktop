#ifndef HEADERPATHWIDGET_H
#define HEADERPATHWIDGET_H

#include <QFrame>
#include <QtWidgets>
#include "stdmodel.h"
class HeaderPathWidget : public QToolBar
{
    Q_OBJECT
public:
    explicit HeaderPathWidget( QWidget *parent = 0);
    void setModel(QStandardItemModel * model);

    void setCurrentIndex(const QModelIndex& index);
//    void setPath(const QByteArray& path);
signals:
   void clicked(const QModelIndex& index);
    
private slots:
   void buttonClicked(QAction * action);

private:
    QHBoxLayout * mLayout;
    QModelIndex mCurrentIndex;
    QStandardItemModel * mModel;
    
};

#endif // HEADERPATHWIDGET_H
