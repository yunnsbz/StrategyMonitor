
#include "MockDataGenerator.h"
#include <QDebug>
#include <QRandomGenerator>

MockDataGenerator::MockDataGenerator()
    :
    m_orderTimer(new QTimer(this)),
    m_strategyTimer(new QTimer(this)),

{
    connect(m_strategyTimer, &QTimer::timeout, this, &MockDataGenerator::onStrategyTimerTimeout);

    m_strategyTimer->start(m_strategyInterval);

    connect(m_orderTimer, &QTimer::timeout, this, &MockDataGenerator::onOrderyTimerTimeout);

    m_orderTimer->start(m_orderInterval);
}

void MockDataGenerator::onStrategyTimerTimeout()
{
    const StrategyData data = createStrategy();

    emit strategyUpdateGenerated(data);
}

StrategyData MockDataGenerator::createStrategy()
{
    static int currentId = 0;
    currentId++;

    // type
    StrategyData::Type type = static_cast<StrategyData::Type>(
        QRandomGenerator::global()->bounded(0, 2)); // 0 veya 1

    // state
    StrategyData::State state = static_cast<StrategyData::State>(
        QRandomGenerator::global()->bounded(0, 2)); // 0 veya 1

    // isim seçimi
    QVector<QString> namePool = {
        "Alpha", "Beta", "Gamma", "Delta", "Omega",
        "Zeta", "Sigma", "Kappa", "Echo", "Nova"
    };
    QString strategyName = namePool[QRandomGenerator::global()->bounded(namePool.size())] + QString::number(currentId);

    StrategyData data;
    data.unique_strategy_id = currentId;
    data.type = type;
    data.state = state;
    data.strategy_name = strategyName;
    qDebug() << data.strategy_name;
    return data;
}
