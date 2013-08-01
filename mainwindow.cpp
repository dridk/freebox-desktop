#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    freebox = new MaFreeBox;

    //    freebox->setApplicationToken("Cw0MVrumznvfZxn3xnGbKeg6afjVp+XTqptWeSraESzfxp/SAdZ9ML+zAvwNoPro");
    freebox->setApplicationId("fr.freebox.testapp2");

    freebox->loadApplicationToken();

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(login()));
    connect(freebox,SIGNAL(error(QString,Error)), this,SLOT(showError()));

    connect(ui->listButton,SIGNAL(clicked()),this,SLOT(getList()));


    connect(freebox->fileSystem(),SIGNAL(fileListReceived(QList<File>)),
            this,SLOT(setList(QList<File>)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{

    qDebug()<<"login";
    freebox->requestLogin();

    /*
  freebox->authorize("fr.freebox.testapp2","Test App2","0.1","mon PC");
    connect(freebox,SIGNAL(authorizedReceived(QString,int)),loop,SLOT(quit()));
   loop->exec();*/



    //    freebox->login();
    //    connect(freebox,SIGNAL(loginReceived()),loop,SLOT(quit()));
    //    loop->exec();

    //    qDebug()<<"fini";



    // freebox->session("fr.freebox.testapp2");
    // connect(freebox,SIGNAL(sessionReceived()),loop,SLOT(quit()));
    // loop->exec();

    // freebox->test();


    //   freebox->authorizeProgress();
    //  connect(freebox,SIGNAL(authorizeProgressReceived(QString,QString)),loop,SLOT(quit()));


    //freebox->session("fr.labsquare.test2");





}

void MainWindow::showError()
{

    QMessageBox::warning(this,"freebox error", freebox->errorString());


}

void MainWindow::getList()
{
    freebox->fileSystem()->requestFileList();
}


void MainWindow::setList(const QList<File> &list)
{
    qDebug()<<"set list";
ui->listWidget->clear();

    foreach ( File f, list)
    {

        ui->listWidget->addItem(f.name);

    }


}
