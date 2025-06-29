#include "StrategyModel.h"
#include "strategy_model_roles.h"

StrategyModel::StrategyModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int StrategyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_strategies.size();
}

QVariant StrategyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_strategies.size())
        return {};

    const StrategyData &s = m_strategies.at(index.row());

    switch (role) {
    case StrategyRoles::IdRole:
        return s.unique_strategy_id;
    case StrategyRoles::NameRole:
        return s.strategy_name;
    case StrategyRoles::TypeRole:
        return (s.type == StrategyData::Type::StrategyType1 ? "StrategyType1" : "StrategyType2");
    case StrategyRoles::StateRole:
        return (s.state == StrategyData::State::Running ? "Running" : "Paused");
    case StrategyRoles::RawDataRole:
        return QVariant::fromValue(s);
    default:
        return {};
    }
}

auto StrategyModel::roleNames() const -> QHash<int, QByteArray>
{
    return {
        { StrategyRoles::IdRole, "unique_strategy_id" },
        { StrategyRoles::NameRole, "strategy_name" },
        { StrategyRoles::TypeRole, "type" },
        { StrategyRoles::StateRole, "state" }
    };
}

void StrategyModel::addStrategy(const StrategyData &strategy)
{
    beginInsertRows(QModelIndex(), m_strategies.size(), m_strategies.size());
    m_strategies.append(strategy);
    endInsertRows();
}

StrategyData StrategyModel::getStrategy(int targetId) const
{
    auto it = std::find_if(m_strategies.begin(), m_strategies.end(),
        [targetId](const StrategyData& strategy) {
            return strategy.unique_strategy_id == targetId;
        });

    if (it != m_strategies.end()) {
        return *it; // Bulunan OrderData'yı döndür
    }
    return {};
}
