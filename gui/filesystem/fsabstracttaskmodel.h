#ifndef ABSTRACTTASKMODEL_H
#define ABSTRACTTASKMODEL_H

#include <QAbstractListModel>
#include <QNetworkReply>


class FSAbstractTaskModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        TitleRole = Qt::UserRole+1,
        SubTitleRole,
        ProgressRole,
        MimeIconRole
    };
    explicit FSAbstractTaskModel(QObject *parent = 0);
    virtual int count() = 0;

public slots:
    virtual void clearFinished() = 0;
    virtual void removeTask(const QModelIndex& index) = 0;

signals:
    void countChanged();




    
};

#endif // ABSTRACTTASKMODEL_H
