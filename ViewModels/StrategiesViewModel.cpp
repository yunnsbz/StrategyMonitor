#include "StrategiesViewModel.h"
#include "StrategyData.h"
#include "StrategyModel.h"

StrategiesViewModel::StrategiesViewModel(QObject *parent)
    :
    QObject(parent),
    m_model(new StrategyModel(this))
{

}

QAbstractItemModel* StrategiesViewModel::model() const {
    return m_model;
}

void StrategiesViewModel::addStrategy(const StrategyData& data) {
    m_model->addStrategy(data);
}

StrategyData StrategiesViewModel::getStrategy(int targetId) const
{
    return m_model->getStrategy(targetId);
}
