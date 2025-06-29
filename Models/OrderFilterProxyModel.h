#ifndef ORDERFILTERPROXYMODEL_H
#define ORDERFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QSet> // Birden fazla strateji ID'si için

class OrderData;

class OrderFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit OrderFilterProxyModel(QObject *parent = nullptr);

    /**
     * use to show only selected list items from StrategyModel.
     */
    void setSelectedStrategyIds(const QSet<int> &ids);
    void clearStrategyFilter();

    /**
     * set price proxy filter between min and max price values.
     */
    void setPriceFilter(double min, double max);
    void clearPriceFilter();

    /**
     * checks unfiltred strategies and fetch min and max price values.
     * Returns: min, max price Range.
     */
    QPair<double,double> getOrdersPriceRange() const;

    /**
     * values should be between 0 and 100 (percentage)
     */
    void setVolumeFilter(double min, double max);
    void clearVolumeFilter();

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QSet<int> m_selectedStrategyIds;
    bool m_strategyFilterActive = false;

    struct PriceFilter{
        double min = 0;
        double max = 0;
        bool isActive = false;
    }
    m_priceFilter;

    struct VolumeFilter{
        double min = 0;
        double max = 0;
        bool isActive = false;
    }
    m_volumeFilter;


    bool strategyFilter(OrderData) const;
    bool priceFilter(OrderData) const;
    bool volumeFilter(OrderData) const;
};


#endif // ORDERFILTERPROXYMODEL_H
