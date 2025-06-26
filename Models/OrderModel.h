#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "OrderData.h"

class OrderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        StrategyName,
        OrderId,
        BuySell,
        Price,
        Volume
    };

    explicit OrderModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void loadOrders(const QList<OrderData> &orders);
    void addOrder(const OrderData &order);
    void updateOrder(const OrderData &order); // unique_order_id ile bulup günceller
    void clearOrders();

private:
    QList<OrderData> m_orders;
    QHash<int, QString> m_strategyNameCache; // Strateji ID'den isme map

    int ColumnCount = 5;
};

#endif // ORDERMODEL_H
