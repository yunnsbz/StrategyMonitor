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

    connect(filter(),&OrderFilterProxyModel::filterChanged, this, &OrdersViewModel::onOrderFilterChanged);
}

void OrdersViewModel::applyStrategyFilter(QSet<int> ids)
{
    filter()->setSelectedStrategyIds(ids);
}

void OrdersViewModel::setPriceFilter(double min, double max)
{
    filter()->setPriceFilter(min, max);
}

QPair<double, double> OrdersViewModel::getOrdersPriceRange()
{
    return filter()->getOrdersPriceRange();
}

void OrdersViewModel::clearPriceFilter()
{
    filter()->clearPriceFilter();
}

void OrdersViewModel::setVolumeFilter(double min, double max)
{
    filter()->setVolumeFilter(min, max);
}

void OrdersViewModel::clearVolumeFilter()
{
    filter()->clearVolumeFilter();
}

QAbstractItemModel* OrdersViewModel::model() {
    return m_filteredOrderModel;
}

OrderModel *OrdersViewModel::orderModel()
{
    return m_model;
}

OrderFilterProxyModel *OrdersViewModel::filter()
{
    return m_filteredOrderModel;
}

void OrdersViewModel::addOrder(const OrderData& data) {
    m_model->addOrder(data);
}

int OrdersViewModel::columnIndexForRole(int role)
{
    return m_model->getColumnIndex(role);
}

void OrdersViewModel::onOrderFilterChanged(int role, bool state)
{
    emit orderFilterChanged(columnIndexForRole(role), state);
}
