#ifndef AUTHORIZEMESSAGEBOX_H
#define AUTHORIZEMESSAGEBOX_H

#include <QMessageBox>
#include <QTimer>
#include "fbxapi.h"
class AuthorizeMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit AuthorizeMessageBox(FbxAPI * freebox,  QWidget *parent = 0);
    void setTrackId(int id);



public slots:
     void getStatus();
    void showMessage(const FbxAPI::AuthStatus& status);

private:

    FbxAPI * mFbx;
    QTimer * mTimer;
    int mTrackId;


    
};

#endif // AUTHORIZEMESSAGEBOX_H
