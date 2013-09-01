#include "dlcategorywidget.h"

DLCategoryWidget::DLCategoryWidget(QWidget *parent) :
    QWidget(parent)
{
    mCateogryView = new QListWidget;
    mRssView = new QListWidget;

    QVBoxLayout * layout = new QVBoxLayout;
    setLayout(layout);

    layout->addWidget(mCateogryView);
    layout->setContentsMargins(0,0,0,0);

    QFont font;
    font.setBold(true);

    QListWidgetItem * titleItem = new QListWidgetItem(QIcon(),"Téléchargements");
    titleItem->setFlags(Qt::NoItemFlags);
    titleItem->setFont(font);
//    titleItem->setSizeHint(QSize(0,40));
    mCateogryView->addItem(titleItem);
    mCateogryView->addItem(new QListWidgetItem(QIcon(""),"Tous"));
    mCateogryView->addItem(new QListWidgetItem(QIcon(":arrow_up.png"),"En cours"));
    mCateogryView->addItem(new QListWidgetItem(QIcon(":share.png"),"Partagés"));
    mCateogryView->addItem(new QListWidgetItem(QIcon(":accept")," Terminés"));

    QListWidgetItem * rssItem = new QListWidgetItem(QIcon(),"Flux RSS");
    rssItem->setFlags(Qt::NoItemFlags);
    rssItem->setFont(font);
    mCateogryView->addItem(rssItem);
    mCateogryView->addItem(new QListWidgetItem(QIcon(":rss.png")," RSS"));
}
