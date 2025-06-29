
#include "MockDataGenerator.h"
#include "OrderData.h"
#include "StrategyData.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QVector>


int MockDataGenerator::currentStrategytId = 0;
int MockDataGenerator::currentOrderId = 0;

MockDataGenerator::MockDataGenerator()
    :
    m_orderTimer(new QTimer(this)),
    m_strategyTimer(new QTimer(this))
{
    connect(m_strategyTimer, &QTimer::timeout, this, &MockDataGenerator::onStrategyTimerTimeout);

    m_strategyTimer->start(m_strategyInterval);

    connect(m_orderTimer, &QTimer::timeout, this, &MockDataGenerator::onOrderTimerTimeout);

    m_orderTimer->start(m_orderInterval);
}

void MockDataGenerator::onStrategyTimerTimeout()
{
    const StrategyData data = createStrategy();

    emit strategyUpdateGenerated(data);
}

void MockDataGenerator::onOrderTimerTimeout()
{
    const OrderData data = createOrder();

    emit orderUpdateGenerated(data);
}

StrategyData MockDataGenerator::createStrategy()
{
    currentStrategytId++;

    // type
    const auto type = static_cast<StrategyData::Type>(
        QRandomGenerator::global()->bounded(0, 2));

    // state
    const auto state = static_cast<StrategyData::State>(
        QRandomGenerator::global()->bounded(0, 2));

    // isim seçimi
    const QVector<QString> namePool = {
        "Alpha", "Beta", "Gamma", "Delta", "Omega",
        "Zeta", "Sigma", "Kappa", "Echo", "Nova"
    };
    const QString strategyName = namePool[QRandomGenerator::global()->bounded(namePool.size())] + QString::number(currentStrategytId);

    StrategyData data;
    data.unique_strategy_id = currentStrategytId;
    data.type = type;
    data.state = state;
    data.strategy_name = strategyName;
    return data;
}

OrderData MockDataGenerator::createOrder()
{
    currentOrderId++;

    // side
    const OrderData::Side side = static_cast<OrderData::Side>(
        QRandomGenerator::global()->bounded(0, 2));

    const double price = QRandomGenerator::global()->generateDouble() * 1500;
    const double active_volume = QRandomGenerator::global()->generateDouble() * 1000;
    const double filled_volume = QRandomGenerator::global()->generateDouble() * active_volume;

    int order_id = 0;
    if(currentStrategytId > 0)
        order_id = QRandomGenerator::global()->bounded(1,currentStrategytId+1);

    OrderData data;
    data.unique_strategy_id = order_id;
    data.unique_order_id = currentOrderId;
    data.side = side;
    data.price = price;
    data.filled_volume = filled_volume;
    data.active_volume = active_volume;
    return data;
}
