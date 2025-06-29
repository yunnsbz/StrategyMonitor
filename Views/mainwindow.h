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

    /**
     * used to show only one state from strategies.
     * there are two states: "Running" and "Paused".
     */
    void onSelectedStrategiesChanged();

private slots:
    void onMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected);

    void onPriceFilterRequested();
    void onVolumeFilterRequested();

    /**
     * used for strategy state toggle buttons
     */
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

    // Strategy state filters
    bool m_showRunningToggle = false;
    bool m_showPausedToggle = false;
};
#endif // MAINWINDOW_H
