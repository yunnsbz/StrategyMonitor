#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainViewModel.h"
#include "StrategyItemDelegate.h"
#include "OrderTypeDelegate.h"
#include "filterdialog.h"

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    MainVM(new MainViewModel()),
    priceDialog(new FilterDialog(this)),
    volumeDialog(new FilterDialog(this))
{
    ui->setupUi(this);

    ui->splitter->setSizes({400,600});
    ui->splitter->widget(0)->setMinimumWidth(320);

    // liste item Delegate:
    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->StrategiesListView->setItemDelegate(delegate);
    ui->StrategiesListView->setModel(MainVM->strategiesModel());

    ui->OrdersTableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->OrdersTableView->setModel(MainVM->ordersModel());

    OrderTypeDelegate *orderTypeDelegate = new OrderTypeDelegate(this);
    ui->OrdersTableView->setItemDelegateForColumn(SIDE_COLUMN_INDEX, orderTypeDelegate);

    // liste itemine tıklama:
    connect(ui->StrategiesListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::OnMultipleListItemClicked);

    connect(ui->OrdersTableView->horizontalHeader(), &QHeaderView::customContextMenuRequested,
            this, [this](const QPoint& pos) {
        int column = ui->OrdersTableView->horizontalHeader()->logicalIndexAt(pos);
        if (column == PRICE_COLUMN_INDEX) {
            onPriceFilterRequested();
        }
        else if(column == VOLUME_COLUMN_INDEX){
            onVolumeFilterRequested();
        }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList deselectedIndexes = deselected.indexes();
    for(auto &index : deselectedIndexes){
        MainVM->SetStrategySelected(index.data(Qt::UserRole+1).toInt());
    }
    QModelIndexList selectedIndexes = selected.indexes();
    for(auto &index : selectedIndexes){
        MainVM->SetStrategySelected(index.data(Qt::UserRole+1).toInt());
    }

    onSelectedStrategiesChanged();
}

void MainWindow::onPriceFilterRequested()
{
    auto priceRange = MainVM->ordersPriceRange();

    if(priceRange.second <= 0) return;

    priceDialog->setRange(priceRange.first, priceRange.second);

    priceDialog->setInfoText("Set Price Range Between Min and Max values:");

    if (priceDialog->exec() == QDialog::Accepted) {
        if (priceDialog->wasClearFilterPressed()) {
            MainVM->clearPriceFilter();
        } else {
            double min = priceDialog->minValue();
            double max = priceDialog->maxValue();
            MainVM->setPriceFilter(min, max);
        }
    }
}

void MainWindow::onVolumeFilterRequested()
{
    volumeDialog->setRange(0, 100, true);

    volumeDialog->setInfoText("Set Volume persentage:");

    if (volumeDialog->exec() == QDialog::Accepted) {
        if (volumeDialog->wasClearFilterPressed()) {
            MainVM->clearVolumeFilter();
        } else {
            double min = volumeDialog->minValue();
            double max = volumeDialog->maxValue();
            MainVM->setVolumeFilter(min, max);
        }
    }
}

void MainWindow::onSelectedStrategiesChanged()
{
    auto names = MainVM->getStrategiesSelected();

    if(names.isEmpty()){
        ui->label_selected_strategies->setText("(Showing All Orders)");
    }
    else{
        QString output = "(";
        for(auto name : names)
        {
            output += name + ", ";
        }
        // sonda virgül varsa kaldır
        if(output.endsWith(", ")){ output.removeLast(); output.removeLast(); }
        output += ")";
        ui->label_selected_strategies->setText(output);
    }
}
