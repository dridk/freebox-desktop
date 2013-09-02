#include "dlcategorywidget.h"

DLCategoryWidget::DLCategoryWidget(QWidget *parent) :
    QWidget(parent)
{
    mCateogryView = new QTreeWidget;

    QVBoxLayout * layout = new QVBoxLayout;
    setLayout(layout);

    layout->addWidget(mCateogryView);
    layout->setContentsMargins(0,0,0,0);

    QFont font;
    font.setBold(true);


    QTreeWidgetItem * torrentRootItem = new QTreeWidgetItem;
    torrentRootItem->setText(0,"Téléchargements");
    torrentRootItem->setFlags(Qt::ItemIsEnabled);
    torrentRootItem->setFont(0,font);

    QTreeWidgetItem * allItem = new QTreeWidgetItem;
    QTreeWidgetItem * downloadingItem = new QTreeWidgetItem;
    QTreeWidgetItem * seedingItem = new QTreeWidgetItem;
    QTreeWidgetItem * doneItem = new QTreeWidgetItem;

    allItem->setText(0,"Tous");
    allItem->setIcon(0,QIcon(":drive-harddisk.png"));
    allItem->setData(0,Qt::UserRole,"");
    downloadingItem->setText(0,"En Cours");
    downloadingItem->setIcon(0, QIcon(":downloading"));
    downloadingItem->setData(0,Qt::UserRole,"downloading");

    seedingItem->setText(0,"Partagés");
    seedingItem->setIcon(0, QIcon(":seeding"));
    seedingItem->setData(0,Qt::UserRole,"seeding");

    doneItem->setText(0,"Terminés");
    doneItem->setIcon(0, QIcon(":done"));
    doneItem->setData(0,Qt::UserRole,"done");

    mCateogryView->addTopLevelItem(torrentRootItem);

    torrentRootItem->addChild(allItem);
    torrentRootItem->addChild(downloadingItem);
    torrentRootItem->addChild(seedingItem);
    torrentRootItem->addChild(doneItem);
    mCateogryView->expandAll();
    mCateogryView->setRootIsDecorated(false);
    torrentRootItem->setSizeHint(0, QSize(0,30));

    connect(mCateogryView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));


//    QListWidgetItem * titleItem = new QListWidgetItem(QIcon(),"Téléchargements");
//    titleItem->setFlags(Qt::NoItemFlags);
//    titleItem->setFont(font);
////    titleItem->setSizeHint(QSize(0,40));
//    mCateogryView->addItem(titleItem);
//    mCateogryView->addItem(new QListWidgetItem(QIcon(""),"Tous"));
//    mCateogryView->addItem(new QListWidgetItem(QIcon(":arrow_up.png"),"En cours"));
//    mCateogryView->addItem(new QListWidgetItem(QIcon(":share.png"),"Partagés"));
//    mCateogryView->addItem(new QListWidgetItem(QIcon(":accept")," Terminés"));

//    QListWidgetItem * rssItem = new QListWidgetItem(QIcon(),"Flux RSS");
//    rssItem->setFlags(Qt::NoItemFlags);
//    rssItem->setFont(font);
//    mCateogryView->addItem(rssItem);
            //    mCateogryView->addItem(new QListWidgetItem(QIcon(":rss.png")," RSS"));
}

void DLCategoryWidget::itemClicked(const QModelIndex &index)
{

    emit statusClicked(index.data(Qt::UserRole).toString());

}
