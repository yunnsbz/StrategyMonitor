#include "OrdersViewModel.h"
#include "OrderModel.h"
#include "OrderFilterProxyModel.h"
#include "OrderData.h"

OrdersViewModel::OrdersViewModel(QObject *parent)
    :
    QObject(parent),
    m_model(new OrderModel()),
    m_filteredOrderModel(new OrderFilterProxyModel(this))
{
    m_filteredOrderModel->setSourceModel(m_model);
}

QAbstractItemModel* OrdersViewModel::model() {
    return m_filteredOrderModel;
}

OrderFilterProxyModel *OrdersViewModel::filter()
{
    return m_filteredOrderModel;
}

void OrdersViewModel::addOrder(const OrderData& data, QString StrategyName) {
    m_model->addOrder(data, StrategyName);
}
