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

    void applyStrategyFilter(QSet<int> ids);

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
    QPair<double,double> getOrdersPriceRange();

    /**
     * values should be between 0 and 100 (percentage)
     */
    void setVolumeFilter(double min, double max);
    void clearVolumeFilter();

    QAbstractItemModel* model();
    OrderModel* orderModel();
    OrderFilterProxyModel* filter();

    /**
     * calls OrderModel
     */
    void addOrder(const class OrderData& data);

private slots:
    void onOrderFilterChanged(int role, bool state);

private:
    OrderModel* m_model;
    OrderFilterProxyModel* m_filteredOrderModel;


};

#endif // ORDERSVIEWMODEL_H
