#ifndef STRATEGYMODEL_H
#define STRATEGYMODEL_H

#include <QAbstractListModel>

#include "StrategyData.h"

class StrategyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    StrategyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addStrategy(const StrategyData &strategy);
    StrategyData getStrategy(int targetId) const;

private:
    QVector<StrategyData> m_strategies;
};

#endif // STRATEGYMODEL_H
