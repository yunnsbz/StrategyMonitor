#ifndef STRATEGYDATA_H
#define STRATEGYDATA_H

#include <QString>
#include <QObject>
#include <QMetaType>

struct StrategyData
{
    Q_GADGET
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

#endif // STRATEGYDATA_H
