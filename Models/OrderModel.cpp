#include "OrderModel.h"
#include "order_model_roles.h"



OrderModel::OrderModel(QObject *parent)
    :
    QAbstractTableModel(parent)
{
    int column = 0;
    for (auto it = OrderModel::kHeaderLabels.begin(); it != OrderModel::kHeaderLabels.end(); ++it, ++column) {
        roleToColumnMap[it.key()] = column;
        columnToRoleMap[column] = it.key();
    }
}

const QMap<int, QString> OrderModel::kHeaderLabels {
    { OrderRoles::StrategyNameRole, "Strategy Name" },
    { OrderRoles::OrderIdRole,      "Order ID" },
    { OrderRoles::BuySellRole,      "Side" },
    { OrderRoles::PriceRole,        "Price" },
    { OrderRoles::FilledVolumeRole,       "Filled Volume" },
    { OrderRoles::ActiveVolumeRole,       "Active Volume" },
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
            return {};
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
        case OrderRoles::FilledVolumeRole:
            return QString("%1")
                .arg(QString::number(order.filled_volume, 'f', 0));
        case OrderRoles::ActiveVolumeRole:
            return QString("%1")
                .arg(QString::number(order.active_volume, 'f', 0));
        case OrderRoles::RawDataRole:
            return QVariant::fromValue(order);
        default:
            return {};
    }

    return {};
}

QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    // The order of the keys specifies the order of the columns.
    // The value of the keys is independent of the number of columns.
    auto keys = kHeaderLabels.keys();
    if (section >= 0 && section < keys.size())
        return kHeaderLabels[keys[section]];

    return {};
}

void OrderModel::setStrategyNameResolver(StrategyNameResolver resolver)
{
    m_nameResolver = std::move(resolver);
}

void OrderModel::addOrder(const OrderData &order)
{
    const int newRow = m_orders.count();
    beginInsertRows(QModelIndex(), newRow, newRow);
    m_orders.append(order);
    endInsertRows();
}


void OrderModel::clearOrders()
{
    if (m_orders.isEmpty())
        return;
    beginResetModel();
    m_orders.clear();
    endResetModel();
}

int OrderModel::getColumnIndex(int role)
{
    if(roleToColumnMap.contains(role))
        return roleToColumnMap[role];
    else
        return -1;
}
