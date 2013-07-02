#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(test()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    MaFreeBox * freebox = new MaFreeBox;
    freebox->init();
    QEventLoop * loop = new QEventLoop;
    connect(freebox,SIGNAL(ready()),loop,SLOT(quit()));
    loop->exec();
    disconnect(freebox,SIGNAL(ready()),loop,SLOT(quit()));

    qDebug()<<"init success";
//    freebox->authorize("fr.labsquare.test2","test2","0.2","mon PC");
//    connect(freebox,SIGNAL(authorizedReceived(QString,int)),
//            freebox,SLOT(authorizeProgress()));


//   connect(freebox,SIGNAL(authorizeProgressReceived(QString,QString)),loop,SLOT(quit()));

   //loop->exec();

   freebox->login("fr.labsquare.test2","0.2","xxxxxx");





}
