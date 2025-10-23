//spora rewolucja
#include <AnalogButtons.h>
#ifndef A1 // esp32 doesn't define analog pins
#define ANALOG_PIN 0
#else
#define ANALOG_PIN A0
#endif

int out1 = 2;
int out2 = 3;
int out3 = 4;
int out4 = 5;
int out5 = 6;
int out6 = 7;
int out7 = 8;
int out8 = 9;
int wh_s = 10;

// A call back function that you pass into the constructor of AnalogButtons, see example
// below. Alternativly you could extend the Button class and re-define the methods pressed() 
// or held() which are called 
void b1Click() {  
    Serial.print("B1_click"); 
}
void b1Hold() {  
    Serial.print("B1_hold"); 
}
void b2Click() {  
    Serial.print("B2_click"); 
}
void b2Hold() {  
    Serial.print("B2_hold"); 
}

void b3Click() {  
    Serial.print("B3_click"); 
}
void b3Hold() {  
    Serial.print("B3_hold"); 
}

void b4Click() {  
    Serial.print("B4_click"); 
}
void b4Hold() {  
    Serial.print("B4_hold"); 
}

void b5Click() {  
    Serial.print("B5_click"); 
}
void b5Hold() {  
    Serial.print("B5_hold"); 
}

void b6Click() {  
    Serial.print("B6_click"); 
}
void b6Hold() {  
    Serial.print("B6_hold"); 
}

void b7Click() {  
    Serial.print("B7_click"); 
}
void b7Hold() {  
    Serial.print("B7_hold"); 
}

void b8Click() {  
    Serial.print("B8_click"); 
}
void b8Hold() {  
    Serial.print("B8_hold"); 
}



AnalogButtons analogButtons(ANALOG_PIN, INPUT, 5, 3);
Button b1 = Button(0, &b1Click, &b1Hold, 1000, 2500);
Button b2 = Button(6, &b2Click, &b2Hold, 1000, 2500);
Button b3 = Button(26, &b3Click, &b3Hold, 1000, 2500);
Button b4 = Button(11, &b4Click, &b4Hold, 1000, 2500);
Button b5 = Button(132, &b5Click, &b5Hold, 1000, 2500);
Button b6 = Button(55, &b6Click, &b6Hold, 1000, 2500);
Button b7 = Button(83, &b7Click, &b7Hold, 1000, 2500);
Button b8 = Button(17, &b8Click, &b8Hold, 1000, 2500);
void setup() {
  Serial.begin(9600);
//  Serial.println("Testing your Analog buttons");

  analogButtons.add(b1);
  analogButtons.add(b2);
  analogButtons.add(b3);
  analogButtons.add(b4);
  analogButtons.add(b5);
  analogButtons.add(b6);
  analogButtons.add(b7);
  analogButtons.add(b8);

// out1-left out2-right turn relays
// out3
// out4 
// out5 
// out6 
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(wh_s, INPUT_PULLUP); 
 }
 
void loop() {  
  // To check values when button are pressed
  analogButtons.check();
  

}

void configure() {
  unsigned int value = analogRead(ANALOG_PIN);
  Serial.println(value);
  delay(250);
}
