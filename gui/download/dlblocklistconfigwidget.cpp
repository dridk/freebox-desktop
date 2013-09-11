#include "dlblocklistconfigwidget.h"

DLBlocklistConfigWidget::DLBlocklistConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * boxLayout = new QVBoxLayout;

    mLabel     = new QLabel;
    mTextEdit  = new QPlainTextEdit;
    mNoteLabel = new QLabel;

    mNoteLabel->setWordWrap(true);
    mNoteLabel->setTextFormat(Qt::RichText);
    mLabel->setText("Listes d'URL de fichiers de blocage d'IP, séparées par un saut à la ligne");
    mNoteLabel->setText("<b>Note :</b> Les listes de blocages de pairs doivent être au format CIDR");


    boxLayout->addWidget(mLabel);
    boxLayout->addWidget(mTextEdit);
    boxLayout->addWidget(mNoteLabel);



    setLayout(boxLayout);

    setWindowTitle("BlockList");


}

DLBlocklistConfigWidget::~DLBlocklistConfigWidget()
{
    delete mNoteLabel;
    delete mTextEdit;
}

void DLBlocklistConfigWidget::setConfig(const DlBlockListConfig &cfg)
{
    foreach (QString txt, cfg.sources)
    mTextEdit->appendPlainText(txt);

}
