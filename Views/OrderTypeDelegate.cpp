#include "OrderTypeDelegate.h"
#include <qapplication.h>

OrderTypeDelegate::OrderTypeDelegate(QObject *parent)
    :
    QStyledItemDelegate(parent)
{

}

void OrderTypeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    // Sadece arka plan çizilsin
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, opt.widget);

    const QString value = index.data().toString().toLower(); // "buy" veya "sell"

    QIcon icon;
    if (value == "buy")
        icon = QIcon(":/icons/Views/buy-icon.png");
    else if (value == "sell")
        icon = QIcon(":/icons/Views/sell-icon.png");
    else
        qDebug() << "column error";

    // Simgeyi çiz
    const QRect iconRect = option.rect;
    const QSize iconSize = QSize(24, 24);
    icon.paint(painter, iconRect.left() + iconRect.width()/2 - iconSize.width()/2, iconRect.top() + iconRect.height()/2 - iconSize.height()/2, iconSize.width(), iconSize.height());

    painter->restore();
}
