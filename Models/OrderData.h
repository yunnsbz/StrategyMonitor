#ifndef ORDERDATA_H
#define ORDERDATA_H

#include <QObject>
#include <QMetaType>

struct OrderData {
    Q_GADGET // Qt meta veri sistemi için Q_GADGET kullanıyoruz (QObject türetmesi gerekmez)
public:
    int unique_order_id;
    int unique_strategy_id;
    double price;
    double active_volume;
    double filled_volume;

    enum class Side : char { Buy, Sell };
    Q_ENUM(Side) // Side enum'unu Qt meta veri sistemine kaydeder

    Side side;
};

// OrderData'yı QVariant ile kullanılabilir hale getirmek için meta tip kaydı
Q_DECLARE_METATYPE(OrderData)

#endif // ORDERDATA_H
