// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2025 BTS

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include "Arduino.h"
#include "../definitions.h"

void loop();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->start(5);
    connect(timer, &QTimer::timeout, this, []() {
        loop();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

#define OUTPUT_OFF_SS "color: gray;\nborder: 1px solid gray;"
#define OUTPUT_ON_SS "color: green;\nborder: 2px solid green;"

void MainWindow::setOutput(int pin, int value)
{
    switch (pin) {
        case OUTPUT_TURN_LEFT:
            ui->out1->setStyleSheet(value == HIGH ? OUTPUT_ON_SS : OUTPUT_OFF_SS);
            break;
        case OUTPUT_TURN_RIGHT:
            ui->out2->setStyleSheet(value == HIGH ? OUTPUT_ON_SS : OUTPUT_OFF_SS);
            break;
        // todo
    }
}

int MainWindow::buttonsAsAdc()
{
    if (ui->btn1->isDown()) return BTN_TURN_LEFT_ADC_MIN + 1; // BTN_TURN_LEFT
    if (ui->btn2->isDown()) return BTN_TURN_RIGHT_ADC_MIN + 1; // BTN_TURN_RIGHT
    // todo

    return BTN_NONE_ADC_MAX - 1;
}

void MainWindow::print(QString msg)
{
    ui->log->moveCursor(QTextCursor::End);
    ui->log->insertPlainText(msg);
}

int MainWindow::input(int pin)
{
    switch (pin) {
        case INPUT_1:
            return ui->btn1->isDown() ? LOW : HIGH;
        case INPUT_2:
            return ui->btn2->isDown() ? LOW : HIGH;
        case INPUT_WHEEL_ROT_SENSOR:
            return ui->btn3->isDown() ? LOW : HIGH;
        // todo
    }
    return HIGH;
}

