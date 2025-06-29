#ifndef ORDERSVIEWMODEL_H
#define ORDERSVIEWMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QAbstractProxyModel>

class OrderModel;
class OrderFilterProxyModel;

class OrdersViewModel : public QObject
{
    Q_OBJECT
public:
    explicit OrdersViewModel(QObject *parent = nullptr);

    void applyStrategyFilter(const QSet<int> &ids);

    /**
     * set price proxy filter between min and max price values.
     * calls OrderFilterProxyModel
     */
    void setPriceFilter(double min, double max);
    void clearPriceFilter();
    /**
     * checks unfiltred strategies and fetch min and max price values.
     * Returns: min, max price Range.
     */
    auto getOrdersPriceRange() -> QPair<double,double>;
    auto getFilledVolRange() -> QPair<int, int>;
    auto getActiveVolRange() -> QPair<int, int>;

    /**
     * values should be between 0 and 100 (percentage)
     */
    void setFilledVolFilter(double min, double max);
    void clearFilledVolFilter();

    void setActiveVolFilter(double min, double max);
    void clearActiveVolFilter();

    QAbstractItemModel* model();
    OrderModel* orderModel();
    OrderFilterProxyModel* filter();

    /**
     * calls OrderModel
     */
    void addOrder(const class OrderData& data);

    int columnIndexForRole(int role);

signals:
    void orderFilterChanged(int column, bool state);

private slots:
    void onOrderFilterChanged(int role, bool state);

private:
    OrderModel* m_model;
    OrderFilterProxyModel* m_filteredOrderModel;


};

#endif // ORDERSVIEWMODEL_H
