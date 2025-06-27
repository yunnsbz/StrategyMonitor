#include "OrderModel.h"


OrderModel::OrderModel(QObject *parent)
    :
    QAbstractTableModel(parent)
{
}

int OrderModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_orders.count();
}

int OrderModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return ColumnCount;
}

QVariant OrderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_orders.count() || index.row() < 0)
        return QVariant();

    const OrderData &order = m_orders.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (static_cast<Column>(index.column())) {
            case StrategyName:
                return m_strategyNameCache[order.unique_strategy_id];
            case OrderId:
                return QString::number(order.unique_order_id).rightJustified(3, '0');
            case BuySell:
                return (order.side == OrderData::Side::Buy ? "Buy" : "Sell");
            case Price:
                return QString::number(order.price, 'f', 2) + "$";
            case Volume:
                return QString("%1/%2")
                    .arg(QString::number(order.filled_volume, 'f', 0), QString::number(order.active_volume, 'f', 0));
            default:
                return QVariant();
        }
    }
    else if (role == Qt::UserRole) {
        return QVariant::fromValue(order); // OrderData nesnesini QVariant olarak döndür
    }
    return QVariant();
}

QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (static_cast<Column>(section)) {
            case StrategyName:
                return QStringLiteral("Strategy Name");
            case OrderId:
                return QStringLiteral("Order ID");
            case BuySell:
                return QStringLiteral("Buy/Sell");
            case Price:
                return QStringLiteral("Price");
            case Volume:
                return QStringLiteral("Volume (Filled/Active)");
            default:
                return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void OrderModel::loadOrders(const QList<OrderData> &orders)
{
    beginResetModel();
    m_orders = orders;
    endResetModel();
}

void OrderModel::addOrder(const OrderData &order, QString strategyName)
{
    int newRow = m_orders.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
    m_orders.append(order);
    endInsertRows();
    m_strategyNameCache[order.unique_strategy_id] = strategyName;
}

void OrderModel::updateOrder(const OrderData &updatedOrder)
{
    for (int i = 0; i < m_orders.count(); ++i) {
        if (m_orders[i].unique_order_id == updatedOrder.unique_order_id) {
            m_orders[i] = updatedOrder;
            // Sadece değişen satırın güncellenmesi için dataChanged sinyali
            emit dataChanged(index(i, 0), index(i, ColumnCount - 1));
            return;
        }
    }
}

void OrderModel::clearOrders()
{
    if (m_orders.isEmpty()) return;
    beginResetModel();
    m_orders.clear();
    endResetModel();
}
