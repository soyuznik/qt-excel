#include "mainwindow.h"
#include <QtWidgets>
#include<iostream>
#include<fstream>
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainwindow window(true);








    window.setWindowState(Qt::WindowMaximized);
    window.show();
    return app.exec();


}
