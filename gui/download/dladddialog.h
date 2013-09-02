#ifndef DLADDDIALOG_H
#define DLADDDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QDialogButtonBox>
#include "fsmodel.h"
#include "fbxapi.h"
class DLAddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DLAddDialog(FbxAPI * fbx, QWidget *parent = 0);
    
signals:
    
public slots:
    void getDestination();

protected slots:
    void add();
    void urlChanged(const QString& text);


private:
    QLineEdit * mUrlEdit;
    QLineEdit * mDestinationEdit;
    QDialogButtonBox * mButtonBox;
    FbxAPI * mFbx;
    
};

#endif // DLADDDIALOG_H
