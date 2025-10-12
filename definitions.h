#ifndef E854D29A_BF8B_4937_A8D1_64B955DA4D53
#define E854D29A_BF8B_4937_A8D1_64B955DA4D53

// Koniecznie trzeba opisać co oznaczają te OUT i BTN, a jeszcze lepiej je ponazywać
//outputs
//TURN_LEFT left turn sigbal
//TURN_RIGHT right turn signal
//OUT3 high-low beam
//OUT4 wiper on-off
//OUT5 wiper speed +
//OUT6 wiper speed -
//OUT7 phone up
//OUT78 phone down

#define OUTPUT_TURN_LEFT 1
#define OUTPUT_TURN_RIGHT 2
#define OUT3_PIN 4
#define OUT4_PIN 5
#define OUT5_PIN 6
#define OUT6_PIN 7
#define OUT7_PIN 8
#define OUT8_PIN 9

//resistive keyboard input
#define BUTTON_PIN 0

//buttons
//BTN_TURN_LEFT-left turn sigbal
//BTN_TURN_RIGHT-right turn signal
//BTN3-high-low beam
//BTN4 wiper on-off
//BTN5 wiper speed +
//BTN5 wiper speed -
//BTN7 phone up
//BTN8 phone down

#define BTN_NONE 0
#define BTN_TURN_LEFT 1
#define BTN_TURN_RIGHT 2
#define BTN3 3
#define BTN4 4
#define BTN5 5
#define BTN6 6
#define BTN7 7
#define BTN8 8

#define BTN_NONE_ADC_MAX 3
#define BTN_TURN_RIGHT_ADC_MIN 4
#define BTN_TURN_RIGHT_ADC_MAX 8
#define BTN_TURN_LEFT_ADC_MIN 15
#define BTN_TURN_LEFT_ADC_MAX 20
#define BTN3_ADC_MAX 28
#define BTN4_ADC_MIN 8
#define BTN4_ADC_MAX 13
#define BTN5_ADC_MIN 52
#define BTN5_ADC_MAX 57
#define BTN6_ADC_MIN 129
#define BTN6_ADC_MAX 134
#define BTN7_ADC_MIN 80
#define BTN7_ADC_MAX 85
#define BTN8_ADC_MIN 200
#define BTN8_ADC_MAX 210

#define INPUT_1 1
#define INPUT_2 2
#define INPUT_WHEEL_ROT_SENSOR 3

#endif /* E854D29A_BF8B_4937_A8D1_64B955DA4D53 */
