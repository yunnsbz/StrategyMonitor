#ifndef ORDERFILTERPROXYMODEL_H
#define ORDERFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QSet> // Birden fazla strateji ID'si için

class OrderFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit OrderFilterProxyModel(QObject *parent = nullptr);

    void setSelectedStrategyIds(const QSet<int> &ids);
    void clearStrategyFilter();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QSet<int> m_selectedStrategyIds;
    bool m_filterActive = false;
};


#endif // ORDERFILTERPROXYMODEL_H
