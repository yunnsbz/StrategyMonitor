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

    void setSelectedStrategyIds(const QSet<int> &ids);
    void clearStrategyFilter();

    void setPriceFilter(double min, double max);
    void clearPriceFilter();
    QPair<double,double> ordersPriceRange() const;

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


    bool strategyFilter(OrderData) const;
    bool priceFilter(OrderData) const;
};


#endif // ORDERFILTERPROXYMODEL_H
