int out1Pin = 2;
int out2Pin = 3;
int out3Pin = 4;
int out4Pin = 5;
int out5Pin = 6;
int out6Pin = 7;
int out7Pin = 8;
int out8Pin = 9;
int buttonPin = 0;
int buttonValue;

#define BTN_NONE 0
#define BTN1 1
#define BTN2 2
#define BTN3 3
#define BTN4 4
#define BTN5 5
#define BTN6 6
#define BTN7 7
#define BTN8 8


void setup() { Serial.begin(9600);}

int getBtn() {
  buttonValue = analogRead(buttonPin);
//  Serial.println(buttonValue);

  if (buttonValue == 0) {return BTN1;}
  if (buttonValue > 4 && buttonValue < 8) {return BTN2;}
  if (buttonValue > 22 && buttonValue < 28) {return BTN3;}
  if (buttonValue > 8 && buttonValue < 13) {return BTN4;}
  if (buttonValue > 52 && buttonValue < 57) {return BTN5;}
  if (buttonValue > 129 && buttonValue < 134) {return BTN6;}
//  if (buttonValue > 80 && buttonValue < 85) {return BTN7;}
//  if (buttonValue > 15 && buttonValue < 20) {return BTN8;}
  return BTN_NONE;
}

void loop() {
  int btn = BTN_NONE;
  unsigned long start = millis();
  while (true) {
    // tu w pętli sprawdzamy stan przycisków i czekamy na zmianę
    int newBtn = getBtn();
    // wykrywajmy zmianę stanu przycisków
    if (newBtn != btn) {
      // jeśli do tej pory jakiś przycisk był wciśnięty
      if (btn != BTN_NONE) {
        // wciśnięty powyżej sekundy???
        if (millis() - start > 1000) {
          Serial.print("LONG ");
          Serial.println(btn);
          // tutaj można dodać kod obsługi długiego wciśnięcia
        } else
         if (millis() - start > 100) {
            Serial.print("SHORT ");
            Serial.println(btn);
            // tutaj można dodać kod obsługi krótkiego wciśnięcia
//            if (BTN1 == SHORT 1) {digitalWrite(out1Pin,HIGH);}
        }
        else {
          Serial.print("TOO SHORT ");
          Serial.println(btn);
        }
      }
      // zapamiętujemy aktualny czas, jeśli przycisk się zmieni to
      // będziemy mogli policzyć czas jego wciśnięcia
      start = millis();
      // zapamiętujemy nowy stan jako bieżący stan
      btn = newBtn;
    }
    if (buttonValue > 81 && buttonValue < 84) {digitalWrite(out7Pin,HIGH);}
    else {digitalWrite(out7Pin,LOW);}
    if (buttonValue > 16 && buttonValue < 18) {digitalWrite(out8Pin,HIGH);}
    else {digitalWrite(out8Pin,LOW);
    }
  }
}