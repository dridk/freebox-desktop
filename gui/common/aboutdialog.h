#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QWebView>
#include "aboutheader.h"
class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);
    
signals:
    
public slots:

private:
   QTabWidget *mTabWidget;
   AboutHeader * mAboutHeader;
   QTextEdit * mContributorTextEdit;
   QTextEdit * mLicenceTextEdit;
   QWebView * mView;
    
};

#endif // ABOUTDIALOG_H
