// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2025 BTS

#include <QDateTime>
#include "Arduino.h"
#include "mainwindow.h"

int pins[10];
extern MainWindow* mainWindow;

void pinMode(int pin, int mode) {}

unsigned long millis() {
    return QDateTime::currentMSecsSinceEpoch();
}

int analogRead(int pin) {
    return mainWindow->buttonsAsAdc();
}

void digitalWrite(int pin, int value) {
    pins[pin] = value;
    mainWindow->setOutput(pin, value);
    Serial.print("Digital write pin ");
    Serial.print(pin);
    Serial.print(" value ");
    Serial.println(value);
}

int digitalRead(int pin) {
    return pins[pin];
}

// serial

void SerialClass::begin(int baudrate)
{
    mainWindow->print("Serial started");
}

void SerialClass::print(const char *msg)
{
    mainWindow->print(QString(msg));
}

void SerialClass::print(int val)
{
    mainWindow->print(QString::number(val));
}

void SerialClass::println(const char *msg)
{
    mainWindow->print(QString(msg) + "\n");
}

void SerialClass::println(int val)
{
    mainWindow->print(QString::number(val) + "\n");
}

SerialClass Serial;
