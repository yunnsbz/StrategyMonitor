#include "StrategyItemDelegate.h"
#include "strategy_model_roles.h"

#include <QApplication>
#include <QPainterPath>

StrategyDelegate::StrategyDelegate(QObject *parent)
    :
    QStyledItemDelegate(parent)
{

}

QSize StrategyDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return {280, 70};
}

void StrategyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // values
    const QString strategyId = index.data(StrategyRoles::IdRole).toString();
    const QString name = index.data(StrategyRoles::NameRole).toString();
    const QString type = index.data(StrategyRoles::TypeRole).toString();
    const QString state = index.data(StrategyRoles::StateRole).toString();

    // item states
    const bool isSelected = option.state & QStyle::State_Selected;
    const bool isMouseOver = option.state & QStyle::State_MouseOver;

    painter->save();
    const QRect rect = option.rect;

    const int topSpace = 5;
    const int leftSpace = 10;
    const int rightSpace = 10;

    // background
    QPainterPath backgroundPath;
    backgroundPath.addRoundedRect(rect.adjusted(5, 5, -5, -5), 5, 5);

    QColor backgroundColor(0x1E1E1E);
    if (isSelected) {
        if(isMouseOver)
            backgroundColor.setRgb(0x3B4C66);
        else
            backgroundColor.setRgb(0x303F55);
    } else if(isMouseOver) {
        backgroundColor.setRgb(0x2A2A2A);
    }
    painter->fillPath(backgroundPath, backgroundColor);

    // çerçeve
    QPen borderPen(QColor(0x444444));
    borderPen.setWidth(3);
    painter->setPen(borderPen);
    painter->drawPath(backgroundPath);

    painter->setPen(QColor(0xffffff));

    // sol seçim ikonu:
    const QRect leftIconRect(rect.left() + 5 + leftSpace, rect.top() + 15 + topSpace, 30, 30);

    // Seçime göre ikon:
    if (isSelected){
        const QIcon icon(":/icons/Views/check_box.svg");
        icon.paint(painter, leftIconRect, Qt::AlignCenter);
    } else {
        const QIcon icon(":/icons/Views/check_box_blank.svg");
        icon.paint(painter, leftIconRect, Qt::AlignCenter);
    }

    // Metinler
    QFont boldFont = option.font;
    boldFont.setBold(true);
    boldFont.setCapitalization(QFont::Capitalize);
    boldFont.setPixelSize(20);

    painter->setFont(boldFont);
    const QRect nameRect = QRect(leftIconRect.right() + 10, rect.top() + 5 + topSpace, 110, 30);
    painter->drawText(nameRect, name);

    QFont smallFont = option.font;
    smallFont.setPointSize(7);
    painter->setFont(smallFont);

    const QRect idRect = QRect(leftIconRect.right() + 10, rect.top() + 35 + topSpace, 40, 15);
    painter->drawText(idRect, "id: " + strategyId);

    const QRect typeRect = QRect(idRect.right() + 10, rect.top() + 35 + topSpace, 80, 15);
    painter->drawText(typeRect, type);

    painter->setFont(option.font);

    // sağ state ikonu
    const QRect rightIconRect(rect.right() - 35 - rightSpace, rect.top() + 15 + topSpace, 30, 30);

    if(state == "Running") {
        const QIcon icon(":/icons/Views/square_running.svg");
        icon.paint(painter, rightIconRect, Qt::AlignCenter);
    } else {
        const QIcon icon(":/icons/Views/square_paused.svg");
        icon.paint(painter, rightIconRect, Qt::AlignCenter);
    }

    const QRect stateRect = QRect(rightIconRect.left() - 45, rect.top() + 20 + topSpace, 45, 20);
    painter->drawText(stateRect, state);

    painter->restore();
}
