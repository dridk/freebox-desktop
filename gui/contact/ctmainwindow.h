#ifndef CTMAINWINDOW_H
#define CTMAINWINDOW_H
#include "abstractmainwindow.h"
#include "ctlistview.h"
#include "ctmodel.h"
class CTMainWindow : public AbstractMainWindow
{
    Q_OBJECT
public:
    explicit CTMainWindow(QWidget *parent = 0);
    
signals:
    
public slots:

private:
CtListView* mListView;
CtModel* mModel;
    
};

#endif // CTMAINWINDOW_H
