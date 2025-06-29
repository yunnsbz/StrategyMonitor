#ifndef STRATEGYFILTERPROXYMODEL_H
#define STRATEGYFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class StrategyData;

class StrategyFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit StrategyFilterProxyModel(QObject *parent = nullptr);
    /**
     * used to show only one state type from strategies.
     * there are two states: "Running" and "Paused".
     */
    void setSelectedState(QString state);
    void clearStrategyFilter();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QSet<int> m_selectedStrategyIds;
    bool m_strategyFilterActive = false;

    QString m_selectedState = "Running";
};

#endif // STRATEGYFILTERPROXYMODEL_H
