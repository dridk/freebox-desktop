#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(test()));

    freebox = new MaFreeBox;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    freebox->init();
    QEventLoop * loop = new QEventLoop;
    connect(freebox,SIGNAL(ready()),loop,SLOT(quit()));
    loop->exec();

    qDebug()<<"init success";

/*
  freebox->authorize("fr.freebox.testapp2","Test App2","0.1","mon PC");
    connect(freebox,SIGNAL(authorizedReceived(QString,int)),loop,SLOT(quit()));
   loop->exec();*/



    freebox->login();
    connect(freebox,SIGNAL(loginReceived()),loop,SLOT(quit()));
    loop->exec();

    qDebug()<<"fini";



 freebox->session("fr.freebox.testapp2");
 connect(freebox,SIGNAL(sessionReceived()),loop,SLOT(quit()));
 loop->exec();

 freebox->test();


    //   freebox->authorizeProgress();
    //  connect(freebox,SIGNAL(authorizeProgressReceived(QString,QString)),loop,SLOT(quit()));


    //freebox->session("fr.labsquare.test2");





}
