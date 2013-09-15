#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "iconbutton.h"
class AccountDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AccountDialog(QWidget *parent = 0);
    ~AccountDialog();

    QString name() const;
    QString hostName() const;
    int port() const;
    QIcon icon() const;
    void setEditMode(bool enable);

    void setData(const QString& name);

protected slots:
    void validate();

private:
    QLineEdit * mNameEdit;
    QLineEdit * mHostNameEdit;
    QSpinBox  * mPortSpinBox;
    QDialogButtonBox * mButtonBox;
    IconButton * mIconButton;




    
};

#endif // ACCOUNTDIALOG_H
