#include "authorizemessagebox.h"

AuthorizeMessageBox::AuthorizeMessageBox(MaFreeBox *freebox, QWidget *parent):
    mFbx(freebox),QMessageBox(parent)
{
    mTimer = new QTimer(this);
    setWindowTitle("Authorisation");
    setText("Authorisation en cours");
    setStandardButtons(QMessageBox::Cancel);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(getStatus()));
    connect(mFbx,SIGNAL(authorizeStatusChanged(MaFreeBox::AuthStatus)), this,SLOT(showMessage(MaFreeBox::AuthStatus)));



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

void AuthorizeMessageBox::showMessage(const MaFreeBox::AuthStatus& status)
{

    qDebug()<<"show message "  <<status;

    if (status == MaFreeBox::PendingStatus)
    {
        setText("Veuillez authoriser l'application sur votre Freebox server");
    }
    if (status == MaFreeBox::TimeOutStatus)
    {
        setText("temps ecoulé");
        reject();
    }
    if (status == MaFreeBox::GrantedStatus)
    {
        setText("Application authorisé avec succes");
        accept();
    }
    if (status == MaFreeBox::DeniedStatus)
    {
        setText("Application non authorisé");
        reject();
    }



}
