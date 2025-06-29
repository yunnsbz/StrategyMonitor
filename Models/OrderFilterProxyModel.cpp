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

void OrderFilterProxyModel::setVolumeFilter(double min, double max)
{
    m_volumeFilter.min = min;
    m_volumeFilter.max = max;
    m_volumeFilter.isActive = true;
    invalidateFilter();
}

void OrderFilterProxyModel::clearVolumeFilter()
{
    m_volumeFilter.isActive = false;
    invalidateFilter();
}

void OrderFilterProxyModel::clearPriceFilter()
{
    m_priceFilter.isActive = false;
    invalidateFilter();
}

bool OrderFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        if (left.column() == 3) { // price column
            bool ok1, ok2;
            double l = leftData.toString().removeLast().toDouble(&ok1);
            double r = rightData.toString().removeLast().toDouble(&ok2);

            if (ok1 && ok2)
                return l < r;
            else qDebug() <<"double değil";
        }
        else if(left.column() == 4) { // volume column
            QStringList leftParts = leftData.toString().split("/");
            QStringList rightParts = rightData.toString().split("/");
            try{
                double l = leftParts[0].toDouble() / leftParts[1].toDouble();
                double r = rightParts[0].toDouble() / rightParts[1].toDouble();

                return l < r;
            }
            catch(const std::exception& ex){
                qDebug() << "error while sorting volume";
            }
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
        volumeFilter(order);

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

bool OrderFilterProxyModel::volumeFilter(OrderData order) const
{
    if (!m_volumeFilter.isActive) {
        return true;
    }

    double persentage = (order.filled_volume / order.active_volume) * 100;

    return persentage <= m_volumeFilter.max && persentage >= m_volumeFilter.min;
}
