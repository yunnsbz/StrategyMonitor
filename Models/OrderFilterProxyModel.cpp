#include "OrderFilterProxyModel.h"
#include "OrderData.h"

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
    m_filterActive = true;
    invalidateFilter();
}

void OrderFilterProxyModel::clearStrategyFilter()
{
    m_selectedStrategyIds.clear();
    m_filterActive = false;
    invalidateFilter();
}

bool OrderFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // Filtre aktif değilse veya seçili ID yoksa tüm satırları kabul et
    if (!m_filterActive || m_selectedStrategyIds.isEmpty()) {
        qDebug() << "Filtre aktif değil veya seçili ID yok. tüm satırları kabul et";
        return true;
    }

    QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    if (!sourceIndex.isValid()) {
        qDebug() << "source valid değil";
        return false;
    }

    QVariant dataVariant = sourceModel()->data(sourceIndex, Qt::UserRole);
    if (!dataVariant.canConvert<OrderData>()) {
        qDebug() << "filtreleme başarısız";
        return false;
    }

    OrderData order = dataVariant.value<OrderData>();
    qDebug() << "filtreleme başarılı";
    return m_selectedStrategyIds.contains(order.unique_strategy_id);
}
