#ifndef STRATEGYDATA_H
#define STRATEGYDATA_H

#include <QString>
#include <QObject>
#include <QMetaType>

struct StrategyData
{
    Q_GADGET
public:
    int unique_strategy_id;
    QString strategy_name;

    enum class Type { StrategyType1, StrategyType2 };
    Q_ENUM(Type)
    Type type;

    enum class State : char { Paused, Running };
    Q_ENUM(State)
    State state;
};

Q_DECLARE_METATYPE(StrategyData)

inline bool operator==(const StrategyData& lhs, const StrategyData& rhs)
{
    return lhs.unique_strategy_id == rhs.unique_strategy_id;
}

inline uint qHash(const StrategyData& key, uint seed = 0)
{
    return qHash(key.unique_strategy_id, seed);
}
#endif // STRATEGYDATA_H
