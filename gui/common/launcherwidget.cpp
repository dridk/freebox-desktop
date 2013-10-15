#include "launcherwidget.h"
#include "fsmainwindow.h"
#include "dlmainwindow.h"
#include "clmainwindow.h"
LauncherWidget::LauncherWidget(QWidget *parent) :
    QListWidget(parent)
{
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setFlow(QListView::LeftToRight);


    setWindowTitle("freebox-desktop");
    resize(480,300);
    setIconSize(QSize(80,80));
    setSpacing(10);


    QListWidgetItem * item1 = new QListWidgetItem;
    item1->setText("Téléchargement");
    item1->setIcon(QIcon(":main_dl.png"));
    addItem(item1);

    QListWidgetItem * item2 = new QListWidgetItem;
    item2->setText("Explorateur de fichiers");
    item2->setIcon(QIcon(":main_fs.png"));
    addItem(item2);

    QListWidgetItem * item3 = new QListWidgetItem;
    item3->setText("Journal d'appels");
    item3->setIcon(QIcon(":main_fs.png"));
    addItem(item3);

    setWindowIcon(QIcon(":myappico.icns"));

    connect(this,SIGNAL(doubleClicked(QModelIndex)), this,SLOT(launch(QModelIndex)));

}

void LauncherWidget::launch(const QModelIndex &index)
{
    if (index.row() == 0)
    {
        DLMainWindow * win = new DLMainWindow;
        win->show();
        return;
    }

    if (index.row() == 1)
    {
        FSMainWindow * win = new FSMainWindow;
        win->show();
        return;
    }

    if (index.row() == 2)
    {
        CLMainWindow * win = new CLMainWindow;
        win->show();
        return;
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
