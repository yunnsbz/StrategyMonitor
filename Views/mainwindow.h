#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filterdialog.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QItemSelection>
#include <QListView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DataReceiver;
class StrategiesViewModel;
class OrdersViewModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected);

    void onPriceFilterRequested();
    void onVolumeFilterRequested();
    void onSelectedStrategiesChanged();

    void onStrategyFilterChanged();

private:
    Ui::MainWindow *ui;

    StrategiesViewModel* m_strategiesVM;
    OrdersViewModel* m_ordersVM;

    DataReceiver* m_dataReceiver;

    FilterDialog* m_priceDialog;
    FilterDialog* m_volumeDialog;

    static constexpr int SIDE_COLUMN_INDEX = 2;
    static constexpr int PRICE_COLUMN_INDEX = 3;
    static constexpr int VOLUME_COLUMN_INDEX = 4;
    double m_currentPriceFilterMin = 0.0;
    double m_currentPriceFilterMax = 0.0;
    bool m_priceFilterActive = false;

    // Strategy Filters:
    bool m_showRunningToggle = false;
    bool m_showPausedToggle = false;


};
#endif // MAINWINDOW_H
