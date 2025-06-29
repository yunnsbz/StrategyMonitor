#ifndef STRATEGYITEMDELEGATE_H
#define STRATEGYITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QPainter>

class StrategyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit StrategyDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // Satır yüksekliğini ayarla:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // STRATEGYITEMDELEGATE_H
