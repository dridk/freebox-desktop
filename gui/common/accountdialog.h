#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QtWidgets>
class AccountDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AccountDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    void load();
    void add();
    void edit();
    void remove();
    void exportKey();
    void setDefault();

private:
    QTableView * mTableView;
    QStandardItemModel * mModel;
    QPushButton * mAddButton;
    QPushButton * mEditButton;
    QPushButton * mRemoveButton;
    QPushButton * mSetDefaultButton;
    QPushButton * mExportButton;
    QPushButton * mCancelButton;
    
};

#endif // ACCOUNTDIALOG_H
