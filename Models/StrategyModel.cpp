#include "StrategyModel.h"


StrategyModel::StrategyModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int StrategyModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_strategies.size();
}

QVariant StrategyModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_strategies.size())
        return QVariant();

    const StrategyData &s = m_strategies.at(index.row());

    switch (role) {
    case IdRole:
        return s.unique_strategy_id;
    case NameRole:
        return s.strategy_name;
    case TypeRole:
        return (s.type == StrategyData::Type::StrategyType1 ? "StrategyType1" : "StrategyType2");
    case StateRole:
        return (s.state == StrategyData::State::Running ? "Running" : "Paused");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> StrategyModel::roleNames() const {
    return {
        { IdRole, "unique_strategy_id" },
        { NameRole, "strategy_name" },
        { TypeRole, "type" },
        { StateRole, "state" }
    };
}

void StrategyModel::addStrategy(const StrategyData &strategy) {
    beginInsertRows(QModelIndex(), m_strategies.size(), m_strategies.size());
    m_strategies.append(strategy);
    endInsertRows();
}

StrategyData StrategyModel::getStrategy(int targetId) const {
    auto it = std::find_if(m_strategies.begin(), m_strategies.end(),
        [targetId](const StrategyData& strategy) {
            return strategy.unique_strategy_id == targetId;
        });

    if (it != m_strategies.end()) {
        return *it; // Bulunan OrderData'yı döndür
    }
    return {};
}
