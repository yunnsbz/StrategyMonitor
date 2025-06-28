#include "OrderModel.h"


OrderModel::OrderModel(QObject *parent)
    :
    QAbstractTableModel(parent)
{
}

const QMap<int, QString> OrderModel::kHeaderLabels {
    { StrategyNameRole, "Strategy Name" },
    { OrderIdRole,      "Order ID" },
    { BuySellRole,      "Buy/Sell" },
    { PriceRole,        "Price" },
    { VolumeRole,       "Volume (Filled/Active)" }
};

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

    // tüm itemleri ortalama:
    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    // tableView'in kullanacağı DisplayRole:
    if (role == Qt::DisplayRole) {
        auto keys = kHeaderLabels.keys();
        if (index.column() >= 0 && index.column() < keys.size()) {
            role = keys[index.column()];
        } else {
            return QVariant();
        }
    }

    switch (role) {
        case StrategyNameRole:
            return m_nameResolver(order.unique_strategy_id);
        case OrderIdRole:
            return QString::number(order.unique_order_id).rightJustified(3, '0');
        case BuySellRole:
            return order.side == OrderData::Side::Buy ? "Buy" : "Sell";
        case PriceRole:
            return QString::number(order.price, 'f', 2) + "$";
        case VolumeRole:
            return QString("%1/%2")
                .arg(QString::number(order.filled_volume, 'f', 0),
                     QString::number(order.active_volume, 'f', 0));
        case RawDataRole:
            return QVariant::fromValue(order);
        default:
            return QVariant();
    }

    return QVariant();
}


QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    // key'lerin sırası sütunların sırasını belirtir. key'lerin değeri sütun sırasından bağımsızdır.
    auto keys = kHeaderLabels.keys();
    if (section >= 0 && section < keys.size())
        return kHeaderLabels[keys[section]];

    return QVariant();
}

void OrderModel::setStrategyNameResolver(StrategyNameResolver resolver)
{
    m_nameResolver = resolver;
}

void OrderModel::loadOrders(const QList<OrderData> &orders)
{
    beginResetModel();
    m_orders = orders;
    endResetModel();
}

void OrderModel::addOrder(const OrderData &order)
{
    int newRow = m_orders.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
    m_orders.append(order);
    endInsertRows();
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
