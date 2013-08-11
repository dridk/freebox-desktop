#ifndef HEADERPATHWIDGET_H
#define HEADERPATHWIDGET_H

#include <QFrame>
#include <QtWidgets>
class HeaderPathWidget : public QToolBar
{
    Q_OBJECT
public:
    explicit HeaderPathWidget(QWidget *parent = 0);
    void addButton(const QString& name, const QString& path);

    void setPath(const QStringList& list);
signals:
    
public slots:

private:
    QHBoxLayout * mLayout;
    QList<QToolButton*> mButtonList;
    
};

#endif // HEADERPATHWIDGET_H
