#include "dlthrottlingconfigwidget.h"

DLThrottlingConfigWidget::DLThrottlingConfigWidget(QWidget *parent) :
    QWidget(parent)
{

    mNormalDLSpinBox     = new QSpinBox;
    mNormalULSpinBox     = new QSpinBox;
    mSlowDLSpinBox        = new QSpinBox;
    mSlowULSpinBox        = new QSpinBox;
    mNormalModeButton    = new QRadioButton;
    mSlowModeButton      = new QRadioButton;
    mHibernateModeButton = new QRadioButton;
    mScheduleModeButton  = new QRadioButton;
    mScheduleTableWidget = new DLScheduleTableWidget;
    mLabel               = new QLabel;
    mHibernateButton     = new QPushButton("Désactivé");
    mSlowButton          = new QPushButton("Vitesse réduite");
    mNormalButton        = new QPushButton("Normal");
    mButtonsGroup        = new QButtonGroup;

    mNormalModeButton->setText("Forcer en mode normal");
    mSlowModeButton->setText("Forcer en mode réduit");
    mHibernateModeButton->setText("Désactiver les transferts");
    mScheduleModeButton->setText("Utiliser la planification");
    mNormalDLSpinBox->setSuffix(" ko/s");
    mNormalULSpinBox->setSuffix(" ko/s");
    mSlowDLSpinBox->setSuffix(" ko/s");
    mSlowULSpinBox->setSuffix(" ko/s");
    mNormalDLSpinBox->setSpecialValueText("illimité");
    mNormalULSpinBox->setSpecialValueText("illimité");
    mSlowDLSpinBox->setSpecialValueText("illimité");
    mSlowULSpinBox->setSpecialValueText("illimité");

    mSlowDLSpinBox->setRange(0,100000);
    mSlowULSpinBox->setRange(0,100000);
    mNormalDLSpinBox->setRange(0,100000);
    mNormalULSpinBox->setRange(0,100000);

    //Creation des icons couleurs pour les 3 buttons
    QPixmap pix(32,32);
    pix.fill(mScheduleTableWidget->typeColors().at(0));
    mNormalButton->setIcon(QIcon(pix));
    pix.fill(mScheduleTableWidget->typeColors().at(1));
    mSlowButton->setIcon(QIcon(pix));
    pix.fill(mScheduleTableWidget->typeColors().at(2));
    mHibernateButton->setIcon(QIcon(pix));


    mNormalButton->setCheckable(true);
    mNormalButton->setChecked(true);
    mSlowButton->setCheckable(true);
    mHibernateButton->setCheckable(true);

    mButtonsGroup->addButton(mNormalButton);
    mButtonsGroup->addButton(mSlowButton);
    mButtonsGroup->addButton(mHibernateButton);

    connect(mButtonsGroup,SIGNAL(buttonClicked(int)),
            this,SLOT(setCurrentScheduleType(int)));


    QFormLayout * mainLayout = new QFormLayout;
    QGridLayout * radioLayout = new QGridLayout;

    radioLayout->addWidget(mScheduleModeButton, 0,0);
    radioLayout->addWidget(mSlowModeButton, 1,0);
    radioLayout->addWidget(mHibernateModeButton, 0,1);
    radioLayout->addWidget(mNormalModeButton, 1,1);
    //    radioLayout->setAlignment(Qt::AlignLeft);


    QHBoxLayout * normalLayout = new QHBoxLayout;
    normalLayout->addWidget(new QLabel("Download:"));
    normalLayout->addWidget(mNormalDLSpinBox);
    normalLayout->addWidget(new QLabel("Upload:"));
    normalLayout->addWidget(mNormalULSpinBox);
    //    normalLayout->setAlignment(Qt::Align);

    QHBoxLayout * lowLayout = new QHBoxLayout;
    lowLayout->addWidget(new QLabel("Download:"));
    lowLayout->addWidget(mSlowDLSpinBox);
    lowLayout->addWidget(new QLabel("Upload:"));
    lowLayout->addWidget(mSlowULSpinBox);
    //    lowLayout->setAlignment(Qt::AlignLeft);

    QHBoxLayout * buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(mHibernateButton);
    buttonsLayout->addWidget(mSlowButton);
    buttonsLayout->addWidget(mNormalButton);
    mLabel->setWordWrap(true);
    mLabel->setText("Vous pouvez définir le mode de téléchargement à appliquer "
                    "en fonction des plages horaires en coloriant le tableau ci-dessous."
                    "Séléctionnez le mode de planification en cliquant sur les boutons sous "
                    "le tableau, puis cliquez sur les case du tableau pour appliquer.");

    mainLayout->addRow("Normal", normalLayout);
    mainLayout->addRow("Réduit", lowLayout);
    mainLayout->addRow("Mode de planification:", radioLayout);

    QVBoxLayout * layout  =new QVBoxLayout;
    layout->addLayout(mainLayout);
    layout->addWidget(mLabel);
    layout->addWidget(mScheduleTableWidget);
    layout->addLayout(buttonsLayout);


    setLayout(layout);



    setWindowTitle("Limites de vitesse");
}

