#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include "MockDataGenerator.h"

#include <QObject>
#include <QAbstractItemModel>

class StrategiesViewModel;

class MainViewModel : public QObject{

    Q_OBJECT

public:
    MainViewModel();

    QAbstractItemModel* strategiesModel();
    // eğer strateji seçili değilse ekler seçili ise çıkartır.
    void SetStrategySelected(int strategy_id);

public slots:
    void onOrderDataReceived(const class OrderData& order);
    void onStrategyDataReceived(const class StrategyData& strategy);

private:
    MockDataGenerator* DataGenerator;

    StrategiesViewModel* StrategiesVM;
    QVector<int> SelectedStrategies;
};

#endif // MAINVIEWMODEL_H
