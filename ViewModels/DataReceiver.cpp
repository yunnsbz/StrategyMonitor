#include "DataReceiver.h"
#include "OrderData.h"
#include "StrategyData.h"
#include "StrategiesViewModel.h"
#include "OrdersViewModel.h"

#include <QDebug>

DataReceiver::DataReceiver(StrategiesViewModel* StrategiesVM, OrdersViewModel* OrdersVM)
    :
    m_dataGenerator(new MockDataGenerator()),
    m_ordersVM(OrdersVM),
    m_strategiesVM(StrategiesVM)
{
    connect(m_dataGenerator, &MockDataGenerator::strategyUpdateGenerated, this, &DataReceiver::onStrategyDataReceived);
    connect(m_dataGenerator, &MockDataGenerator::orderUpdateGenerated, this, &DataReceiver::onOrderDataReceived);
}

void DataReceiver::onStrategyDataReceived(const StrategyData &strategy)
{
    m_strategiesVM->addStrategy(strategy);
}

void DataReceiver::onOrderDataReceived(const OrderData &order)
{
    m_ordersVM->addOrder(order);
}
