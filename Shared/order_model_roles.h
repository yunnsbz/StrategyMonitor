#ifndef ORDER_MODEL_ROLES_H
#define ORDER_MODEL_ROLES_H

#include <QObject>

namespace OrderRoles
{
    Q_NAMESPACE
    /**
     * you can change the values here and the order of the table column will change accordingly.
     */
    enum Role {
        StrategyNameRole    = Qt::UserRole + 1,
        OrderIdRole         = Qt::UserRole + 2,
        BuySellRole         = Qt::UserRole + 3,
        PriceRole           = Qt::UserRole + 4,
        FilledVolumeRole    = Qt::UserRole + 5,
        ActiveVolumeRole    = Qt::UserRole + 6,
        RawDataRole         = Qt::UserRole + 7,
    };
    Q_ENUM_NS(Role)
}

#endif // ORDER_MODEL_ROLES_H
