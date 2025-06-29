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

void StrategiesViewModel::setStrategySelected(QVariant data)
{
    if (!data.canConvert<StrategyData>()) {
        qDebug() << "setStrategySelected > StrategyData çevirme başarısız";
        return;
    }
    StrategyData strategy = data.value<StrategyData>();
    if(m_selectedStrategies.contains(strategy))
        m_selectedStrategies.remove(strategy);
    else
        m_selectedStrategies.insert(strategy);
}

QSet<int> StrategiesViewModel::getSelectedStrategyIds()
{
    QSet<int> idSet;

    for (const StrategyData& strategy : m_selectedStrategies) {
        idSet.insert(strategy.unique_strategy_id);
    }
    return idSet;
}

QSet<QString> StrategiesViewModel::getSelectedStrategyNames()
{
    QSet<QString> selectedNames;
    for(StrategyData strategy : m_selectedStrategies){
        QString name = getStrategy(strategy.unique_strategy_id).strategy_name;
        if(!name.isEmpty()){
            selectedNames.insert(name);
        }
    }
    return selectedNames;
}

void StrategiesViewModel::setStrategyStateFilter(QString state)
{
    filter()->setSelectedState(state);
}

void StrategiesViewModel::clearStrategyFilter()
{
    filter()->clearStrategyFilter();
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
