#ifndef DLADDFILEDIALOG_H
#define DLADDFILEDIALOG_H

#include <QDialog>
#include <QtWidgets>
class DLAddFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DLAddFileDialog(QWidget *parent = 0);
    ~DLAddFileDialog();

    const QString& fileName() const;


private:
    QLineEdit * mFileEdit;
    QLineEdit * mDestEdit;
    QLineEdit * mPassEdit;
    QDialogButtonBox * mBoxButton;


};

#endif // DLADDFILEDIALOG_H
