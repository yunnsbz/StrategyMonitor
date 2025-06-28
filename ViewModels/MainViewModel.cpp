#include "MainViewModel.h"
#include "OrderData.h"
#include "StrategyData.h"
#include "StrategiesViewModel.h"
#include "OrdersViewModel.h"
#include "OrderModel.h"
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

    OrdersVM->orderModel()->setStrategyNameResolver([this](int strategyId) -> QString {
        const StrategyData strategy = StrategiesVM->getStrategy(strategyId);
        return strategy.strategy_name.isEmpty() ? QString("[Unknown]") : strategy.strategy_name;
    });
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

QSet<QString> MainViewModel::getStrategiesSelected()
{
    QSet<QString> selectedNames;
    for(int id : SelectedStrategies){
        QString name = StrategiesVM->getStrategy(id).strategy_name;
        if(!name.isEmpty()){
            selectedNames.insert(name);
        }
    }
    return selectedNames;
}

void MainViewModel::setPriceFilter(double min, double max)
{
    OrdersVM->filter()->setPriceFilter(min, max);
}

QPair<double, double> MainViewModel::ordersPriceRange()
{
    return OrdersVM->filter()->ordersPriceRange();
}

void MainViewModel::clearPriceFilter()
{
    OrdersVM->filter()->clearPriceFilter();
}

void MainViewModel::setVolumeFilter(double min, double max)
{
    OrdersVM->filter()->setVolumeFilter(min, max);
}

void MainViewModel::clearVolumeFilter()
{
    OrdersVM->filter()->clearVolumeFilter();
}

void MainViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    StrategiesVM->addStrategy(strategy);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{
    OrdersVM->addOrder(order);
}
