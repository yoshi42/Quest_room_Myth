//Code for heart beating
#include <SoftwareSerial.h>
#include "FastLED.h"          // библиотека для работы с лентой

#define LED_COUNT 23          // число светодиодов в кольце/ленте

#define LED_DT0 5             // пин, куда подключен DIN ленты
#define LED_DT1 6
#define LED_DT2 7
#define LED_DT3 8
#define LED_DT4 9
#define LED_DT5 10
#define LED_DT6 11           


int max_bright = 255;         // максимальная яркость (0 - 25)

// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
struct CRGB leds0[LED_COUNT];
struct CRGB leds1[LED_COUNT];
struct CRGB leds2[LED_COUNT];
struct CRGB leds3[LED_COUNT];
struct CRGB leds4[LED_COUNT];
struct CRGB leds5[LED_COUNT];
struct CRGB leds6[LED_COUNT];

int delay1 = 217;          //-FX LOOPS DELAY VAR
int delay2 = 72;          //-FX LOOPS DELAY VAR
int delay3 = 45;          //-FX LOOPS DELAY VAR
int delay4 = 36;          //-FX LOOPS DELAY VAR

int thisdelay = 217;          //-FX LOOPS DELAY VAR
int thisstep = 0;           //-FX LOOPS DELAY VAR
int thishue = 0;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR


int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------



#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        2  //Serial Transmit pin
#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW



int zamok1 = 15;
int zamok2 = 14;
int light = 13;

int s1 = 16;
int s2 = 17;
int s3 = 18;
int s4 = 19;

int sens = 12;

int p_sens = 0;
int start = 0;
int brightness = 10;

String string0 = "Master_Heart_on#";
String string1 = "Master_Heart_1#";
String string2 = "Master_Heart_2#";
String string3 = "Master_Heart_3#";
String string4 = "Master_Heart_dead#";
String string5 = "Master_Heart_off#";
String string6 = "Master_Heart_open#";
String string;


String stringitem = "Slave_Heart_itemInside#";

unsigned long time0 = 0;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup() {
  Serial.begin(9600);              // открыть порт для связи
  //Serial.println("setup done");
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, LOW);
  RS485Serial.begin(9600);

  pinMode(zamok1, OUTPUT);
  pinMode(zamok2, OUTPUT);
  pinMode(light, OUTPUT);

  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);

  pinMode(sens, INPUT_PULLUP);

  digitalWrite(zamok1, LOW);
  digitalWrite(zamok2, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);


  LEDS.setBrightness(max_bright);  // ограничить максимальную яркость
  LEDS.addLeds<WS2811, LED_DT0, GRB>(leds0, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  LEDS.addLeds<WS2811, LED_DT1, GRB>(leds1, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  LEDS.addLeds<WS2811, LED_DT2, GRB>(leds2, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  LEDS.addLeds<WS2811, LED_DT3, GRB>(leds3, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  LEDS.addLeds<WS2811, LED_DT4, GRB>(leds4, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  LEDS.addLeds<WS2811, LED_DT5, GRB>(leds5, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  LEDS.addLeds<WS2811, LED_DT6, GRB>(leds6, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
}



void loop() {
  digitalWrite(SSerialTxControl, LOW);
  if (Serial.available()) {
      string = "";
    delay(100);
    tx();
  }

  color_bounceFADE();
}


void tx() {                          // розпізнання команди
  digitalWrite(SSerialTxControl, LOW);
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#')
    {
      if (string.equals(string0))
      {
        message_on();
      }
      if (string.equals(string1) )
      {
        message_1();
      }
      if (string.equals(string2))
      {
        message_2();
      }
      if (string.equals(string3))
      {
        message_3();
      }
      if (string.equals(string4))
      {
        time0 = millis();
        message_dead();
      }
      if (string.equals(string5))
      {
        start = 0;
        p_sens = 0;
        brightness = 1;
        digitalWrite(s1, LOW);
        digitalWrite(s2, LOW);
        digitalWrite(s3, LOW);
        digitalWrite(s4, LOW);
        one_color_all(0, 0, 0);          // погасить все светодиоды
        LEDS.show();                     // отослать команду
      }
      if (string.equals(string6))
      {
        digitalWrite(zamok1, HIGH);
        digitalWrite(zamok2, HIGH);
        delay(20*brightness);
        digitalWrite(zamok1, LOW);
        digitalWrite(zamok2, LOW);
      }
      string = "";
    }
  }
  loop();
}


void message_on() {
  if (digitalRead(sens) == LOW) {
    digitalWrite(zamok1, HIGH);
    delay(20*brightness);
    digitalWrite(zamok1, LOW);
  }
}

void message_1() {     
  //Serial.println("message1");             
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  thisdelay = delay1;
  start = 1;
  brightness = 5;
  color_bounceFADE();

}
void message_2() {
  //Serial.println("message2");
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, LOW);
  thisdelay = delay2;
  start = 1;
  brightness = 7;
  color_bounceFADE();

}
void message_3() {
  digitalWrite(zamok1, HIGH);
  delay(1000);
  digitalWrite(zamok1, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, HIGH);
  digitalWrite(light, HIGH);
  thisdelay = delay3;
  p_sens = 1;
  start = 1;
  brightness = 9;
   color_bounceFADE();

}


void message_dead() {
  p_sens = 0;
  while (millis() - time0 < 10000) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    digitalWrite(s4, LOW);
    start = 1;
    thisdelay = delay4;
    brightness = 10;
     color_bounceFADE();
  }
  while (millis() - time0 > 10000 && millis() - time0 < 20000) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    digitalWrite(s4, LOW);
    start = 1;
    thisdelay = delay2;
    brightness = 7;
    color_bounceFADE();
  }
  while (millis() - time0 > 20000 && millis() - time0 < 30000) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    digitalWrite(s4, HIGH);
    start = 1;
    thisdelay = delay3;
    brightness = 9;
     color_bounceFADE();
  }
  while (millis() - time0 > 30000 && millis() - time0 < 50000) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, HIGH);
    digitalWrite(s3, LOW);
    digitalWrite(s4, LOW);
    start = 1;
    thisdelay = delay1;
    brightness = 5;
     color_bounceFADE();
  }
  if (millis() - time0 > 50000) {
    start = 0;
    p_sens = 0;
    brightness = 10;
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    digitalWrite(s4, LOW);
    one_color_all(0, 0, 0);          // погасить все светодиоды
    LEDS.show();                     // отослать команду
    color_bounceFADE();
    

  }

}





