#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "OrderData.h"

using StrategyNameResolver = std::function<QString(int strategyId)>;

class OrderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OrderModel(QObject *parent = nullptr);

    /**
     * header data.
     * you can change the column order with OrderRoles enum.
     */
    static const QMap<int, QString> kHeaderLabels;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * used for data function to fetch strategy name from StrategyModel.
     */
    void setStrategyNameResolver(StrategyNameResolver resolver);

    void addOrder(const OrderData &order);
    void clearOrders();

    /*
     * returns -1 if the role does not exits
     */
    int getColumnIndex(int role);

private:
    QList<OrderData> m_orders;

    static constexpr int COLUMN_COUNT = 5;

    QMap<int,int> roleToColumnMap;
    QMap<int,int> columnToRoleMap;
    StrategyNameResolver m_nameResolver;
};

#endif // ORDERMODEL_H
