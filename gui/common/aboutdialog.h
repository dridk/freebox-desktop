#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "aboutheader.h"
class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);
    

    void keyPressEvent(QKeyEvent *);



private:
    QTabWidget *mTabWidget;
    AboutHeader * mAboutHeader;
    QTextBrowser * mContributorTextEdit;
    QTextBrowser * mLicenceTextEdit;
    QList<Qt::Key> mKonamiCodes;
    int mKonamiValid;



};

#endif // ABOUTDIALOG_H
