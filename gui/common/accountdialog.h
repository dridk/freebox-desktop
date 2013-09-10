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

private:
    QTableWidget * mTableWidget;
    QPushButton * mAddButton;
    QPushButton * mEditButton;
    QPushButton * mRemoveButton;
    QPushButton * mSetDefaultButton;
    QPushButton * mExportButton;
    QPushButton * mCancelButton;
    
};

#endif // ACCOUNTDIALOG_H
