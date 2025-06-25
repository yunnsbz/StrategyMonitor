#ifndef STRATEGIESVIEWMODEL_H
#define STRATEGIESVIEWMODEL_H

#include "StrategyModel.h"
#include "MockDataGenerator.h"

#include <QObject>

class StrategiesViewModel : public QObject {
    Q_OBJECT
public:
    explicit StrategiesViewModel(QObject *parent = nullptr);

    StrategyModel* model() const;

    void addStrategy(const class StrategyData& data);

public slots:
    void onStrategyDataReceived(const class StrategyData& strategy);

private:
    MockDataGenerator* DataGenerator;
    StrategyModel* m_model;
};

#endif // STRATEGIESVIEWMODEL_H
