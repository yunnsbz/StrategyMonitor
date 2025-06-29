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
#include "order_model_roles.h"
#include "strategy_model_roles.h"

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ordersVM(new OrdersViewModel(this)),
    m_strategiesVM(new StrategiesViewModel(this)),
    m_dataReceiver(new DataReceiver(m_strategiesVM, m_ordersVM)),
    m_priceDialog(new FilterDialog(this)),
    m_volumeDialog(new FilterDialog(this))
{
    ui->setupUi(this);

    // splitter:
    ui->splitter->setSizes({400,600});
    ui->splitter->widget(0)->setMinimumWidth(320);

    // listView:
    ui->listViewStrategies->setModel(m_strategiesVM->model());

    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->listViewStrategies->setItemDelegate(delegate);

    // tableView
    ui->tableViewOrders->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableViewOrders->setModel(m_ordersVM->model());

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

        // use PRICE_COLUMN_INDEX instead if columns can change on the ui
        // othervise columns can only change in the OrderModel (kHeaderLabels)
        if (column == m_ordersVM->orderModel()->getColumnIndex(OrderRoles::PriceRole))
            onPriceFilterRequested();
        else if(column == m_ordersVM->orderModel()->getColumnIndex(OrderRoles::VolumeRole))
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

    m_ordersVM->orderModel()->setStrategyNameResolver([this](int strategyId) -> QString {
        const StrategyData strategy = m_strategiesVM->getStrategy(strategyId);
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
        m_strategiesVM->setStrategySelected(index.data(StrategyRoles::RawDataRole));

    QModelIndexList selectedIndexes = selected.indexes();

    for(auto &index : selectedIndexes)
        m_strategiesVM->setStrategySelected(index.data(StrategyRoles::RawDataRole));

    m_ordersVM->applyStrategyFilter(m_strategiesVM->getSelectedStrategyIds());

    onSelectedStrategiesChanged();
}

void MainWindow::onPriceFilterRequested()
{
    auto priceRange = m_ordersVM->getOrdersPriceRange();

    if(priceRange.second <= 0) return;

    m_priceDialog->setRange(priceRange.first, priceRange.second);

    m_priceDialog->setTitleText("Set Price Range Between Min and Max values:");

    if (m_priceDialog->exec() == QDialog::Accepted) {
        if (m_priceDialog->wasClearFilterPressed()) {
            m_ordersVM->clearPriceFilter();
        } else {
            double min = m_priceDialog->minValue();
            double max = m_priceDialog->maxValue();
            m_ordersVM->setPriceFilter(min, max);
        }
    }
}

void MainWindow::onVolumeFilterRequested()
{
    m_volumeDialog->setRange(0, 100, true);

    m_volumeDialog->setTitleText("Set Volume percentage:");

    if (m_volumeDialog->exec() == QDialog::Accepted) {
        if (m_volumeDialog->wasClearFilterPressed()) {
            m_ordersVM->clearVolumeFilter();
        } else {
            double min = m_volumeDialog->minValue();
            double max = m_volumeDialog->maxValue();
            m_ordersVM->setVolumeFilter(min, max);
        }
    }
}

void MainWindow::onSelectedStrategiesChanged()
{
    auto names = m_strategiesVM->getSelectedStrategyNames();

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
        m_strategiesVM->clearStrategyFilter();
    }
    else if(m_showPausedToggle){
        m_strategiesVM->setStrategyStateFilter("Paused");
    }
    else if(m_showRunningToggle){
        m_strategiesVM->setStrategyStateFilter("Running");
    }
}
