#ifndef STRATEGYFILTERPROXYMODEL_H
#define STRATEGYFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class StrategyData;

class StrategyFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit StrategyFilterProxyModel(QObject *parent = nullptr);

    void SetSelectedState(QString state);
    void clearStrategyFilter();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QSet<int> m_selectedStrategyIds;
    bool m_strategyFilterActive = false;

    QString SelectedState = "Running";
};

#endif // STRATEGYFILTERPROXYMODEL_H
