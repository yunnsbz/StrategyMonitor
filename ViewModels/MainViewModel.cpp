#include "MainViewModel.h"
#include "OrderData.h"


#include <QDebug>

MainViewModel::MainViewModel()
    :
    DataGenerator(new MockDataGenerator())
{

    connect(DataGenerator, &MockDataGenerator::orderUpdateGenerated, this, &MainViewModel::onOrderDataReceived);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{
    qDebug() << "--------order--------";
    qDebug() << "strateji id: " << order.unique_strategy_id;
    qDebug() << "order id: " << order.unique_order_id;
}
