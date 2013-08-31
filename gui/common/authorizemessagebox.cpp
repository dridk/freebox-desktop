#include "authorizemessagebox.h"
#include <QVBoxLayout>
AuthorizeMessageBox::AuthorizeMessageBox(FbxAPI *freebox, QWidget *parent):
    QDialog(parent), mFbx(freebox)
{
    mTextLabel = new QLabel;
    mGifLabel  = new QLabel;
    mCancelButton = new QPushButton("Annuler");
    mTimer = new QTimer(this);
    mTextLabel->setWordWrap(true);
    mTextLabel->setAlignment(Qt::AlignCenter);
    mGifLabel->setMovie(new QMovie(":auth.gif"));

    mGifLabel->setFrameStyle(QFrame::Box|QFrame::Sunken);
    mGifLabel->movie()->start();
    mGifLabel->movie()->stop();


    setWindowTitle("Authorisation");
    setText("Authorisation en cours");

    connect(mTimer,SIGNAL(timeout()),this,SLOT(getStatus()));
    connect(mFbx,SIGNAL(authorizeStatusChanged(FbxAPI::AuthStatus)), this,SLOT(showMessage(FbxAPI::AuthStatus)));
    connect(mCancelButton,SIGNAL(clicked()),this,SLOT(close()));
    QVBoxLayout * layout = new QVBoxLayout;
    setLayout(layout);

    layout->addWidget(mGifLabel);
    layout->addWidget(mTextLabel);
    layout->addStretch();
    layout->addWidget(mCancelButton);

    setFixedWidth(300);


    mTimer->setInterval(1000);
    mTimer->start();

    setAttribute(Qt::WA_DeleteOnClose);


}

void AuthorizeMessageBox::setTrackId(int id)
{
    mTrackId = id;
}

void AuthorizeMessageBox::setText(const QString &message)
{

    mTextLabel->setText(message);

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
        mGifLabel->movie()->start();
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
