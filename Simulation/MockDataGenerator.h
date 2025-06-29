#ifndef MOCKDATAGENERATOR_H
#define MOCKDATAGENERATOR_H

#include <QObject>
#include <QTimer>

struct OrderData;
struct StrategyData;

class MockDataGenerator : public QObject
{
    Q_OBJECT
public:
    MockDataGenerator();

public slots:
    void onStrategyTimerTimeout();
    void onOrderTimerTimeout();

signals:
    void strategyUpdateGenerated(const StrategyData& strategy);
    void orderUpdateGenerated(const OrderData& order);

private:

    StrategyData createStrategy();
    OrderData createOrder();

    QTimer* m_strategyTimer;
    QTimer* m_orderTimer;

    int m_strategyInterval = 800;
    int m_orderInterval = 1600;

    static int currentStrategytId;
    static int currentOrderId;

};

#endif // MOCKDATAGENERATOR_H
