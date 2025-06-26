#include "MainViewModel.h"
#include "OrderData.h"
#include "StrategyData.h"
#include "StrategiesViewModel.h"


#include <QDebug>

MainViewModel::MainViewModel()
    :
    DataGenerator(new MockDataGenerator()),
    StrategiesVM(new StrategiesViewModel()),
    OrdersVM(new OrdersViewModel())
{
    connect(DataGenerator, &MockDataGenerator::strategyUpdateGenerated, this, &MainViewModel::onStrategyDataReceived);
    connect(DataGenerator, &MockDataGenerator::orderUpdateGenerated, this, &MainViewModel::onOrderDataReceived);
}

QAbstractItemModel* MainViewModel::strategiesModel()
{
    return StrategiesVM->model();
}

QAbstractItemModel *MainViewModel::ordersModel()
{
    return OrdersVM->model();
}

void MainViewModel::SetStrategySelected(int strategy_id)
{
    SelectedStrategies.insert(strategy_id);
}

void MainViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    StrategiesVM->addStrategy(strategy);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{
    OrdersVM->addOrder(order);
}
