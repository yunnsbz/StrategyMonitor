#ifndef STRATEGYDATA_H
#define STRATEGYDATA_H

#include <QString>

struct StrategyData
{
    int unique_strategy_id;
    enum class Type { StrategyType1, StrategyType2 } type;
    QString strategy_name;
    enum class State : char { Paused, Running } state;

    bool operator==(const StrategyData& oth) {
        return unique_strategy_id == oth.unique_strategy_id;
    }
};

#endif // STRATEGYDATA_H
