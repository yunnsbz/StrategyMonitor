#ifndef STRATEGIESVIEWMODEL_H
#define STRATEGIESVIEWMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class StrategyModel;

class StrategiesViewModel : public QObject {
    Q_OBJECT
public:
    explicit StrategiesViewModel(QObject *parent = nullptr);

    QAbstractItemModel* model() const;

    void addStrategy(const class StrategyData& data);

public slots:


private:
    StrategyModel* m_model;
};

#endif // STRATEGIESVIEWMODEL_H
