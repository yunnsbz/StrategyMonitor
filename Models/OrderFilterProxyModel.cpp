#include "OrderFilterProxyModel.h"
#include "OrderData.h"
#include "order_model_roles.h"

OrderFilterProxyModel::OrderFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void OrderFilterProxyModel::setSelectedStrategyIds(const QSet<int> &ids)
{
    if (ids.isEmpty()) {
        clearStrategyFilter();
        return;
    }
    m_selectedStrategyIds = ids;
    m_strategyFilterActive = true;
    invalidateFilter();
}

void OrderFilterProxyModel::clearStrategyFilter()
{
    m_selectedStrategyIds.clear();
    m_strategyFilterActive = false;
    invalidateFilter();
}

void OrderFilterProxyModel::setPriceFilter(double min, double max)
{
    m_priceFilter.min = min;
    m_priceFilter.max = max;
    m_priceFilter.isActive = true;
    emit filterChanged(OrderRoles::PriceRole, true);
    invalidateFilter();
}

QPair<double, double> OrderFilterProxyModel::getOrdersPriceRange() const
{
    double minPrice = std::numeric_limits<double>::max();
    double maxPrice = std::numeric_limits<double>::lowest();

    const QAbstractItemModel* model = sourceModel();
    const int rowCount = model->rowCount();

    for (int row = 0; row < rowCount; ++row) {
        QModelIndex sourceIndex = model->index(row, 0); // herhangi bir sütun olur
        QVariant rawVariant = model->data(sourceIndex, OrderRoles::RawDataRole);

        if (!rawVariant.canConvert<OrderData>())
            continue;

        OrderData order = rawVariant.value<OrderData>();

        // check only for unfiltered strategies
        if (!m_selectedStrategyIds.isEmpty() && !m_selectedStrategyIds.contains(order.unique_strategy_id))
            continue;

        double price = order.price;
        minPrice = std::min(minPrice, price);
        maxPrice = std::max(maxPrice, price);
    }

    if (minPrice == std::numeric_limits<double>::max())
        return {0.0, 0.0};

    return {minPrice, maxPrice};
}

QPair<int, int> OrderFilterProxyModel::getFilledVolRange() const
{
    double minVol = std::numeric_limits<double>::max();
    double maxVol = std::numeric_limits<double>::lowest();

    const QAbstractItemModel* model = sourceModel();
    const int rowCount = model->rowCount();

    for (int row = 0; row < rowCount; ++row) {
        QModelIndex sourceIndex = model->index(row, 0); // herhangi bir sütun olur
        QVariant rawVariant = model->data(sourceIndex, OrderRoles::RawDataRole);

        if (!rawVariant.canConvert<OrderData>())
            continue;

        OrderData order = rawVariant.value<OrderData>();

        // check only for unfiltered strategies
        if (!m_selectedStrategyIds.isEmpty() && !m_selectedStrategyIds.contains(order.unique_strategy_id))
            continue;

        double volume = order.filled_volume;
        minVol = std::min(minVol, volume);
        maxVol = std::max(maxVol, volume);
    }

    if (minVol == std::numeric_limits<double>::max())
        return {0.0, 0.0};

    return {minVol, maxVol};
}

QPair<int, int> OrderFilterProxyModel::getActiveVolRange() const
{
    double minVol = std::numeric_limits<double>::max();
    double maxVol = std::numeric_limits<double>::lowest();

    const QAbstractItemModel* model = sourceModel();
    const int rowCount = model->rowCount();

    for (int row = 0; row < rowCount; ++row) {
        QModelIndex sourceIndex = model->index(row, 0); // herhangi bir sütun olur
        QVariant rawVariant = model->data(sourceIndex, OrderRoles::RawDataRole);

        if (!rawVariant.canConvert<OrderData>())
            continue;

        OrderData order = rawVariant.value<OrderData>();

        // check only for unfiltered strategies
        if (!m_selectedStrategyIds.isEmpty() && !m_selectedStrategyIds.contains(order.unique_strategy_id))
            continue;

        double volume = order.active_volume;
        minVol = std::min(minVol, volume);
        maxVol = std::max(maxVol, volume);
    }

    if (minVol == std::numeric_limits<double>::max())
        return {0.0, 0.0};

    return {minVol, maxVol};
}

