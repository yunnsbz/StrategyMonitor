#ifndef STRATEGY_MODEL_ROLES_H
#define STRATEGY_MODEL_ROLES_H

#include <QObject> // Q_NAMESPACE için gerekli

namespace StrategyRoles { // Namespace kullanarak organize etmek en iyisidir
    Q_NAMESPACE

    enum Role {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TypeRole,
        StateRole
    };
    Q_ENUM_NS(Role) // Bu enum'u Qt'nin meta sistemine kaydeder
}

#endif // STRATEGY_MODEL_ROLES_H
