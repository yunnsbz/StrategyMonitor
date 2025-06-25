#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include "MockDataGenerator.h"


class MainViewModel : public QObject{

    Q_OBJECT

public:
    MainViewModel();

public slots:
    void onOrderDataReceived(const class OrderData& order);

private:
    MockDataGenerator* DataGenerator;

};

#endif // MAINVIEWMODEL_H
