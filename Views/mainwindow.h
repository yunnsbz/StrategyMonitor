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

class MainViewModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected);

    void onPriceFilterRequested();
    void onVolumeFilterRequested();


private:
    Ui::MainWindow *ui;

    MainViewModel* MainVM;

    FilterDialog* priceDialog;
    FilterDialog* volumeDialog;

    static constexpr int PRICE_COLUMN_INDEX = 3;
    static constexpr int VOLUME_COLUMN_INDEX = 4;
    double m_currentPriceFilterMin = 0.0;
    double m_currentPriceFilterMax = 0.0;
    bool m_priceFilterActive = false;

};
#endif // MAINWINDOW_H
