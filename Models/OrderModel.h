#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "OrderData.h"

using StrategyNameResolver = std::function<QString(int strategyId)>;

class OrderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        StrategyNameRole    = Qt::UserRole + 1,
        OrderIdRole         = Qt::UserRole + 2,
        BuySellRole         = Qt::UserRole + 3,
        PriceRole           = Qt::UserRole + 4,
        VolumeRole          = Qt::UserRole + 5,
        RawDataRole         = Qt::UserRole + 6,
    };

    // header data:
    static const QMap<int, QString> kHeaderLabels;

    explicit OrderModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setStrategyNameResolver(StrategyNameResolver resolver);

    void loadOrders(const QList<OrderData> &orders);
    void addOrder(const OrderData &order);
    void updateOrder(const OrderData &order); // unique_order_id ile bulup günceller
    void clearOrders();

private:
    QList<OrderData> m_orders;

    int ColumnCount = 5;

    StrategyNameResolver m_nameResolver;
};

#endif // ORDERMODEL_H
