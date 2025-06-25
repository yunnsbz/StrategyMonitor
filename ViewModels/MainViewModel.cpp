#include "MainViewModel.h"
#include "OrderData.h"
#include "StrategyData.h"

#include <QDebug>

MainViewModel::MainViewModel()
    :
    DataGenerator(new MockDataGenerator())
{
    connect(DataGenerator, &MockDataGenerator::strategyUpdateGenerated, this, &MainViewModel::onStrategyDataReceived);
    connect(DataGenerator, &MockDataGenerator::orderUpdateGenerated, this, &MainViewModel::onOrderDataReceived);
}

void MainViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    qDebug() << "--------strategy--------";
    qDebug() << "strateji name: " << strategy.strategy_name;
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{
    qDebug() << "--------order--------";
    qDebug() << "strateji id: " << order.unique_strategy_id;
    qDebug() << "order id: " << order.unique_order_id;
}