void color_bounceFADE() {                    //-m6-BOUNCE COLOR (SIMPLE MULTI-LED FADE)
    if (p_sens == 1 && digitalRead(sens) == LOW)
    {
      digitalWrite(SSerialTxControl, HIGH);
      Serial.println(stringitem);
      digitalWrite(zamok2, HIGH);
      delay(1000);
      digitalWrite(zamok2, LOW);
      digitalWrite(SSerialTxControl, LOW);
      p_sens = 0;
      start = 0;
      time0 = millis();
      message_dead();
    }

  if (start == 1) {

    idex = idex + 1;
    if (idex == LED_COUNT  ) {
      idex = 0;
    }


    int iL1 = adjacent_cw(idex);
    int iL2 = adjacent_cw(iL1);
    int iL3 = adjacent_cw(iL2);
    int iL4 = adjacent_cw(iL3);
    int iR1 = adjacent_ccw(idex);
    int iR2 = adjacent_ccw(iR1);
    int iR3 = adjacent_ccw(iR2);
    int iR4 = adjacent_ccw(iR3);
    for (int i = 0; i < LED_COUNT; i++ ) {
        if (Serial.available()) {
    tx();
  }


      if (i == idex) {
        leds0[i] = CHSV(thishue, thissat, 25*brightness);
        leds1[i] = CHSV(thishue, thissat, 25*brightness);
        leds2[i] = CHSV(thishue, thissat, 25*brightness);
        leds3[i] = CHSV(thishue, thissat, 25*brightness);
        leds4[i] = CHSV(thishue, thissat, 25*brightness);
        leds5[i] = CHSV(thishue, thissat, 25*brightness);
        leds6[i] = CHSV(thishue, thissat, 25*brightness);

      }
      else if (i == iL1) {
        leds0[i] = CHSV(thishue, thissat, 20*brightness);
        leds1[i] = CHSV(thishue, thissat, 20*brightness);
        leds2[i] = CHSV(thishue, thissat, 20*brightness);
        leds3[i] = CHSV(thishue, thissat, 20*brightness);
        leds4[i] = CHSV(thishue, thissat, 20*brightness);
        leds5[i] = CHSV(thishue, thissat, 20*brightness);
        leds6[i] = CHSV(thishue, thissat, 20*brightness);
      }
      else if (i == iL2) {
        leds0[i] = CHSV(thishue, thissat, 15*brightness);
        leds1[i] = CHSV(thishue, thissat, 15*brightness);
        leds2[i] = CHSV(thishue, thissat, 15*brightness);
        leds3[i] = CHSV(thishue, thissat, 15*brightness);
        leds4[i] = CHSV(thishue, thissat, 15*brightness);
        leds5[i] = CHSV(thishue, thissat, 15*brightness);
        leds6[i] = CHSV(thishue, thissat, 15*brightness);
      }
      else if (i == iL3) {
        leds0[i] = CHSV(thishue, thissat, 8*brightness);
        leds1[i] = CHSV(thishue, thissat, 8*brightness);
        leds2[i] = CHSV(thishue, thissat, 8*brightness);
        leds3[i] = CHSV(thishue, thissat, 8*brightness);
        leds4[i] = CHSV(thishue, thissat, 8*brightness);
        leds5[i] = CHSV(thishue, thissat, 8*brightness);
        leds6[i] = CHSV(thishue, thissat, 8*brightness);
      }
      else if (i == iL4) {
        leds0[i] = CHSV(thishue, thissat, 2*brightness);
        leds1[i] = CHSV(thishue, thissat, 2*brightness);
        leds2[i] = CHSV(thishue, thissat, 2*brightness);
        leds3[i] = CHSV(thishue, thissat, 2*brightness);
        leds4[i] = CHSV(thishue, thissat, 2*brightness);
        leds5[i] = CHSV(thishue, thissat, 2*brightness);
        leds6[i] = CHSV(thishue, thissat, 2*brightness);
      }
      else if (i == iR1) {
        leds0[i] = CHSV(thishue, thissat, 20*brightness);
        leds1[i] = CHSV(thishue, thissat, 20*brightness);
        leds2[i] = CHSV(thishue, thissat, 20*brightness);
        leds3[i] = CHSV(thishue, thissat, 20*brightness);
        leds4[i] = CHSV(thishue, thissat, 20*brightness);
        leds5[i] = CHSV(thishue, thissat, 20*brightness);
        leds6[i] = CHSV(thishue, thissat, 20*brightness);
      }
      else if (i == iR2) {
        leds0[i] = CHSV(thishue, thissat, 15*brightness);
        leds1[i] = CHSV(thishue, thissat, 15*brightness);
        leds2[i] = CHSV(thishue, thissat, 15*brightness);
        leds3[i] = CHSV(thishue, thissat, 15*brightness);
        leds4[i] = CHSV(thishue, thissat, 15*brightness);
        leds5[i] = CHSV(thishue, thissat, 15*brightness);
        leds6[i] = CHSV(thishue, thissat, 15*brightness);
      }
      else if (i == iR3) {
        leds0[i] = CHSV(thishue, thissat, 8*brightness);
        leds1[i] = CHSV(thishue, thissat, 8*brightness);
        leds2[i] = CHSV(thishue, thissat, 8*brightness);
        leds3[i] = CHSV(thishue, thissat, 8*brightness);
        leds4[i] = CHSV(thishue, thissat, 8*brightness);
        leds5[i] = CHSV(thishue, thissat, 8*brightness);
        leds6[i] = CHSV(thishue, thissat, 8*brightness);
      }
      else if (i == iR4) {
        leds0[i] = CHSV(thishue, thissat, 2*brightness);
        leds1[i] = CHSV(thishue, thissat, 2*brightness);
        leds2[i] = CHSV(thishue, thissat, 2*brightness);
        leds3[i] = CHSV(thishue, thissat, 2*brightness);
        leds4[i] = CHSV(thishue, thissat, 2*brightness);
        leds5[i] = CHSV(thishue, thissat, 2*brightness);
        leds6[i] = CHSV(thishue, thissat, 2*brightness);
      }
      else {
        leds0[i] = CHSV(0, 0, 0);
        leds1[i] = CHSV(0, 0, 0);
        leds2[i] = CHSV(0, 0, 0);
        leds3[i] = CHSV(0, 0, 0);
        leds4[i] = CHSV(0, 0, 0);
        leds5[i] = CHSV(0, 0, 0);
        leds6[i] = CHSV(0, 0, 0);
      }
    }
    LEDS.show();
    delay(thisdelay);
  }
}

//---FIND ADJACENT INDEX CLOCKWISE
int adjacent_cw(int i) {
  int r;
  if (i < LED_COUNT - 1) {
    r = i + 1;
  }
  else {
    r = 0;
  }
  return r;
}

//---FIND ADJACENT INDEX COUNTER-CLOCKWISE
int adjacent_ccw(int i) {
  int r;
  if (i > 0) {
    r = i - 1;
  }
  else {
    r = LED_COUNT - 1;
  }
  return r;
}


void one_color_all(int cred, int cgrn, int cblu) {       //-SET ALL LEDS TO ONE COLOR
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds0[i].setRGB( cred, cgrn, cblu);
    leds1[i].setRGB( cred, cgrn, cblu);
    leds2[i].setRGB( cred, cgrn, cblu);
    leds3[i].setRGB( cred, cgrn, cblu);
    leds4[i].setRGB( cred, cgrn, cblu);
    leds5[i].setRGB( cred, cgrn, cblu);
    leds6[i].setRGB( cred, cgrn, cblu);

  }
}

