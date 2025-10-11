// Koniecznie trzeba opisać co oznaczają te OUT i BTN, a jeszcze lepiej je ponazywać
//outputs
//OUT1 left turn sigbal
//OUT2 right turn signal
//OUT3 high-low beam
//OUT4 wiper on-off
//OUT5 wiper speed +
//OUT6 wiper speed -
//OUT7 phone up
//OUT78 phone down

#define OUT1_PIN 2
#define OUT2_PIN 3
#define OUT4_PIN 5
#define OUT5_PIN 6
#define OUT6_PIN 7
#define OUT7_PIN 8
#define OUT8_PIN 9

//resistive keyboard input
#define BUTTON_PIN 0

//buttons
//BTN1-left turn sigbal
//BTN2-right turn signal
//BTN3-high-low beam
//BTN4 wiper on-off
//BTN5 wiper speed +
//BTN5 wiper speed -
//BTN7 phone up
//BTN8 phone down

#define BTN_NONE 0
#define BTN1 1
#define BTN2 2
#define BTN3 3
#define BTN4 4
#define BTN5 5
#define BTN6 6
#define BTN7 7
#define BTN8 8

int buttonValue;

void setup() { Serial.begin(9600);}

int getBtn() {
  int adcValue = analogRead(BUTTON_PIN);
  if (adcValue > 4 && adcValue < 8) { return BTN2; }
  else if (adcValue > 22 && adcValue < 28) { return BTN3; }
  else if (adcValue > 8 && adcValue < 13) { return BTN4; }
  else if (adcValue > 52 && adcValue < 57) { return BTN5; }
  else if (adcValue > 129 && adcValue < 134) { return BTN6; }
  else if (adcValue > 80 && adcValue < 85) { return BTN7; }
  else if (adcValue > 15 && adcValue < 20) { return BTN8; }

  return BTN_NONE;
}

int getDebouncedBtn() {
  // to jest stan "stały", czyli po deobuncingu (min 50ms), static to zmienne których wartość
  // jest zachowywana pomiędzy wywołaniami funkcji
  static int currentButton = BTN_NONE;
  // tu będziemy zapisywać stan "chwilowy", taki stan przechodzi
  // do stanu stałego jeśli się nie zmieni przez 50ms (debouncing)
  static int debouncingButton = 0;
  static int firstSeen = 0;

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

//  Serial.println(buttonValue);
//measured voltage values ​​for individual buttons
  if (buttonValue == 0) { return BTN_NONE; }
  if (buttonValue > 4 && buttonValue < 8) { return BTN2; }
  if (buttonValue > 22 && buttonValue < 28) { return BTN3; }
  if (buttonValue > 8 && buttonValue < 13) { return BTN4; }
  if (buttonValue > 52 && buttonValue < 57) { return BTN5; }
  if (buttonValue > 129 && buttonValue < 134) { return BTN6; }
  if (buttonValue > 80 && buttonValue < 85) { return BTN7; }
  if (buttonValue > 15 && buttonValue < 20) { return BTN8; }

  return BTN_NONE;
}

void loop() {
  int btn = BTN_NONE;
  unsigned long start = millis();
  while (true) {
    // tu w pętli sprawdzamy stan przycisków i czekamy na zmianę
    int newBtn = getDebouncedBtn();
    // wykrywajmy zmianę stanu przycisków
    if (newBtn != btn) {
      // jeśli do tej pory jakiś przycisk był wciśnięty
      if (btn != BTN_NONE) {
        // obsługa wciśnięcia przycisku

        // wciśnięty powyżej sekundy???
        if (millis() - start > 1000) {
          Serial.print("LONG ");
          Serial.println(btn);
          // tutaj można dodać kod obsługi długiego wciśnięcia
          // ...
        } else if (millis() - start > 50) {
          // zakładam, że krótkie wciśnięcie to powyżej 50ms, może wyeliminujemy ewentualne przypadkowe
          // naciśnięcia, tu obsłużmy między innymi załączanie kierunkowskazu

          switch (btn) {
            case BTN7:
              // włącz kierunkowskaz 1 i dla pewności wyłącz 2
              digitalWrite(OUT8_PIN, LOW);
              digitalWrite(OUT7_PIN, HIGH);
              break;
            case BTN8:
              // włącz kierunkowskaz 2 i dla pewności wyłącz 1
              digitalWrite(OUT7_PIN, LOW);
              digitalWrite(OUT8_PIN, HIGH);
              break;
          }
        }
      } else {
        // tu obsługa puszczenia przycisku, np kierunkowskazów
        switch (btn) {
          case BTN7:
          case BTN8:
            // wyłączamy dla pewności oba kierunkowskazy
            digitalWrite(OUT7_PIN, LOW);
            digitalWrite(OUT8_PIN, LOW);
            break;
        }
      }

      // zapamiętujemy aktualny czas, jeśli przycisk się zmieni to
      // będziemy mogli policzyć czas jego wciśnięcia
      start = millis();
      // zapamiętujemy nowy stan jako bieżący stan
      btn = newBtn;
    }
  }
}
