#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include "MockDataGenerator.h"

#include <QObject>

class OrderData;
class StrategyData;
class StrategiesViewModel;
class OrdersViewModel;

class DataReceiver : public QObject
{
    Q_OBJECT

public:
    DataReceiver(StrategiesViewModel* StrategiesVM, OrdersViewModel* OrdersVM);

public slots:
    void onOrderDataReceived(const OrderData& order);
    void onStrategyDataReceived(const StrategyData& strategy);

private:
    MockDataGenerator* m_dataGenerator;

    StrategiesViewModel* m_strategiesVM;
    OrdersViewModel* m_ordersVM;
};

#endif // DATARECEIVER_H
