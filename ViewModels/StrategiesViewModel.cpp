#include "StrategiesViewModel.h"
#include "StrategyData.h"

#include <QDebug>


StrategiesViewModel::StrategiesViewModel(QObject *parent)
    :
    QObject(parent),
    m_model(new StrategyModel(this)),
    DataGenerator(new MockDataGenerator())
{
    connect(DataGenerator, &MockDataGenerator::strategyUpdateGenerated, this, &StrategiesViewModel::onStrategyDataReceived);
}

void StrategiesViewModel::onStrategyDataReceived(const StrategyData &strategy)
{
    qDebug() << "--------strategy--------";
    qDebug() << "strateji name: " << strategy.strategy_name;

    m_model->addStrategy(strategy);
}

StrategyModel* StrategiesViewModel::model() const {
    return m_model;
}

void StrategiesViewModel::addStrategy(const StrategyData& data) {
    m_model->addStrategy(data);
}
