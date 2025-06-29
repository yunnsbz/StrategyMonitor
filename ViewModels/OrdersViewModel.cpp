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

void OrdersViewModel::applyStrategyFilter(const QSet<int> &ids)
{
    filter()->setSelectedStrategyIds(ids);
}

void OrdersViewModel::setPriceFilter(double min, double max)
{
    filter()->setPriceFilter(min, max);
}

auto OrdersViewModel::getOrdersPriceRange() -> QPair<double, double>
{
    return filter()->getOrdersPriceRange();
}

auto OrdersViewModel::getFilledVolRange() -> QPair<int, int>
{
    return filter()->getFilledVolRange();
}

auto OrdersViewModel::getActiveVolRange() -> QPair<int, int>
{
    return filter()->getOrdersPriceRange();
}

void OrdersViewModel::clearPriceFilter()
{
    filter()->clearPriceFilter();
}

void OrdersViewModel::setFilledVolFilter(double min, double max)
{
    filter()->setFilledVolFilter(min, max);
}

void OrdersViewModel::setActiveVolFilter(double min, double max)
{
    filter()->setActiveVolFilter(min, max);
}

void OrdersViewModel::clearActiveVolFilter()
{
    filter()->clearActiveVolFilter();
}

void OrdersViewModel::clearFilledVolFilter()
{
    filter()->clearFilledVolFilter();
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
