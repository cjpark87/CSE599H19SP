#include "ColorConverterLib.h"
#define MAX_ANALOG_INPUT_VAL 1023
const int LED_OUTPUT = 3;
const int LED_R_OUTPUT = 9;
const int LED_G_OUTPUT = 10;
const int LED_B_OUTPUT = 11;
const int BUZZER_OUTPUT_PIN = 12;
const int PHOTO_INPUT_PIN = A0;
const int REG_INPUT_PIN = A1;
const int PRESS_INPUT_PIN = A2;
uint8_t r,g,b;
double h,s,l;

int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R_OUTPUT, OUTPUT);
  pinMode(LED_G_OUTPUT, OUTPUT);
  pinMode(LED_B_OUTPUT, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(BUZZER_OUTPUT_PIN, OUTPUT);
  pinMode(PHOTO_INPUT_PIN, INPUT);
  pinMode(REG_INPUT_PIN, INPUT);
  pinMode(PRESS_INPUT_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  l = 1.0-min(1.0, max(0, map(analogRead(PHOTO_INPUT_PIN), 500, 750, 0, 500)/1000.0));
  s = 1.0;
  h = min(1.0, max(0.0, map(analogRead(REG_INPUT_PIN), 180, 900, 0, 1000)/1000.0));

  ColorConverter::HslToRgb(h,s,l, r,g,b);
  
  analogWrite(LED_R_OUTPUT, 255-r);
  analogWrite(LED_G_OUTPUT, 255-g);
  analogWrite(LED_B_OUTPUT, 255-b);

  if (analogRead(PRESS_INPUT_PIN) > 250) {
    play();  
  }
  
  delay(100);
}

void play() {
  tone(BUZZER_OUTPUT_PIN, tones[7]);
  light(random(0,255), random(0,255), random(0,255));
  delay(500);
  tone(BUZZER_OUTPUT_PIN, tones[2]);
  light(random(0,255), random(0,255), random(0,255));
  delay(200);
  noTone(BUZZER_OUTPUT_PIN);
  light(0,0,0);
  delay(100);
  tone(BUZZER_OUTPUT_PIN, tones[2]);
  light(random(0,255), random(0,255), random(0,255));
  delay(200);
  tone(BUZZER_OUTPUT_PIN, tones[4]);
  light(random(0,255), random(0,255), random(0,255));
  delay(500);
  tone(BUZZER_OUTPUT_PIN, tones[2]);
  light(random(0,255), random(0,255), random(0,255));
  delay(900);
  noTone(BUZZER_OUTPUT_PIN);
  light(0,0,0);
  delay(100);
  tone(BUZZER_OUTPUT_PIN, tones[6]);
  light(random(0,255), random(0,255), random(0,255));
  delay(500);
  tone(BUZZER_OUTPUT_PIN, tones[7]);
  light(random(0,255), random(0,255), random(0,255));
  delay(500);
  noTone(BUZZER_OUTPUT_PIN);
  light(0,0,0);
  delay(500);
  
}

void light (int r, int g, int b) {
  analogWrite(LED_R_OUTPUT, 255-r);
  analogWrite(LED_G_OUTPUT, 255-g);
  analogWrite(LED_B_OUTPUT, 255-b);
}

