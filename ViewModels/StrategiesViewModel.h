#ifndef STRATEGIESVIEWMODEL_H
#define STRATEGIESVIEWMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class StrategyModel;
class StrategyFilterProxyModel;

class StrategiesViewModel : public QObject
{
    Q_OBJECT
public:
    explicit StrategiesViewModel(QObject *parent = nullptr);

    QAbstractItemModel* model() const;
    StrategyFilterProxyModel* filter() const;
    void addStrategy(const class StrategyData& data);

    StrategyData getStrategy(int targetId) const;

private:
    StrategyModel* m_model;
    StrategyFilterProxyModel* m_filteredStrategyModel;
};

#endif // STRATEGIESVIEWMODEL_H
