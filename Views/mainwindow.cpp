#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainViewModel.h"
#include "StrategiesViewModel.h"
#include "StrategyItemDelegate.h"

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    MainVM(new MainViewModel()),
    StrategiesVM(new StrategiesViewModel())
{
    ui->setupUi(this);

    ui->splitter->setSizes({400,600});

    // Delegate: özel görünüm
    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->StrategiesListView->setItemDelegate(delegate);

    // ViewModel'deki modeli View'e bağla
    ui->StrategiesListView->setModel(StrategiesVM->model());
}

MainWindow::~MainWindow()
{
    delete ui;
}
