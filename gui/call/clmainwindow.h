#ifndef CLMAINWINDOW_H
#define CLMAINWINDOW_H
#include "abstractmainwindow.h"
#include "clmodel.h"
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
};

#endif // CLMAINWINDOW_H
