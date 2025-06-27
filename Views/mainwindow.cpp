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
    ui->splitter->widget(0)->setMinimumWidth(300);

    // liste item Delegate:
    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->StrategiesListView->setItemDelegate(delegate);

    ui->StrategiesListView->setModel(MainVM->strategiesModel());

    ui->OrdersTableView->setModel(MainVM->ordersModel());

    // liste itemine tıklama:
    //connect(ui->StrategiesListView, &QListView::clicked, this, &MainWindow::OnListItemClicked);
    connect(ui->StrategiesListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::OnMultipleListItemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnListItemClicked(const QModelIndex& index)
{
    MainVM->SetStrategySelected(index.data(Qt::UserRole+1).toInt());
}

void MainWindow::OnMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList deselectedIndexes = deselected.indexes();
    for(auto index : deselectedIndexes){
        MainVM->SetStrategySelected(index.data(Qt::UserRole+1).toInt());
    }
    QModelIndexList selectedIndexes = selected.indexes();
    for(auto index : selectedIndexes){
        MainVM->SetStrategySelected(index.data(Qt::UserRole+1).toInt());
    }
}
