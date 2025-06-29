#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "OrderModel.h"
#include "OrdersViewModel.h"
#include "StrategiesViewModel.h"
#include "StrategyData.h"
#include "StrategyItemDelegate.h"
#include "DataReceiver.h"
#include "OrderTypeDelegate.h"
#include "filterdialog.h"
#include "strategy_model_roles.h"

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ordersVM(new OrdersViewModel(this)),
    strategiesVM(new StrategiesViewModel(this)),
    dataReceiver(new DataReceiver(strategiesVM, ordersVM)),
    priceDialog(new FilterDialog(this)),
    volumeDialog(new FilterDialog(this))
{
    ui->setupUi(this);

    // splitter:
    ui->splitter->setSizes({400,600});
    ui->splitter->widget(0)->setMinimumWidth(320);

    // listView:
    ui->listViewStrategies->setModel(strategiesVM->model());

    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->listViewStrategies->setItemDelegate(delegate);

    // tableView
    ui->tableViewOrders->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableViewOrders->setModel(ordersVM->model());

    OrderTypeDelegate *orderTypeDelegate = new OrderTypeDelegate(this);
    ui->tableViewOrders->setItemDelegateForColumn(SIDE_COLUMN_INDEX, orderTypeDelegate);

    // strategies filter button toggles
    ui->pushButtonShowRunning->setCheckable(true);
    ui->pushButtonShowPaused->setCheckable(true);

    // list item onClick
    connect(ui->listViewStrategies->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onMultipleListItemClicked);

    // table header column onRightClick
    connect(ui->tableViewOrders->horizontalHeader(), &QHeaderView::customContextMenuRequested, this,
            [this](const QPoint& pos) {
        int column = ui->tableViewOrders->horizontalHeader()->logicalIndexAt(pos);

        if (column == PRICE_COLUMN_INDEX)
            onPriceFilterRequested();
        else if(column == VOLUME_COLUMN_INDEX)
            onVolumeFilterRequested();
    });

    connect(ui->pushButtonDeselectAll, &QPushButton::clicked, this, [this](){
       ui->listViewStrategies->clearSelection();
    });

    connect(ui->pushButtonShowRunning, &QPushButton::toggled, this, [this](bool checked){
        m_showRunningToggle = checked;
        onStrategyFilterChanged();
    });
    connect(ui->pushButtonShowPaused, &QPushButton::toggled, this, [this](bool checked){
        m_showPausedToggle = checked;
        onStrategyFilterChanged();
    });

    ordersVM->orderModel()->setStrategyNameResolver([this](int strategyId) -> QString {
        const StrategyData strategy = strategiesVM->getStrategy(strategyId);
        return strategy.strategy_name.isEmpty() ? QString("[Unknown]") : strategy.strategy_name;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList deselectedIndexes = deselected.indexes();

    for(auto &index : deselectedIndexes)
        strategiesVM->setStrategySelected(index.data(StrategyRoles::RawDataRole));

    QModelIndexList selectedIndexes = selected.indexes();

    for(auto &index : selectedIndexes)
        strategiesVM->setStrategySelected(index.data(StrategyRoles::RawDataRole));

    ordersVM->applyStrategyFilter(strategiesVM->getSelectedStrategyIds());

    onSelectedStrategiesChanged();
}

void MainWindow::onPriceFilterRequested()
{
    auto priceRange = ordersVM->getOrdersPriceRange();

    if(priceRange.second <= 0) return;

    priceDialog->setRange(priceRange.first, priceRange.second);

    priceDialog->setInfoText("Set Price Range Between Min and Max values:");

    if (priceDialog->exec() == QDialog::Accepted) {
        if (priceDialog->wasClearFilterPressed()) {
            ordersVM->clearPriceFilter();
        } else {
            double min = priceDialog->minValue();
            double max = priceDialog->maxValue();
            ordersVM->setPriceFilter(min, max);
        }
    }
}

void MainWindow::onVolumeFilterRequested()
{
    volumeDialog->setRange(0, 100, true);

    volumeDialog->setInfoText("Set Volume persentage:");

    if (volumeDialog->exec() == QDialog::Accepted) {
        if (volumeDialog->wasClearFilterPressed()) {
            ordersVM->clearVolumeFilter();
        } else {
            double min = volumeDialog->minValue();
            double max = volumeDialog->maxValue();
            ordersVM->setVolumeFilter(min, max);
        }
    }
}

void MainWindow::onSelectedStrategiesChanged()
{
    auto names = strategiesVM->getSelectedStrategyNames();

    if(names.isEmpty()) {
        ui->labelSelectedStrategies->setText("(Showing All Orders)");
    } else {
        QString output = "(";

        for(auto name : names)
            output += name + ", ";

        // sonda virgül varsa kaldır
        if(output.endsWith(", ")){
            output.removeLast();
            output.removeLast();
        }

        output += ")";
        ui->labelSelectedStrategies->setText(output);
    }
}

void MainWindow::onStrategyFilterChanged()
{
    if(m_showPausedToggle == m_showRunningToggle){
        strategiesVM->clearStrategyFilter();
    }
    else if(m_showPausedToggle){
        strategiesVM->setStrategyStateFilter("Paused");
    }
    else if(m_showRunningToggle){
        strategiesVM->setStrategyStateFilter("Running");
    }
}
