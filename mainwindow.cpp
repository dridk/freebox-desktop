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

   qDebug()<<"init success";
   //freebox->authorize("fr.labsquare.test2","test2","0.2","mon PC");

   qDebug()<<freebox->appToken();

}
