#include "headerpathwidget.h"
#include <QHBoxLayout>
HeaderPathWidget::HeaderPathWidget( QWidget *parent) :
    QToolBar(parent)
{
    layout()->setContentsMargins(0,0,0,0);

    connect(this,SIGNAL(actionTriggered(QAction*)),this,SLOT(buttonClicked(QAction*)));
}

void HeaderPathWidget::setModel(QStandardItemModel *model)
{
    mModel = model;

}

void HeaderPathWidget::setCurrentIndex(const QModelIndex &index)
{
    clear();
    mCurrentIndex = index;
    QByteArray array = index.data(FileSystemModel::PathRole).toByteArray();
    array = QByteArray::fromBase64(array);

    //convert array to path list as stringList
    QByteArray dirBase64;
    foreach (QByteArray folder, array.split(0x2F))
    {
        if (!folder.isEmpty()) {
            QAction * action = addAction(QString::fromUtf8(folder));
            dirBase64 += QString("/"+folder).toUtf8().toBase64();
            action->setData(dirBase64);

        }

    }

    actions().last()->setDisabled(true);



}

void HeaderPathWidget::buttonClicked(QAction *action)
{

    int total = actions().count();
    int index = actions().indexOf(action);

    if (index == total - 1)
        emit clicked(mCurrentIndex);

    QModelIndex result = mCurrentIndex;
    for (int i=0 ; i< (total-index)-1; ++i)
    {
        result = result.parent();
    }

    emit clicked(result);

}

//void HeaderPathWidget::setPath(const QByteArray &path)
//{
//    mPath = path;
//    QByteArray realPath = QByteArray::fromBase64(path);
//    QStringList list;

//    foreach (QByteArray folder, realPath.split(0x2F))
//    {
//        if (!folder.isEmpty())
//            list.append(QString::fromUtf8(folder));
//    }

//    clear();
//    if (list.isEmpty())
//        return;

//    int start = list.count()-3 > 0 ? list.count()-3 : 0;

//    QByteArray base64Path;

//    for (int i= start; i<list.count(); ++i )
//    {
//        base64Path +=  QString("/"+list.at(i)).toUtf8();

//        QAction * action = addAction(list.at(i));
//        action->setEnabled(list.at(i) != list.last());
//        action->setData(base64Path.toBase64());
//        addSeparator();
//        connect(action,SIGNAL(triggered()),this,SLOT(buttonClicked()));
//    }

//}


//void HeaderPathWidget::buttonClicked()
//{
//    if (sender()->metaObject()->className() != QString("QAction"))
//        return;

//    QAction * action = qobject_cast<QAction*>(sender());

//   qDebug()<<action->data();
//    emit pathClicked(action->data().toByteArray());

//}
