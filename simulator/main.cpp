// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2025 BTS

#include "mainwindow.h"

#include <QApplication>

MainWindow* mainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainWindow = new MainWindow();
    mainWindow->show();

    return a.exec();
}
