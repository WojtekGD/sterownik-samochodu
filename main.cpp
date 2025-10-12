
#include <Arduino.h>
#include "definitions.h"

void setup() {
  Serial.begin(9600);

  pinMode(OUTPUT_TURN_LEFT, OUTPUT);
  pinMode(OUTPUT_TURN_RIGHT, OUTPUT);
  pinMode(INPUT_WHEEL_ROT_SENSOR, INPUT_PULLUP);
  // warto ustawić resztę wyjść i wejść
}

int getBtn() {
  int adcValue = analogRead(BUTTON_PIN);

  if (adcValue > BTN_TURN_LEFT_ADC_MIN && adcValue < BTN_TURN_LEFT_ADC_MAX) { return BTN_TURN_LEFT; }
  else if (adcValue > BTN_TURN_RIGHT_ADC_MIN && adcValue < BTN_TURN_RIGHT_ADC_MAX) { return BTN_TURN_RIGHT; }
  else if (adcValue > 22 && adcValue < 28) { return BTN3; }
  else if (adcValue > 8 && adcValue < 13) { return BTN4; }
  else if (adcValue > 52 && adcValue < 57) { return BTN5; }
  else if (adcValue > 129 && adcValue < 134) { return BTN6; }
  else if (adcValue > 80 && adcValue < 85) { return BTN7; }
  else if (adcValue > 15 && adcValue < 20) { return BTN8; }

  return BTN_NONE;
}

// funkcja zwraca nowy przycisk dopiero kiedy jego stan się ustabilizuje
// czyli nie zmieni przez 50ms (debouncing)
int getDebouncedBtn() {
  // to jest stan "stały", czyli po deobuncingu (min 50ms), static to zmienne których wartość
  // jest zachowywana pomiędzy wywołaniami funkcji
  static int currentButton = BTN_NONE;
  // tu będziemy zapisywać stan "chwilowy", taki stan przechodzi
  // do stanu stałego jeśli się nie zmieni przez 50ms (debouncing)
  static int debouncingButton = 0;
  static unsigned long firstSeen = 0;

  int buttonValue = getBtn();
  if (buttonValue != debouncingButton) {
    // zmiana przycisku, resetujemy licznik czasu
    firstSeen = millis();
    debouncingButton = buttonValue;
    // nie uzysknęliśmy jeszcze stabilnego stanu
  } else if (millis() - firstSeen > 50) {
    // minęło 50ms, przycisk się nie zmienił, więc
    // uzyskaliśmy stabilny stan
    currentButton = debouncingButton;
  }

  return currentButton;
}

void loop() {
  static int btn = BTN_NONE;
  static unsigned long start = millis();
  static unsigned long turnLeftStopTime = 0;
  static unsigned long turnRightStopTime = 0;

    // tu w pętli sprawdzamy stan przycisków i czekamy na zmianę
    int newBtn = getDebouncedBtn();
    // wykrywajmy zmianę stanu przycisków
    if (newBtn != btn) {
      Serial.print("Button changed from ");
      Serial.print(btn);
      Serial.print(" to ");
      Serial.println(newBtn);

      // jeśli do tej pory jakiś przycisk był wciśnięty
      if (btn != BTN_NONE) {
        // obsługa wciśnięcia przycisku

        // wciśnięty powyżej sekundy???
        if (millis() - start > 1000) {
          // obsługa długiego wciśnięcia
          switch (btn) {
            case BTN_TURN_LEFT:
              // po prostu włącz
              digitalWrite(OUTPUT_TURN_LEFT, HIGH);
              break;
          }
        } else if (millis() - start > 150) {
          // obsługa krótkiego wciśnięcia
          switch (btn) {
            case BTN_TURN_LEFT:
              // jeśli którykolwiek z kierunkowskazów jest włączony to go wyłącz, w przeciwnym razie włącz LEWY
              if (digitalRead(OUTPUT_TURN_LEFT) == LOW || digitalRead(OUTPUT_TURN_RIGHT) == LOW) {
                digitalWrite(OUTPUT_TURN_LEFT, LOW);
                digitalWrite(OUTPUT_TURN_LEFT, LOW);
              } else {
                digitalWrite(OUTPUT_TURN_LEFT, HIGH);
                turnLeftStopTime = 0; // deaktywuj timer
              }
              break;
          }

          // zakładam, że krótkie wciśnięcie to powyżej 50ms, może wyeliminujemy ewentualne przypadkowe
          // naciśnięcia, tu obsłużmy między innymi załączanie kierunkowskazu

          // switch (btn) {
          //   case BTN7:
          //     // włącz kierunkowskaz 1 i dla pewności wyłącz 2
          //     digitalWrite(OUT8_PIN, LOW);
          //     digitalWrite(OUT7_PIN, HIGH);
          //     break;
          //   case BTN8:
          //     // włącz kierunkowskaz 2 i dla pewności wyłącz 1
          //     digitalWrite(OUT7_PIN, LOW);
          //     digitalWrite(OUT8_PIN, HIGH);
          //     break;
          // }
        }
      } else {
        // tu obsługa puszczenia przycisku, np kierunkowskazów
        // switch (btn) {
        //   case BTN7:
        //   case BTN8:
        //     // wyłączamy dla pewności oba kierunkowskazy
        //     digitalWrite(OUT7_PIN, LOW);
        //     digitalWrite(OUT8_PIN, LOW);
        //     break;
        // }
      }

      // zapamiętujemy aktualny czas, jeśli przycisk się zmieni to
      // będziemy mogli policzyć czas jego wciśnięcia
      start = millis();
      // zapamiętujemy nowy stan jako bieżący stan
      btn = newBtn;
    }

    if (turnLeftStopTime != 0 && millis() > turnLeftStopTime) {
      // czas wyłączenia minął, wyłączamy kierunkowskaz
      digitalWrite(OUTPUT_TURN_LEFT, LOW);
      turnLeftStopTime = 0; // deaktywuj timer
    } else if (turnLeftStopTime == 0 && digitalRead(OUTPUT_TURN_LEFT) == HIGH && digitalRead(INPUT_WHEEL_ROT_SENSOR) == LOW) {
      // kierunkowskaz włączon długim wciśnięciem, czujnik wykrył obrót koła, wyłącz za sekundę
      turnLeftStopTime = millis() + 1000;
    }

    // if (turnRightStopTime != 0 && millis() > turnRightStopTime) {
    //   // czas wyłączenia minął, wyłączamy kierunkowskaz
    //   digitalWrite(OUTPUT_TURN_RIGHT, LOW);
    //   turnRightStopTime = 0; // deaktywuj timer
    // }
  //}
}
