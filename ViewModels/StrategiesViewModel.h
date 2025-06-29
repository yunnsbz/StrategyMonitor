#ifndef STRATEGIESVIEWMODEL_H
#define STRATEGIESVIEWMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include "StrategyData.h"

class StrategyModel;
class StrategyFilterProxyModel;

class StrategiesViewModel : public QObject
{
    Q_OBJECT
public:
    explicit StrategiesViewModel(QObject *parent = nullptr);

    /**
     * if strategy allready selected then removes it from the set.
     * if strategy is not in the set then inserts it.
     */
    void setStrategySelected(const QVariant &data);
    QSet<int> getSelectedStrategyIds();
    QSet<QString> getSelectedStrategyNames();

    /**
     * used to show only one state type from strategies.
     * there are two states: "Running" and "Paused".
     */
    void setStrategyStateFilter(QString state) const;
    void clearStrategyFilter();

    QAbstractItemModel* model() const;
    StrategyFilterProxyModel* filter() const;
    void addStrategy(const class StrategyData& data);
    StrategyData getStrategy(int targetId) const;

private:
    StrategyModel* m_model;
    StrategyFilterProxyModel* m_filteredStrategyModel;

    QSet<StrategyData> m_selectedStrategies;
};

#endif // STRATEGIESVIEWMODEL_H
