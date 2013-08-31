#ifndef AUTHORIZEMESSAGEBOX_H
#define AUTHORIZEMESSAGEBOX_H

#include <QMessageBox>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include "fbxapi.h"
class AuthorizeMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit AuthorizeMessageBox(FbxAPI * freebox,  QWidget *parent = 0);
    void setTrackId(int id);

    void setText(const QString& message);

public slots:
     void getStatus();
    void showMessage(const FbxAPI::AuthStatus& status);

private:

    FbxAPI * mFbx;
    QTimer * mTimer;
    int mTrackId;
    QLabel * mTextLabel;
    QLabel * mGifLabel;
    QPushButton * mCancelButton;


    
};

#endif // AUTHORIZEMESSAGEBOX_H
