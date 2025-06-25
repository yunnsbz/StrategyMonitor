#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainViewModel.h"

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    MainViewModel_(new MainViewModel())
{
    ui->setupUi(this);

    ui->splitter->setSizes({400,600});
}

MainWindow::~MainWindow()
{
    delete ui;

}
