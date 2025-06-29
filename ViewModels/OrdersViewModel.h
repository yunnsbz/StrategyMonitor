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

    void setPriceFilter(double min, double max);
    QPair<double,double> getOrdersPriceRange();
    void clearPriceFilter();

    void setVolumeFilter(double min, double max);
    void clearVolumeFilter();

    QAbstractItemModel* model();
    OrderModel* orderModel();
    OrderFilterProxyModel* filter();

    void addOrder(const class OrderData& data);

private:
    OrderModel* m_model;
    OrderFilterProxyModel* m_filteredOrderModel;


};

#endif // ORDERSVIEWMODEL_H
