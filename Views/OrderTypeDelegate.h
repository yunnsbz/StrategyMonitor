#ifndef ORDERTYPEDELEGATE_H
#define ORDERTYPEDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QPainter>

class OrderTypeDelegate : public QStyledItemDelegate {
public:
    OrderTypeDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // ORDERTYPEDELEGATE_H
