#include "MainViewModel.h"
#include "OrderData.h"
#include "StrategyData.h"
#include "StrategiesViewModel.h"


#include <QDebug>

MainViewModel::MainViewModel()
    :
    DataGenerator(new MockDataGenerator()),
    StrategiesVM(new StrategiesViewModel())
{
    connect(DataGenerator, &MockDataGenerator::strategyUpdateGenerated, this, &MainViewModel::onStrategyDataReceived);
    connect(DataGenerator, &MockDataGenerator::orderUpdateGenerated, this, &MainViewModel::onOrderDataReceived);
}

QAbstractItemModel* MainViewModel::strategiesModel()
{
    return StrategiesVM->model();
}

void MainViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    StrategiesVM->addStrategy(strategy);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{

}
