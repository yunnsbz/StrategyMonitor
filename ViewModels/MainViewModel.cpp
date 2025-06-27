#include "MainViewModel.h"
#include "OrderData.h"
#include "StrategyData.h"
#include "StrategiesViewModel.h"
#include "OrdersViewModel.h"
#include "OrderFilterProxyModel.h"


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
    if(SelectedStrategies.contains(strategy_id)){
        SelectedStrategies.remove(strategy_id);
    }
    else SelectedStrategies.insert(strategy_id);
    OrdersVM->filter()->setSelectedStrategyIds(SelectedStrategies);
}

void MainViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    StrategiesVM->addStrategy(strategy);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{
    auto strategy = StrategiesVM->getStrategy(order.unique_strategy_id);
    OrdersVM->addOrder(order, strategy.strategy_name);
}
