#ifndef DLFEEDCONFIGWIDGET_H
#define DLFEEDCONFIGWIDGET_H

#include <QtWidgets>

class DLFeedConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DLFeedConfigWidget(QWidget *parent = 0);
    void setFetchInterval(int interval);
    void setMaxItems(int max);
    
signals:
    
public slots:

private:
    QSpinBox* mFetchIntervalBox;
    QSpinBox* mMaxItemsBox;
    
};

#endif // DLFEEDCONFIGWIDGET_H
