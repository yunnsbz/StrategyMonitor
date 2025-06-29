#include "OrderModel.h"
#include "order_model_roles.h"



OrderModel::OrderModel(QObject *parent)
    :
    QAbstractTableModel(parent)
{
}

const QMap<int, QString> OrderModel::kHeaderLabels {
    { OrderRoles::StrategyNameRole, "Strategy Name" },
    { OrderRoles::OrderIdRole,      "Order ID" },
    { OrderRoles::BuySellRole,      "Side" },
    { OrderRoles::PriceRole,        "Price" },
    { OrderRoles::VolumeRole,       "Volume (Filled/Active)" }
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
    return COLUMN_COUNT;
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

    // DisplayRole for tableView:
    if (role == Qt::DisplayRole) {
        auto keys = kHeaderLabels.keys();
        if (index.column() >= 0 && index.column() < keys.size()) {
            role = keys[index.column()];
        } else {
            return QVariant();
        }
    }

    switch (role) {
        case OrderRoles::StrategyNameRole:
            return m_nameResolver(order.unique_strategy_id);
        case OrderRoles::OrderIdRole:
            return QString::number(order.unique_order_id).rightJustified(3, '0');
        case OrderRoles::BuySellRole:
            return order.side == OrderData::Side::Buy ? "Buy" : "Sell";
        case OrderRoles::PriceRole:
            return QString::number(order.price, 'f', 2) + "$";
        case OrderRoles::VolumeRole:
            return QString("%1/%2        \%%3")
                .arg(QString::number(order.filled_volume, 'f', 0),
                     QString::number(order.active_volume, 'f', 0),
                     QString::number((order.filled_volume/order.active_volume)*100, 'f', 2));
        case OrderRoles::RawDataRole:
            return QVariant::fromValue(order);
        default:
            return QVariant();
    }

    return QVariant();
}

QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    // The order of the keys specifies the order of the columns.
    // The value of the keys is independent of the number of columns.
    auto keys = kHeaderLabels.keys();
    if (section >= 0 && section < keys.size())
        return kHeaderLabels[keys[section]];

    return QVariant();
}

void OrderModel::setStrategyNameResolver(StrategyNameResolver resolver)
{
    m_nameResolver = resolver;
}

void OrderModel::addOrder(const OrderData &order)
{
    int newRow = m_orders.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
    m_orders.append(order);
    endInsertRows();
}


void OrderModel::clearOrders()
{
    if (m_orders.isEmpty()) return;
    beginResetModel();
    m_orders.clear();
    endResetModel();
}
