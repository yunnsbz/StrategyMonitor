#include "StrategiesViewModel.h"
#include "StrategyData.h"
#include "StrategyFilterProxyModel.h"
#include "StrategyModel.h"

StrategiesViewModel::StrategiesViewModel(QObject *parent)
    :
    QObject(parent),
    m_model(new StrategyModel(this)),
    m_filteredStrategyModel(new StrategyFilterProxyModel(this))
{
    m_filteredStrategyModel->setSourceModel(m_model);
}

QAbstractItemModel* StrategiesViewModel::model() const
{
    return m_filteredStrategyModel;
}

StrategyFilterProxyModel *StrategiesViewModel::filter() const
{
    return m_filteredStrategyModel;
}

void StrategiesViewModel::addStrategy(const StrategyData& data)
{
    m_model->addStrategy(data);
}

StrategyData StrategiesViewModel::getStrategy(int targetId) const
{
    return m_model->getStrategy(targetId);
}