void OrderFilterProxyModel::setFilledVolFilter(double min, double max)
{
    m_filledVolFilter.min = min;
    m_filledVolFilter.max = max;
    m_filledVolFilter.isActive = true;
    emit filterChanged(OrderRoles::FilledVolumeRole, true);
    invalidateFilter();
}

void OrderFilterProxyModel::clearFilledVolFilter()
{
    m_filledVolFilter.isActive = false;
    emit filterChanged(OrderRoles::FilledVolumeRole, false);
    invalidateFilter();
}

void OrderFilterProxyModel::setActiveVolFilter(double min, double max)
{
    m_activeVolFilter.min = min;
    m_activeVolFilter.max = max;
    m_activeVolFilter.isActive = true;
    emit filterChanged(OrderRoles::ActiveVolumeRole, true);
    invalidateFilter();
}

void OrderFilterProxyModel::clearActiveVolFilter()
{
    m_activeVolFilter.isActive = false;
    emit filterChanged(OrderRoles::ActiveVolumeRole, false);
    invalidateFilter();
}

void OrderFilterProxyModel::clearPriceFilter()
{
    m_priceFilter.isActive = false;
    emit filterChanged(OrderRoles::PriceRole, false);
    invalidateFilter();
}

bool OrderFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        if (leftData.toString().endsWith("$")) { // price column
            bool ok1, ok2;
            double l = leftData.toString().removeLast().toDouble(&ok1);
            double r = rightData.toString().removeLast().toDouble(&ok2);

            if (ok1 && ok2)
                return l < r;
            else qDebug() <<"double değil";
        }
        else if(leftData.canConvert<double>()){
            bool ok1, ok2;
            double l = leftData.toDouble(&ok1);
            double r = rightData.toDouble(&ok2);

            if (ok1 && ok2)
                return l < r;
        }

        // use default order for other columns
        return QSortFilterProxyModel::lessThan(left, right);
    }

bool OrderFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    if (!sourceIndex.isValid()) {
        qDebug() << "source valid değil";
        return false;
    }

    QVariant dataVariant = sourceModel()->data(sourceIndex, OrderRoles::RawDataRole);
    if (!dataVariant.canConvert<OrderData>()) {
        qDebug() << "filtreleme başarısız";
        return false;
    }

    OrderData order = dataVariant.value<OrderData>();

    return
        strategyFilter(order) &&
        priceFilter(order) &&
        filledVolumeFilter(order) &&
        activeVolumeFilter(order);

}

bool OrderFilterProxyModel::strategyFilter(OrderData order) const
{
    // if filter is inactive or no strategies selected // if filter is inactive
    if (!m_strategyFilterActive || m_selectedStrategyIds.isEmpty()) {
        return true;
    }

    // show only selected strategy orders
    return m_selectedStrategyIds.contains(order.unique_strategy_id);
}

bool OrderFilterProxyModel::priceFilter(OrderData order) const
{
    if (!m_priceFilter.isActive) {
        return true;
    }

    // show if order is in the range
    return order.price <= m_priceFilter.max && order.price >= m_priceFilter.min;
}

bool OrderFilterProxyModel::filledVolumeFilter(OrderData order) const
{
    if (!m_filledVolFilter.isActive) {
        return true;
    }
    return order.filled_volume >= m_filledVolFilter.min && order.filled_volume <= m_filledVolFilter.max;
}

bool OrderFilterProxyModel::activeVolumeFilter(OrderData order) const
{
    if (!m_activeVolFilter.isActive) {
        return true;
    }
    return order.active_volume >= m_activeVolFilter.min && order.active_volume <= m_activeVolFilter.max;
}
