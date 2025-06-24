#ifndef ORDERDATA_H
#define ORDERDATA_H

struct OrderUpdate {
    int unique_order_id;
    int unique_strategy_id;
    double price;
    double active_volume;
    double filled_volume;
    enum class Side : char { Buy, Sell } side;

    bool operator==(const OrderUpdate& oth) {
        return unique_strategy_id == oth.unique_strategy_id && unique_order_id == oth.unique_order_id;
    }
};

#endif // ORDERDATA_H
