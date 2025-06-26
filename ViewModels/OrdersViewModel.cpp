#include "OrdersViewModel.h"
#include "OrderModel.h"
#include "OrderData.h"

OrdersViewModel::OrdersViewModel(QObject *parent)
    :
    QObject(parent),
    m_model(new OrderModel()),
{
}

QAbstractItemModel* OrdersViewModel::model() {
    return m_model;
}

void OrdersViewModel::addOrder(const OrderData& data) {
    m_model->addOrder(data);
}
