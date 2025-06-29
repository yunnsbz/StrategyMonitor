#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "MockDataGenerator.h"

#include <QObject>
#include <QAbstractItemModel>

class StrategiesViewModel;
class OrdersViewModel;

class MainViewModel : public QObject
{
    Q_OBJECT

public:
    MainViewModel();

    QAbstractItemModel* strategiesModel();
    QAbstractItemModel* ordersModel();

    // filtreler:

    // eğer strateji seçili değilse ekler seçili ise çıkartır.
    void setStrategySelected(int strategy_id);
    QSet<QString> getSelectedStrategyNames();

    void setPriceFilter(double min, double max);
    QPair<double,double> getOrdersPriceRange();
    void clearPriceFilter();

    void setVolumeFilter(double min, double max);
    void clearVolumeFilter();

    void setStrategyStateFilter(QString state);
    void clearStrategyFilter();

public slots:
    void onOrderDataReceived(const class OrderData& order);
    void onStrategyDataReceived(const class StrategyData& strategy);

private:
    MockDataGenerator* DataGenerator;

    StrategiesViewModel* StrategiesVM;
    OrdersViewModel* OrdersVM;

    QSet<int> m_selectedStrategies;
};

#endif // MAINVIEWMODEL_H
