#include "StrategyItemDelegate.h"
#include <QApplication>

StrategyDelegate::StrategyDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QSize StrategyDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const {
    return QSize(200, 50);
}

void StrategyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    QRect rect = option.rect;

    // sol seçim ikonu:
    QRect leftIconRect(rect.left() + 5, rect.top() + 10, 30, 30);

    // Seçim:
    if (option.state & QStyle::State_Selected){
        //painter->fillRect(option.rect, option.palette.highlight());

        // Sol ikon:
        QIcon icon(":/icons/Views/check_box.svg");
        icon.paint(painter, leftIconRect, Qt::AlignCenter);
    }
    else{
        //painter->fillRect(option.rect, option.palette.base());

        // Sol ikon:
        QIcon icon(":/icons/Views/check_box_blank.svg");
        icon.paint(painter, leftIconRect, Qt::AlignCenter);
    }

    // Verileri al (veriler model'den gelir)
    QString name = index.data(Qt::UserRole + 1).toString();
    QString state = index.data(Qt::UserRole + 2).toString();
    int strategyId = index.data(Qt::UserRole + 0).toInt(); // ID, tıklamada lazım



    // Metinler (iki satır)
    QFont boldFont = option.font;
    boldFont.setBold(true);
    painter->setFont(boldFont);
    QRect nameRect = QRect(leftIconRect.right() + 10, rect.top() + 5, rect.width() - 100, 20);
    painter->drawText(nameRect, name);

    painter->setFont(option.font);
    QRect stateRect = QRect(leftIconRect.right() + 10, rect.top() + 25, rect.width() - 100, 20);
    painter->drawText(stateRect, state);


    painter->restore();
}
