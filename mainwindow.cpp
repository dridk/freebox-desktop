#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    freebox = new MaFreeBox;
    mModel = new FileSystemModel(freebox);

    ui->tableView->setModel(mModel);




    //    freebox->setApplicationToken("Cw0MVrumznvfZxn3xnGbKeg6afjVp+XTqptWeSraESzfxp/SAdZ9ML+zAvwNoPro");
    freebox->setApplicationId("fr.freebox.testapp2");

    freebox->loadApplicationToken();

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(login()));
    connect(freebox,SIGNAL(error(QString,Error)), this,SLOT(showError()));

    connect(ui->listButton,SIGNAL(clicked()),this,SLOT(getList()));

    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),
            mModel,SLOT(setPath(QModelIndex)));

    //    connect(freebox->fileSystem(),SIGNAL(listReceived(QList<FileInfo>)),
    //            this,SLOT(setList(QList<FileInfo>)));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete freebox;
}

void MainWindow::login()
{

    qDebug()<<"login";
    freebox->requestLogin();




}

void MainWindow::showError()
{

    QMessageBox::warning(this,"freebox error", freebox->errorString());


}

void MainWindow::getList()
{
    QStringList tt;
    tt.append("L0Rpc3F1ZSBkdXIvRG9jdG9yIFdobyAtIFMwNUUwMyAtIFZpY3Rvcnkgb2YgdGhlIERhbGVrcyAtIERWQlJJUCAxNzA0MjAxMCAtIE1QRUcyLnNydA==");

           //   freebox->fileSystem()->requestMove(tt,"L0Rpc3F1ZSBkdXIvTXVzaXF1ZXM=");


    QString dir = QFileDialog::getExistingDirectory(this);

    freebox->fileSystem()->requestDownload("L0Rpc3F1ZSBkdXIvRW5mZXJtw6lzIGRlaG9ycy5hdmk=",
                                           dir);

//   mModel->setPath();

}

void MainWindow::setList(const QList<FileInfo> &list)
{





}


//void MainWindow::setList(const QList<File> &list)
//{
//    qDebug()<<"set list";
//ui->listWidget->clear();

//    foreach ( File f, list)
//    {

//        ui->listWidget->addItem(f.name);

//    }


//}
