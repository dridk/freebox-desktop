#include "launcherwidget.h"
#include "fsmainwindow.h"
#include "dlmainwindow.h"
LauncherWidget::LauncherWidget(QWidget *parent) :
    QListWidget(parent)
{
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setFlow(QListView::LeftToRight);

    addView(new FSMainWindow);
    addView(new DLMainWindow);


    setWindowTitle("freebox-desktop");
    resize(480,300);
    setIconSize(QSize(80,80));
    setSpacing(10);

    connect(this,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(launch(QModelIndex)));

}

void LauncherWidget::launch(const QModelIndex &index)
{

    if (index.row() < mViews.count()){

        mViews.at(index.row())->show();

    }


}

void LauncherWidget::addView(AbstractMainWindow *view)
{

    mViews.append(view);
    QListWidgetItem * item = new QListWidgetItem;
    item->setText(view->windowTitle());
    item->setIcon(view->windowIcon());
    addItem(item);

}
