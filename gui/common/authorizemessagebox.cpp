#include "authorizemessagebox.h"

AuthorizeMessageBox::AuthorizeMessageBox(FbxAPI *freebox, QWidget *parent):
    QMessageBox(parent), mFbx(freebox)
{
    mTimer = new QTimer(this);
    setWindowTitle("Authorisation");
    setText("Authorisation en cours");
    setStandardButtons(QMessageBox::Cancel);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(getStatus()));
    connect(mFbx,SIGNAL(authorizeStatusChanged(FbxAPI::AuthStatus)), this,SLOT(showMessage(FbxAPI::AuthStatus)));



    mTimer->setInterval(1000);
    mTimer->start();

    setAttribute(Qt::WA_DeleteOnClose);


}

void AuthorizeMessageBox::setTrackId(int id)
{
    mTrackId = id;
}


void AuthorizeMessageBox::getStatus()
{

    mFbx->requestAuthorizeStatus(mTrackId);

}

void AuthorizeMessageBox::showMessage(const FbxAPI::AuthStatus& status)
{

    qDebug()<<"show message "  <<status;

    if (status == FbxAPI::PendingStatus)
    {
        setText("Veuillez authoriser l'application sur votre Freebox server");
    }
    if (status == FbxAPI::TimeOutStatus)
    {
        setText("temps ecoulé");
        reject();
    }
    if (status == FbxAPI::GrantedStatus)
    {
        setText("Application authorisé avec succes");
        accept();
    }
    if (status == FbxAPI::DeniedStatus)
    {
        setText("Application non authorisé");
        reject();
    }



}
