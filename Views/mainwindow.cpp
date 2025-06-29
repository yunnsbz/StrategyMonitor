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
    mainVM(new MainViewModel()),
    priceDialog(new FilterDialog(this)),
    volumeDialog(new FilterDialog(this))
{
    ui->setupUi(this);

    // splitter:
    ui->splitter->setSizes({400,600});
    ui->splitter->widget(0)->setMinimumWidth(320);

    // listView:
    ui->listViewStrategies->setModel(mainVM->strategiesModel());

    StrategyDelegate *delegate = new StrategyDelegate(this);
    ui->listViewStrategies->setItemDelegate(delegate);

    // tableView
    ui->tableViewOrders->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableViewOrders->setModel(mainVM->ordersModel());

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList deselectedIndexes = deselected.indexes();

    for(auto &index : deselectedIndexes)
        mainVM->setStrategySelected(index.data(Qt::UserRole+1).toInt());

    QModelIndexList selectedIndexes = selected.indexes();

    for(auto &index : selectedIndexes)
        mainVM->setStrategySelected(index.data(Qt::UserRole+1).toInt());

    onSelectedStrategiesChanged();
}

void MainWindow::onPriceFilterRequested()
{
    auto priceRange = mainVM->getOrdersPriceRange();

    if(priceRange.second <= 0) return;

    priceDialog->setRange(priceRange.first, priceRange.second);

    priceDialog->setInfoText("Set Price Range Between Min and Max values:");

    if (priceDialog->exec() == QDialog::Accepted) {
        if (priceDialog->wasClearFilterPressed()) {
            mainVM->clearPriceFilter();
        } else {
            double min = priceDialog->minValue();
            double max = priceDialog->maxValue();
            mainVM->setPriceFilter(min, max);
        }
    }
}

void MainWindow::onVolumeFilterRequested()
{
    volumeDialog->setRange(0, 100, true);

    volumeDialog->setInfoText("Set Volume persentage:");

    if (volumeDialog->exec() == QDialog::Accepted) {
        if (volumeDialog->wasClearFilterPressed()) {
            mainVM->clearVolumeFilter();
        } else {
            double min = volumeDialog->minValue();
            double max = volumeDialog->maxValue();
            mainVM->setVolumeFilter(min, max);
        }
    }
}

void MainWindow::onSelectedStrategiesChanged()
{
    auto names = mainVM->getSelectedStrategyNames();

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
        mainVM->clearStrategyFilter();
    }
    else if(m_showPausedToggle){
        mainVM->setStrategyStateFilter("Paused");
    }
    else if(m_showRunningToggle){
        mainVM->setStrategyStateFilter("Running");
    }
}
