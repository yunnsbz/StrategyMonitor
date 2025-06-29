#include "StrategyFilterProxyModel.h"

#include <utility>
#include "strategy_model_roles.h"


StrategyFilterProxyModel::StrategyFilterProxyModel(QObject *parent)
    :
    QSortFilterProxyModel(parent)
{

}

void StrategyFilterProxyModel::setSelectedState(QString state)
{
    m_selectedState = std::move(state);
    m_strategyFilterActive = true;
    invalidateFilter();
}

void StrategyFilterProxyModel::clearStrategyFilter()
{
    m_strategyFilterActive = false;
    invalidateFilter();
}

bool StrategyFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if(m_strategyFilterActive){
        const QModelIndex stateIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString state = sourceModel()->data(stateIndex, StrategyRoles::StateRole).toString();

        return state == m_selectedState;
    }
    else {
        return true;
    }
}
