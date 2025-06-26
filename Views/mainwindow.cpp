#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainViewModel.h"
#include "StrategyItemDelegate.h"

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    MainVM(new MainViewModel())
{
    ui->setupUi(this);

    ui->splitter->setSizes({400,600});
    ui->splitter->widget(0)->setMinimumWidth(280);
    // Delegate: özel görünüm
    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->StrategiesListView->setItemDelegate(delegate);

    ui->StrategiesListView->setModel(MainVM->strategiesModel());

    connect(ui->StrategiesListView, &QListView::clicked, this, &MainWindow::OnListItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnListItemClicked(const QModelIndex& index)
{
    qDebug() << index.data(Qt::UserRole + 1);
}
