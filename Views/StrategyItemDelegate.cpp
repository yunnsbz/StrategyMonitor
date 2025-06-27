#include "StrategyItemDelegate.h"
#include "strategy_model_roles.h"

#include <QApplication>
#include <QPainterPath>

StrategyDelegate::StrategyDelegate(QObject *parent)
    :
    QStyledItemDelegate(parent)
{}

QSize StrategyDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const {
    return QSize(280, 70);
}

void StrategyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    // Veriler
    QString strategyId = index.data(StrategyRoles::IdRole).toString();
    QString name = index.data(StrategyRoles::NameRole).toString();
    QString type = index.data(StrategyRoles::TypeRole).toString();
    QString state = index.data(StrategyRoles::StateRole).toString();

    bool isSelected = option.state & QStyle::State_Selected;
    bool isMouseOver = option.state & QStyle::State_MouseOver;

    painter->save();
    QRect rect = option.rect;

    int topSpace = 5;
    int leftSpace = 10;
    int rightSpace = 10;

    // arkaplanı çizdirme
    QPainterPath backgroundPath;
    backgroundPath.addRoundedRect(rect.adjusted(5, 5, -5, -5), 5, 5);

    // Arka plan
    QColor backgroundColor(0x1E1E1E);
    if (isSelected){
        if(isMouseOver){
            backgroundColor.setRgb(0x3B4C66);
        }
        else backgroundColor.setRgb(0x303F55);
    }
    else if(isMouseOver){
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
    QRect leftIconRect(rect.left() + 5 + leftSpace, rect.top() + 15 + topSpace, 30, 30);

    // Seçime göre ikon:
    if (isSelected){
        QIcon icon(":/icons/Views/check_box.svg");
        icon.paint(painter, leftIconRect, Qt::AlignCenter);
    }
    else{
        QIcon icon(":/icons/Views/check_box_blank.svg");
        icon.paint(painter, leftIconRect, Qt::AlignCenter);
    }

    // Metinler
    QFont boldFont = option.font;
    boldFont.setBold(true);
    boldFont.setCapitalization(QFont::Capitalize);
    boldFont.setPixelSize(20);

    painter->setFont(boldFont);
    QRect nameRect = QRect(leftIconRect.right() + 10, rect.top() + 5 + topSpace, 110, 30);
    painter->drawText(nameRect, name);

    QFont smallFont = option.font;
    smallFont.setPointSize(7);
    painter->setFont(smallFont);

    QRect idRect = QRect(leftIconRect.right() + 10, rect.top() + 35 + topSpace, 40, 15);
    painter->drawText(idRect, "id: " + strategyId);

    QRect typeRect = QRect(idRect.right() + 10, rect.top() + 35 + topSpace, 80, 15);
    painter->drawText(typeRect, type);

    painter->setFont(option.font);

    // sağ state ikonu
    QRect rightIconRect(rect.right() - 35 - rightSpace, rect.top() + 15 + topSpace, 30, 30);

    if(state == "Running"){
        QIcon icon(":/icons/Views/square_running.svg");
        icon.paint(painter, rightIconRect, Qt::AlignCenter);
    }
    else{
        QIcon icon(":/icons/Views/square_paused.svg");
        icon.paint(painter, rightIconRect, Qt::AlignCenter);
    }

    QRect stateRect = QRect(rightIconRect.left() - 45, rect.top() + 20 + topSpace, 45, 20);
    painter->drawText(stateRect, state);

    painter->restore();
}
