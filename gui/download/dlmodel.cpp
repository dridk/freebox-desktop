#include "dlmodel.h"
#include <QIcon>
#include "fsmodel.h" // pour le humanSize...A mettre dans une autre class
DLModel::DLModel(FbxAPI *fbx, QObject *parent):
    QAbstractTableModel(parent)
{
    mFbx = fbx;
    mTimer = new QTimer();
    connect(mFbx->download(),SIGNAL(listReceived(QList<DownloadTask>)),this,SLOT(setData(QList<DownloadTask>)));

    mTimer->setInterval(1000);
    connect(mTimer,SIGNAL(timeout()),mFbx->download(),SLOT(requestList()));

    mDatas.append(DownloadTask());


}

int DLModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int DLModel::columnCount(const QModelIndex &parent) const
{
    return 10;
}

QVariant DLModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        DownloadTask task = mDatas.at(index.row());
        switch (index.column())
        {

        case 0 : return task.id; break;
            //        case 1 : return task.status; break;
        case 2 : return task.name; break;
        case 3 : return FSModel::sizeHuman(task.size); break;
        case 4 : return task.rxPct; break;
        case 5 : return task.ioPriority; break;
        case 6 : return task.eta.toString("hh 'heures' mm 'mins'"); break;
        case 7 : return FSModel::sizeHuman(task.rxRate)+"/s"; break;
        case 8 : return FSModel::sizeHuman(task.txRate)+"/s"; break;
        case 9 : return task.createdTs.toString(); break;


        }
    }

    if (role == Qt::DecorationRole )
    {
        DownloadTask task = mDatas.at(index.row());

        switch (index.column())
        {
        case 1 :  return QIcon(":update.png");
        case 5 :  return QIcon(":"+task.ioPriority);

        }


    }



    return QVariant();
}

QVariant DLModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch (section)
        {
        case 0: return "#"; break;
        case 1: return ""; break;
        case 2: return "Nom"; break;
        case 3: return "Taille"; break;
        case 4: return "Progression"; break;
        case 5: return "Priorité"; break;
        case 6: return "Temps restant"; break;
        case 7: return "Réception"; break;
        case 8: return "Emission"; break;




        }



    }
    return QVariant();
}

void DLModel::setData(const QList<DownloadTask> &data)
{
    if (data.isEmpty())
        return;

    if (data.count() != mDatas.count())
    {
        beginResetModel();
        mDatas = data;
        endResetModel();
    }

    else {
        mDatas = data;
        emit dataChanged(index(0,0), index(data.count()-1, columnCount()-1));

    }


    emit updated();







}
