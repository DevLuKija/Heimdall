#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Heimdall");
    QCoreApplication::setApplicationName("Heimdall");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
