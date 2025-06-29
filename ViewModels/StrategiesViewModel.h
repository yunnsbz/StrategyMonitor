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

    // eğer strateji seçili değilse ekler seçili ise çıkartır.
    void setStrategySelected(QVariant data);
    QSet<int> getSelectedStrategyIds();
    QSet<QString> getSelectedStrategyNames();

    void setStrategyStateFilter(QString state);
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
