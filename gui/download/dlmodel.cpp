#include "dlmodel.h"
#include <QIcon>
#include "dlmodel.h"
#include "tools.h" // pour le humanSize...A mettre dans une autre class
DLModel::DLModel(FbxAPI *fbx, QObject *parent):
    QAbstractTableModel(parent)
{
    mFbx = fbx;
    mTimer = new QTimer();
    connect(mFbx->download(),SIGNAL(listReceived(QList<DownloadTask>)),this,SLOT(setData(QList<DownloadTask>)));

    mTimer->setInterval(1000);

    connect(mTimer,SIGNAL(timeout()),mFbx->download(),SLOT(requestList()));

    connect(mFbx,SIGNAL(logoutSuccess()),mTimer,SLOT(stop()));
    connect(mFbx,SIGNAL(logoutSuccess()),this,SLOT(clear()));
    connect(mFbx,SIGNAL(loginSuccess()),this,SLOT(start()));

    //    mDatas.append(DownloadTask());


}

int DLModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mDatas.count();
}

int DLModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 11;
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
        case 3 : return task.size!=0?Tools::humanSize(task.size):""; break;
        case 4 : return task.rxPct; break;
        case 5 : return task.ioPriority; break;
        case 6 : return task.eta.toString("hh 'heures' mm 'mins'"); break;
        case 7 : return task.rxRate!=0 ?Tools::humanSize(task.rxRate)+"/s":""; break;
        case 8 : return task.txRate!=0 ?Tools::humanSize(task.txRate)+"/s":""; break;
        case 9 : return task.createdTs.toString(); break;
        case 10 : return task.status; break;

        }
    }

    if (role == Qt::DecorationRole )
    {
        DownloadTask task = mDatas.at(index.row());

        switch (index.column())
        {
        case 1 :  return QIcon(":"+task.status);
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
        case 9: return "Date d'ajout"; break;
        case 10: return "Status"; break;



        }



    }
    return QVariant();
}

const DownloadTask &DLModel::downloadTask(int row)
{
    return mDatas.at(row);
}

void DLModel::setData(const QList<DownloadTask> &data)
{

    // PAsnox, si tu vois ce code... bein, aide moi a faire un truc beau :D
    //==== SI LA LISTE EST VIDE....
    if (data.isEmpty())
    {
        clear();
        return;
    }

    //================= SUPPRESSION LOCAL
    QList<int> removeIds;
    for (int i=0; i<mDatas.count(); ++i)
    {
        int remoteId =hasId(data, mDatas[i].id);
        if (remoteId == -1)
            removeIds.append(i);
        else {
            mDatas.replace(i ,data.value(remoteId));
            emit dataChanged(index(i,0), index(i, columnCount()-1));
        }

    }

    foreach (int id, removeIds)
    {
        qDebug()<<"SUPPRIMER "<<id;
        beginRemoveRows(QModelIndex(), id, id);
        mDatas.removeAt(id);
        endRemoveRows();
    }



    //================= AJOUT LOCAL
    QList<int> addIds;
    for (int i=0; i<data.count(); ++i)
    {
        if (hasId(mDatas, data[i].id) == -1)
            addIds.append(i);
    }
    foreach (int id, addIds)
    {
        beginInsertRows(QModelIndex(), 0,0);
        mDatas.prepend(data.value(id));
        endInsertRows();
    }

    emit updated();
}

void DLModel::clear()
{
    beginRemoveRows(QModelIndex(),0,mDatas.count());
    mDatas.clear();
    endRemoveRows();
}

int DLModel::hasId(const QList<DownloadTask> &list,int id)
{
    int row=0;
    foreach (DownloadTask task, list)
    {
        if (task.id == id)
            return row;

        row++;
    }

    return -1;
}


