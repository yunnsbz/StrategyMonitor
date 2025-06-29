#include "HeaderWithIcons.h"
#include <QPainter>
#include <QStyleOptionHeader>
#include <QStyle>

HeaderWithIcons::HeaderWithIcons(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
    setSectionsClickable(true);
    setHighlightSections(true);
    setSortIndicatorShown(true);
    setStretchLastSection(true);
    setCascadingSectionResizes(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDefaultSectionSize(120);
    setSectionResizeMode(QHeaderView::Stretch);
}

void HeaderWithIcons::setIconForSection(int logicalIndex, const QIcon &icon)
{
    m_sectionIcons[logicalIndex] = icon;
    updateSection(logicalIndex);
}

void HeaderWithIcons::clearIconForSection(int logicalIndex)
{
    m_sectionIcons.remove(logicalIndex);
    updateSection(logicalIndex);
}

void HeaderWithIcons::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    QStyleOptionHeader opt;
    initStyleOption(&opt);
    opt.rect = rect;
    opt.section = logicalIndex;
    opt.text = model()->headerData(logicalIndex, orientation(), Qt::DisplayRole).toString();

    if (m_sectionIcons.contains(logicalIndex)) {
        opt.icon = m_sectionIcons.value(logicalIndex);
        opt.iconAlignment = Qt::AlignLeading | Qt::AlignVCenter;
        opt.textAlignment = Qt::AlignLeading | Qt::AlignVCenter;
    }

    opt.textAlignment = Qt::AlignCenter;

    style()->drawControl(QStyle::CE_Header, &opt, painter, this);

    if (isSortIndicatorShown() && logicalIndex == sortIndicatorSection()) {
        QPolygon arrow;
        const QRect arrowRect = rect.adjusted(rect.width() - 14, 6, -4, -6); // sağ üst köşeye biraz içe

        if (sortIndicatorOrder() == Qt::AscendingOrder) {
            // ▲
            arrow << QPoint(arrowRect.left(), arrowRect.bottom())
                  << QPoint(arrowRect.center().x(), arrowRect.top())
                  << QPoint(arrowRect.right(), arrowRect.bottom());
        } else {
            // ▼
            arrow << QPoint(arrowRect.left(), arrowRect.top())
                  << QPoint(arrowRect.center().x(), arrowRect.bottom())
                  << QPoint(arrowRect.right(), arrowRect.top());
        }

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(Qt::white);   // veya tema rengine göre ayarla
        painter->setPen(Qt::NoPen);
        painter->drawPolygon(arrow);
        painter->restore();
    }
}
