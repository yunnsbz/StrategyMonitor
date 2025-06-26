#ifndef ORDERSVIEWMODEL_H
#define ORDERSVIEWMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class OrderModel;
class OrderFilterProxyModel;

class OrdersViewModel : public QObject {
    Q_OBJECT
public:
    explicit OrdersViewModel(QObject *parent = nullptr);

    QAbstractItemModel* model();

    void addOrder(const class OrderData& data);

private:
    OrderModel* m_model;
};

#endif // ORDERSVIEWMODEL_H
