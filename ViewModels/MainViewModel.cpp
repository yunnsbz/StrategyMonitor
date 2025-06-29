#include "MainViewModel.h"
#include "OrderData.h"
#include "StrategyData.h"
#include "StrategiesViewModel.h"
#include "OrdersViewModel.h"
#include "OrderModel.h"
#include "OrderFilterProxyModel.h"
#include "StrategyFilterProxyModel.h"


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

void MainViewModel::setStrategySelected(int strategy_id)
{
    if(m_selectedStrategies.contains(strategy_id))
        m_selectedStrategies.remove(strategy_id);
    else
        m_selectedStrategies.insert(strategy_id);

    OrdersVM->filter()->setSelectedStrategyIds(m_selectedStrategies);
}

QSet<QString> MainViewModel::getSelectedStrategyNames()
{
    QSet<QString> selectedNames;
    for(int id : m_selectedStrategies){
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

QPair<double, double> MainViewModel::getOrdersPriceRange()
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

void MainViewModel::setStrategyStateFilter(QString state)
{
    StrategiesVM->filter()->SetSelectedState(state);
}

void MainViewModel::clearStrategyFilter()
{
    StrategiesVM->filter()->clearStrategyFilter();
}

void MainViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    StrategiesVM->addStrategy(strategy);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{
    OrdersVM->addOrder(order);
}
