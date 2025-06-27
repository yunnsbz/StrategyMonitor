#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

public slots:
    void OnMultipleListItemClicked(const QItemSelection &selected, const QItemSelection &deselected);


private:
    Ui::MainWindow *ui;

    MainViewModel* MainVM;

};
#endif // MAINWINDOW_H
