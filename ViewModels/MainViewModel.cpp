#include "MainViewModel.h"
#include "OrderData.h"


#include <QDebug>

MainViewModel::MainViewModel()
    :
    DataGenerator(new MockDataGenerator())
{

    connect(DataGenerator, &MockDataGenerator::orderUpdateGenerated, this, &MainViewModel::onOrderDataReceived);
}

void MainViewModel::onOrderDataReceived(const OrderData &order)
{

}
