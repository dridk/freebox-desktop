#ifndef CLMAINWINDOW_H
#define CLMAINWINDOW_H
#include <QtWidgets>
#include "abstractmainwindow.h"
#include "clmodel.h"
#include "cldelegate.h"
class CLMainWindow : public AbstractMainWindow
{
    Q_OBJECT
public:
    explicit CLMainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    

    private:
    QTableView * mView;
    CLModel * mModel;
    CLDelegate * mDelegate;
    QComboBox *mFilterBox;
};

#endif // CLMAINWINDOW_H
