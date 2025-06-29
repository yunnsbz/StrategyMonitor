#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "HeaderWithIcons.h"
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

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ordersVM(new OrdersViewModel(this)),
    m_strategiesVM(new StrategiesViewModel(this)),
    m_dataReceiver(new DataReceiver(m_strategiesVM, m_ordersVM)),
    m_priceDialog(new FilterDialog(this)),
    m_filledVolDialog(new FilterDialog(this)),
    m_activeVolDialog(new FilterDialog(this)),
    m_header(new HeaderWithIcons(Qt::Horizontal, this))
{
    ui->setupUi(this);

    // splitter:
    ui->splitter->setSizes({200,600});
    ui->splitter->widget(0)->setMinimumWidth(320);

    // listView:
    ui->listViewStrategies->setModel(m_strategiesVM->model());

    auto *delegate = new StrategyDelegate(this);
    ui->listViewStrategies->setItemDelegate(delegate);

    // tableView
    ui->tableViewOrders->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableViewOrders->setModel(m_ordersVM->model());

    ui->tableViewOrders->setHorizontalHeader(m_header);
    ui->tableViewOrders->setSortingEnabled(true);
    auto *orderTypeDelegate = new OrderTypeDelegate(this);
    ui->tableViewOrders->setItemDelegateForColumn(SIDE_COLUMN_INDEX, orderTypeDelegate);

    // strategies filter button toggles
    ui->pushButtonShowRunning->setCheckable(true);
    ui->pushButtonShowPaused->setCheckable(true);

    connect(m_ordersVM, &OrdersViewModel::orderFilterChanged, this, &MainWindow::onOrderFilterChanged);

    // list item onClick
    connect(ui->listViewStrategies->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onMultipleListItemClicked);

    // table header column onRightClick
    connect(ui->tableViewOrders->horizontalHeader(), &QHeaderView::customContextMenuRequested, this,
            [this](const QPoint& pos) {
        const int column = ui->tableViewOrders->horizontalHeader()->logicalIndexAt(pos);

        // use PRICE_COLUMN_INDEX instead if columns can change on the ui
        // othervise columns can only change in the OrderModel (kHeaderLabels)
        if (column == m_ordersVM->orderModel()->getColumnIndex(OrderRoles::PriceRole))
            onPriceFilterRequested();
        else if(column == m_ordersVM->orderModel()->getColumnIndex(OrderRoles::FilledVolumeRole))
            onFiledVolFilterRequested();
        else if(column == m_ordersVM->orderModel()->getColumnIndex(OrderRoles::ActiveVolumeRole))
            onActiveVolFilterRequested();
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
    const QModelIndexList deselectedIndexes = deselected.indexes();

    for(const auto &index : deselectedIndexes)
        m_strategiesVM->setStrategySelected(index.data(StrategyRoles::RawDataRole));

    const QModelIndexList selectedIndexes = selected.indexes();

    for(const auto &index : selectedIndexes)
        m_strategiesVM->setStrategySelected(index.data(StrategyRoles::RawDataRole));

    m_ordersVM->applyStrategyFilter(m_strategiesVM->getSelectedStrategyIds());

    onSelectedStrategiesChanged();
}

void MainWindow::onPriceFilterRequested()
{
    const auto priceRange = m_ordersVM->getOrdersPriceRange();

    if(priceRange.second <= 0) return;

    m_priceDialog->setRange(priceRange.first, priceRange.second);

    m_priceDialog->setTitleText("Set Price Range Between Min and Max values");

    if (m_priceDialog->exec() == QDialog::Accepted) {
        if (m_priceDialog->wasClearFilterPressed()) {
            m_ordersVM->clearPriceFilter();
        } else {
            const double min = m_priceDialog->minValue();
            const double max = m_priceDialog->maxValue();
            m_ordersVM->setPriceFilter(min, max);
        }
    }
}

void MainWindow::onFiledVolFilterRequested()
{
    const auto volRange = m_ordersVM->getFilledVolRange();

    m_filledVolDialog->setRange(volRange.first, volRange.second);

    m_filledVolDialog->setTitleText("Set Volume Range Between Min and Max values");

    if (m_filledVolDialog->exec() == QDialog::Accepted) {
        if (m_filledVolDialog->wasClearFilterPressed()) {
            m_ordersVM->clearFilledVolFilter();
        } else {
            const double min = m_filledVolDialog->minValue();
            const double max = m_filledVolDialog->maxValue();
            m_ordersVM->setFilledVolFilter(min, max);
        }
    }
}

void MainWindow::onActiveVolFilterRequested()
{
    const auto volRange = m_ordersVM->getActiveVolRange();

    m_activeVolDialog->setRange(volRange.first, volRange.second);

    m_activeVolDialog->setTitleText("Set Volume Range Between Min and Max values");

    if (m_activeVolDialog->exec() == QDialog::Accepted) {
        if (m_activeVolDialog->wasClearFilterPressed()) {
            m_ordersVM->clearActiveVolFilter();
        } else {
            const double min = m_activeVolDialog->minValue();
            const double max = m_activeVolDialog->maxValue();
            m_ordersVM->setActiveVolFilter(min, max);
        }
    }
}

void MainWindow::onOrderFilterChanged(int column, bool state)
{
    if (state) {
        m_header->setIconForSection(column, QIcon(":/icons/Views/filter-icon.png"));
    } else {
        m_header->clearIconForSection(column);
    }
}

void MainWindow::onSelectedStrategiesChanged()
{
    const auto names = m_strategiesVM->getSelectedStrategyNames();

    if(names.isEmpty()) {
        ui->labelSelectedStrategies->setText("(Showing All Orders)");
    } else {
        QString output = "(";

        for(const auto &name : names)
            output += name + ", ";

        // sonda virgül varsa kaldır
        if(output.endsWith(", ")){
            output.removeLast();
            output.removeLast();
        }

        if (output.length() >= 50) {
            output = output.left(50);
            output += "...";
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

void MainWindow::on_actionHowSimulationWorks_triggered()
{
    const QString infoText =
            "How Simulation Works:\n\n"
            "• QTimer triggers the creation of a new strategy and order every few seconds.\n"
            "• These strategies and orders are created with completely random ranges and values.\n"
            "• The data in the view model is received with the receiver and transferred to the models.\n";

        QMessageBox::information(this, "How Simulation Works", infoText);
}


void MainWindow::on_actionHowToUse_triggered()
{
    const QString infoText =
            "• Right click on the table header titles to filter. (only on price and volumes)\n"
            "• Select the range from the popup menu and apply the filter.\n"
            "• To remove the filter, open the filter window again and click restore defaults.\n"
            "• Click on the headings to sort the table.\n"
            "• You can filter strategies based on their status.\n";

        QMessageBox::information(this, "How To Use", infoText);
}

