#include "mainwindow.h"
#include <QStyleFactory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Stil listesi: "Fusion", "Windows", "WindowsVista"
    // a.setStyle(QStyleFactory::create("WindowsVista"));

    MainWindow w;
    w.show();
    return a.exec();
}
