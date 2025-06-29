#ifndef HEADERWITHICONS_H
#define HEADERWITHICONS_H

#include <QHeaderView>
#include <QMap>
#include <QIcon>

class HeaderWithIcons : public QHeaderView {
    Q_OBJECT

public:
    explicit HeaderWithIcons(Qt::Orientation orientation, QWidget *parent = nullptr);

    void setIconForSection(int logicalIndex, const QIcon &icon);
    void clearIconForSection(int logicalIndex);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

private:
    QMap<int, QIcon> m_sectionIcons;
};

#endif // HEADERWITHICONS_H