const DlThrottlingConfig &DLThrottlingConfigWidget::config()
{
    mCfg.normal.rxRate = mNormalDLSpinBox->value() / 1000;
    mCfg.normal.txRate = mNormalULSpinBox->value() / 1000;
    mCfg.slow.rxRate = mSlowULSpinBox->value() / 1000;
    mCfg.slow.txRate = mSlowDLSpinBox->value() / 1000;
    mCfg.schedule = mScheduleTableWidget->schendule();
    DlThrottlingConfig::Mode mode;
    if (mNormalButton->isChecked())
        mode =  DlThrottlingConfig::NormalMode;

    if (mSlowModeButton->isChecked())
        mode =  DlThrottlingConfig::SlowMode;

    if (mHibernateModeButton->isChecked())
        mode =  DlThrottlingConfig::HibernateMode;

    if (mScheduleModeButton->isChecked())
        mode =  DlThrottlingConfig::ScheduleMode;

    mCfg.mode = mode;



    return mCfg;
}

void DLThrottlingConfigWidget::setConfig(const DlThrottlingConfig &cfg)
{

    mCfg = cfg;
    mNormalDLSpinBox->setValue(cfg.normal.rxRate/1000);
    mNormalULSpinBox->setValue(cfg.normal.txRate/1000);

    mSlowDLSpinBox->setValue(cfg.slow.rxRate/1000);
    mSlowULSpinBox->setValue(cfg.slow.txRate/1000);
    //    enum Mode {NormalMode, SlowMode, HibernateMode, ScheduleMode};

    switch (cfg.mode)
    {
    case DlThrottlingConfig::NormalMode :
        mNormalModeButton->setChecked(true); break;

    case DlThrottlingConfig::SlowMode :
        mSlowModeButton->setChecked(true); break;

    case DlThrottlingConfig::HibernateMode :
        mHibernateModeButton->setChecked(true); break;

    case DlThrottlingConfig::ScheduleMode :
        mScheduleModeButton->setChecked(true); break;

    }

    mScheduleTableWidget->setSchedule(cfg.schedule);


}

void DLThrottlingConfigWidget::setCurrentScheduleType(int id)
{

    if (mHibernateButton == mButtonsGroup->button(id))
        mScheduleTableWidget->setCurrentType(DlThrottlingConfig::HibernateType);

    if (mSlowButton == mButtonsGroup->button(id))
        mScheduleTableWidget->setCurrentType(DlThrottlingConfig::SlowType);

    if (mNormalButton == mButtonsGroup->button(id))
        mScheduleTableWidget->setCurrentType(DlThrottlingConfig::NormalType);

}
