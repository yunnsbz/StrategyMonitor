#ifndef ORDERDATA_H
#define ORDERDATA_H

#include <QObject>
#include <QMetaType>

struct OrderData
{
    Q_GADGET
public:
    int unique_order_id;
    int unique_strategy_id;
    double price;
    double active_volume;
    double filled_volume;

    enum class Side : char { Buy, Sell };
    Q_ENUM(Side)

    Side side;
};

Q_DECLARE_METATYPE(OrderData)

#endif // ORDERDATA_H
