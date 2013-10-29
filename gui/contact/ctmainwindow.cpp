#include "ctmainwindow.h"

CTMainWindow::CTMainWindow(QWidget *parent) :
    AbstractMainWindow(parent)
{

    mListView = new CtListView;
    mModel = new CtModel(fbx());


    mListView->setModel(mModel);



    setCentralWidget(mListView);

    connect(fbx(),SIGNAL(loginSuccess()),
            fbx()->contact(), SLOT(requestList()));

}
