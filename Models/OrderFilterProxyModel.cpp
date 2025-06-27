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

bool OrderFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        // Kolon numarasına göre yalnızca sayısal sıralama gereken sütunları kontrol eder
        if (left.column() == 3) { // price sütunu
            bool ok1, ok2;
            double l = leftData.toString().removeLast().toDouble(&ok1);
            double r = rightData.toString().removeLast().toDouble(&ok2);

            if (ok1 && ok2)
                return l < r;
            else qDebug() <<"double değil";
        }
        else if(left.column() == 4) { // volume sütunu
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

        // Diğer sütunlar için varsayılan sıralama
        return QSortFilterProxyModel::lessThan(left, right);
    }

bool OrderFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // Filtre aktif değilse veya seçili ID yoksa tüm satırları kabul et
    if (!m_filterActive || m_selectedStrategyIds.isEmpty()) {
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

    // filtreleme başarılı
    OrderData order = dataVariant.value<OrderData>();
    return m_selectedStrategyIds.contains(order.unique_strategy_id);
}
