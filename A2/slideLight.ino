#include "ColorConverterLib.h"
#define MAX_ANALOG_INPUT_VAL 1023
const int PRESSED_THRESHOLD = 20;
const int LED_R_OUTPUT = 9;
const int LED_G_OUTPUT = 10;
const int LED_B_OUTPUT = 11;
const int PRESS_INPUT_PIN_1 = A0;
const int PRESS_INPUT_PIN_2 = A1;
const int PRESS_INPUT_PIN_3 = A2;

const bool curr_button1 = true;
const bool curr_button2 = false;
const bool curr_button3 = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R_OUTPUT, OUTPUT);
  pinMode(LED_G_OUTPUT, OUTPUT);
  pinMode(LED_B_OUTPUT, OUTPUT);
  pinMode(PRESS_INPUT_PIN_1, INPUT);
  pinMode(PRESS_INPUT_PIN_2, INPUT);
  pinMode(PRESS_INPUT_PIN_3, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool button1 = analogRead(PRESS_INPUT_PIN_1) > PRESSED_THRESHOLD? true: false;
  bool button2 = analogRead(PRESS_INPUT_PIN_2) > PRESSED_THRESHOLD? true: false;
  bool button3 = analogRead(PRESS_INPUT_PIN_3) > PRESSED_THRESHOLD? true: false;

  setColorAndLightUp(button1, button2, button3);

  delay(100);

  Serial.print(analogRead(PRESS_INPUT_PIN_1));
  Serial.print(",");
  Serial.print(analogRead(PRESS_INPUT_PIN_2));
  Serial.print(",");
  Serial.println(analogRead(PRESS_INPUT_PIN_3));
}

void setColorAndLightUp (bool button1, bool button2, bool button3) {
  double h,s,l;
  uint8_t r,g,b;

  s = 1.0;
  l = 0.0;
  
  if (button1 && button2 && button3) {
    //moon color
    h = 40.0/360.0;
    l = 0.5;
  } else if (button1 && !button2 && button3) {
    //sky color
    h = 200.0/360.0;
    l = 0.5;
  } else if (button1 && button2 && !button3) {
    //sun color
    h = 10.0/360.0;
    l = 0.5;
  } else if (button1 && !button2 && !button3) {
    //bright bulb color
    h = 1.0;
    l = 1.0;
  }

  ColorConverter::HslToRgb(h,s,l, r,g,b);

  analogWrite(LED_R_OUTPUT, 255-r);
  analogWrite(LED_G_OUTPUT, 255-g);
  analogWrite(LED_B_OUTPUT, 255-b);
}
