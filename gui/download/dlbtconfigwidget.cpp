#include "dlbtconfigwidget.h"

DLBtConfigWidget::DLBtConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QFormLayout * layout  = new QFormLayout;
    mMaxPeersSpinBox      = new QSpinBox;
    mStopRatioSpinBox     = new QDoubleSpinBox;
    mCryptoSupportComboBox= new QComboBox;
    mEnableDhtCheckBox    = new QCheckBox;
    mEnablePexCheckBox    = new QCheckBox;
    mAnnounceTimeoutSpinBox  = new QSpinBox;

    mMaxPeersSpinBox->setRange(0,300);
    mStopRatioSpinBox->setRange(0,100);
    mAnnounceTimeoutSpinBox->setRange(0,300);


    mCryptoSupportComboBox->addItem("Désactivé");
    mCryptoSupportComboBox->addItem("Autorisé");
    mCryptoSupportComboBox->addItem("Préféré");
    mCryptoSupportComboBox->addItem("Obligatoire");



    layout->addRow("Nombre de pairs maximum :", mMaxPeersSpinBox);
    layout->addRow("Ratio de partage :", mStopRatioSpinBox);
    layout->addRow("Chiffrement des connexions :", mCryptoSupportComboBox);
    layout->addRow("Activer la DHT :", mEnableDhtCheckBox);
    layout->addRow("Activer l'échange de pairs :", mEnablePexCheckBox);
    layout->addRow("Temps d'attente pour l'annonce sur un traqueur (en secondes):",
                   mAnnounceTimeoutSpinBox);





    setLayout(layout);
    setWindowTitle("Torrent");

}

DLBtConfigWidget::~DLBtConfigWidget()
{
    delete mMaxPeersSpinBox;
    delete mStopRatioSpinBox;
    delete mCryptoSupportComboBox;
    delete mEnableDhtCheckBox;
    delete mEnablePexCheckBox;
    delete mAnnounceTimeoutSpinBox;
}

void DLBtConfigWidget::setConfig(const DlBtConfig &cfg)
{
    mCfg = cfg;
    mMaxPeersSpinBox->setValue(cfg.maxPeers);
    mStopRatioSpinBox->setValue(double(cfg.stopRatio)/100);
    mCryptoSupportComboBox->setCurrentIndex(int(cfg.cryptoSupport));
    mEnableDhtCheckBox->setChecked(cfg.enableDht);
    mEnablePexCheckBox->setChecked(cfg.enablePex);
    mAnnounceTimeoutSpinBox->setValue(cfg.announceTimeout);



}

const DlBtConfig& DLBtConfigWidget::config()
{

    mCfg.maxPeers = mMaxPeersSpinBox->value();
    mCfg.stopRatio = mStopRatioSpinBox->value();
    mCfg.cryptoSupport = DlBtConfig::Type(mCryptoSupportComboBox->currentIndex());
    mCfg.enableDht = mEnableDhtCheckBox->isChecked();
    mCfg.enablePex = mEnablePexCheckBox->isChecked();
    mCfg.announceTimeout = mAnnounceTimeoutSpinBox->value();

    return mCfg;

}
