#include "dlnewsgroupconfigwidget.h"

DLNewsGroupConfigWidget::DLNewsGroupConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    mServerEdit          = new QLineEdit;
    mPortSpinBox         = new QSpinBox;
    mSslCheckBox         = new QCheckBox;
    mNThtreadsSpinBox    = new QSpinBox;
    mUserEdit            = new QLineEdit;
    mPasswordEdit        = new QLineEdit;
    mLazyPar2CheckBox    = new QCheckBox;
    mAutoRepairCheckBox  = new QCheckBox;
    mAutoExtractCheckBox = new QCheckBox;
    mEraseTmpCheckBox    = new QCheckBox;


    mPortSpinBox->setRange(0,65000);
    mNThtreadsSpinBox->setRange(1,30);

    //---------first box ----------------------
    QGroupBox * serverBox = new QGroupBox;
    serverBox->setTitle("Serveur de news");

    QFormLayout * serverLayout = new QFormLayout;
    serverLayout->addRow("Serveur :", mServerEdit);
    serverLayout->addRow("Port :",mPortSpinBox);
    serverLayout->addRow("Nombre de connexions : ", mNThtreadsSpinBox);
    serverLayout->addRow("Utiliser SSL :", mSslCheckBox);
    serverBox->setLayout(serverLayout);



    //---------second box ----------------------
    QGroupBox * idBox = new QGroupBox;
    idBox->setTitle("Identification");
    QHBoxLayout * idLayout = new QHBoxLayout;
    idLayout->addWidget(new QLabel("Utilisateur:   "));
    idLayout->addWidget(mUserEdit);
    idLayout->addWidget(new QLabel("Mot de passe:   "));
    idLayout->addWidget(mPasswordEdit);



    idBox->setLayout(idLayout);


    //---------third box ----------------------
    QGroupBox * prefBox = new QGroupBox;
    prefBox->setTitle("Préférences");
    QFormLayout * prefLayout  = new QFormLayout;
    prefLayout->addRow("Ne pas télécharger les par2 si non nécessaires :", mLazyPar2CheckBox);
    prefLayout->addRow("Réparation automatique :", mAutoRepairCheckBox);
    prefLayout->addRow("Extraction automatique :", mAutoExtractCheckBox);
    prefLayout->addRow("Supprimer les fichiers après extraction :", mEraseTmpCheckBox);
    prefBox->setLayout(prefLayout);


    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(serverBox);
    mainLayout->addWidget(idBox);
    mainLayout->addWidget(prefBox);
    mainLayout->addStretch();

    setLayout(mainLayout);

    setWindowTitle("Newsgroups");


}

DLNewsGroupConfigWidget::~DLNewsGroupConfigWidget()
{
    delete mServerEdit;
    delete mPortSpinBox;
    delete mSslCheckBox;
    delete mNThtreadsSpinBox;
    delete mUserEdit;
    delete mPasswordEdit;
    delete mLazyPar2CheckBox;
    delete mAutoRepairCheckBox;
    delete mAutoExtractCheckBox;
    delete mEraseTmpCheckBox;
}

void DLNewsGroupConfigWidget::setConfig(const DlNewsConfig &cfg)
{
    mCfg = cfg;
    mServerEdit->setText(cfg.server);
    mPortSpinBox->setValue(cfg.port);
    mSslCheckBox->setChecked(cfg.ssl);
    mNThtreadsSpinBox->setValue(cfg.nthreads);
    mUserEdit->setText(cfg.user);
    mPasswordEdit->setText(cfg.password);
    mLazyPar2CheckBox->setChecked(cfg.lazyPar2);
    mAutoRepairCheckBox->setChecked(cfg.autoRepair);
    mAutoExtractCheckBox->setChecked(cfg.autoExtract);
    mEraseTmpCheckBox->setChecked(cfg.eraseTmp);
}

const DlNewsConfig &DLNewsGroupConfigWidget::config()
{

    mCfg.server = mServerEdit->text();
    mCfg.port = mPortSpinBox->value();
    mCfg.ssl = mSslCheckBox->isChecked();
    mCfg.nthreads = mNThtreadsSpinBox->value();
    mCfg.user = mUserEdit->text();
    mCfg.password = mPasswordEdit->text();
    mCfg.lazyPar2 = mLazyPar2CheckBox->isChecked();
    mCfg.autoRepair = mAutoRepairCheckBox->isChecked();
    mCfg.autoExtract = mAutoExtractCheckBox->isChecked();
    mCfg.eraseTmp = mEraseTmpCheckBox->isChecked();

    return mCfg;







}
