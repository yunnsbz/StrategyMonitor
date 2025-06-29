#ifndef STRATEGYDATA_H
#define STRATEGYDATA_H

#include <QString>

struct StrategyData
{
    int unique_strategy_id;
    enum class Type { StrategyType1, StrategyType2 } type;
    QString strategy_name;
    enum class State : char { Paused, Running } state;
};

#endif // STRATEGYDATA_H
