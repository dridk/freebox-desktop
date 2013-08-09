#ifndef AUTHORIZEMESSAGEBOX_H
#define AUTHORIZEMESSAGEBOX_H

#include <QMessageBox>
#include <QTimer>
#include "mafreebox.h"
class AuthorizeMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit AuthorizeMessageBox(MaFreeBox * freebox,  QWidget *parent = 0);
    void setTrackId(int id);



public slots:
     void getStatus();
    void showMessage(const MaFreeBox::AuthStatus& status);

private:

    MaFreeBox * mFbx;
    QTimer * mTimer;
    int mTrackId;


    
};

#endif // AUTHORIZEMESSAGEBOX_H
