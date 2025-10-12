// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2025 BTS

#ifndef ARDUINO_H
#define ARDUINO_H

#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

class SerialClass
{
public:
    void begin(int baudrate);
    void print(const char* msg);
    void print(int val);
    void println(const char* msg);
    void println(int val);
};

extern SerialClass Serial;

void pinMode(int pin, int mode);
unsigned long millis();
int analogRead(int pin);
void digitalWrite(int pin, int value);
int digitalRead(int pin);

#endif // ARDUINO_H

