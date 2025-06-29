#include "StrategyFilterProxyModel.h"
#include "strategy_model_roles.h"


StrategyFilterProxyModel::StrategyFilterProxyModel(QObject *parent)
    :
    QSortFilterProxyModel(parent)
{

}

void StrategyFilterProxyModel::SetSelectedState(QString state)
{
    SelectedState = state;
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
        QModelIndex stateIndex = sourceModel()->index(source_row, 0, source_parent);
        QString state = sourceModel()->data(stateIndex, StrategyRoles::StateRole).toString();

        return state == SelectedState;
    }
    else
        return true;
}
