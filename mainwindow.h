#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mafreebox.h"
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
    void setList(const QList<File>& list);
    
private:
    Ui::MainWindow *ui;
    MaFreeBox * freebox;
};

#endif // MAINWINDOW_H
