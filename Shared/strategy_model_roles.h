#ifndef STRATEGY_MODEL_ROLES_H
#define STRATEGY_MODEL_ROLES_H

#include <QObject>

namespace StrategyRoles
{
    Q_NAMESPACE

    enum Role {
        IdRole      = Qt::UserRole + 1,
        NameRole    = Qt::UserRole + 2,
        TypeRole    = Qt::UserRole + 3,
        StateRole   = Qt::UserRole + 4,
        RawDataRole = Qt::UserRole + 5,
    };
    Q_ENUM_NS(Role)
}

#endif // STRATEGY_MODEL_ROLES_H
