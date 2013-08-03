#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mafreebox.h"
#include "gui/filesystemmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void login();
    void showError();
    void getList();
    void setList(const QList<FileInfo>& list);
    
private:
    Ui::MainWindow *ui;
    MaFreeBox * freebox;
     FileSystemModel * mModel;

};

#endif // MAINWINDOW_H
