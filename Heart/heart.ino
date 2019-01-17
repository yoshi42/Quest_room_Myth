//Code for heart beating
#include <SoftwareSerial.h>
#include "FastLED.h"          // библиотека для работы с лентой

#define LED_COUNT 23          // число светодиодов в кольце/ленте

#define LED_DT0 7             // пин, куда подключен DIN ленты
#define LED_DT1 8        

int max_bright = 255;         // максимальная яркость (0 - 25)

// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
struct CRGB leds0[LED_COUNT];
struct CRGB leds1[LED_COUNT];

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



int zamok1 = 15;          // замок дверцы
int zamok2 = 14;          // замок дневнека
int light = 13;           // свет вокруг отверстия
int p_led = 0;            //флаг подсветки отверстия

int s1 = 16;
int s2 = 17;
int s3 = 18;
int s4 = 19;

int sens = 12;

int p_sens = 0;
int start = 0;
int brightness = 10;
int delay_lock = 1500;

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
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
}



void loop() {
  digitalWrite(SSerialTxControl, LOW);
  if (RS485Serial.available()) {
      string = "";
    delay(100);
    tx();
  }

 color_bounceFADE();
}


void tx() {                          // розпізнання команди
  digitalWrite(SSerialTxControl, LOW);
  while (RS485Serial.available())
  {
    char inChar = RS485Serial.read();
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
        digitalWrite(zamok2, HIGH);
        digitalWrite(zamok1, HIGH);
        delay(delay_lock);
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
    delay(delay_lock);
    digitalWrite(zamok1, LOW);
  }
}

void message_1() {    
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду              
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  thisdelay = delay1;
  start = 1;
  brightness = 5;
  digitalWrite(light, LOW);
  color_bounceFADE();

}
void message_2() {
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, LOW);
  thisdelay = delay2;
  start = 1;
  brightness = 7;
  digitalWrite(light, LOW);
  color_bounceFADE();

}
void message_3() {
  one_color_red();
  LEDS.show();                     // отослать команду
  digitalWrite(light, HIGH);
  digitalWrite(zamok1, HIGH);
  delay(delay_lock);
  digitalWrite(zamok1, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, HIGH);
  thisdelay = delay3;
  p_sens = 1;
  start = 1;
  brightness = 9;
  p_led = 1;
  color_bounceFADE();

}


void message_dead() {
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
  digitalWrite(light, LOW);
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
      RS485Serial.println(stringitem);
      digitalWrite(zamok2, HIGH);
      delay(delay_lock);
      digitalWrite(zamok2, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      digitalWrite(s4, LOW);
      one_color_all(0, 0, 0);          // погасить все светодиоды
      LEDS.show();                     // отослать команду
      digitalWrite(light, LOW);
      delay(15000);
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
    int iL5 = adjacent_cw(iL4);
    int iR1 = adjacent_ccw(idex);
    int iR2 = adjacent_ccw(iR1);
    int iR3 = adjacent_ccw(iR2);
    int iR4 = adjacent_ccw(iR3);
    int iR5 = adjacent_ccw(iR4);
    for (int i = 0; i < LED_COUNT; i++ ) {
      if (RS485Serial.available()) {
        string = "";
        delay(100);
        tx();
      }
      if (i == idex) {
        leds0[i] = CHSV(thishue, thissat, 25*brightness);
      }
      else if (i == iL1) {
        leds0[i] = CHSV(thishue, thissat, 20*brightness);
      }
      else if (i == iL2) {
        leds0[i] = CHSV(thishue, thissat, 16*brightness);
      }
      else if (i == iL3) {
        leds0[i] = CHSV(thishue, thissat, 12*brightness);
      }
      else if (i == iL4) {
        leds0[i] = CHSV(thishue, thissat, 7*brightness);
      }
      else if (i == iL5) {
        leds0[i] = CHSV(thishue, thissat, 2*brightness);
      }
      else if (i == iR1) {
        leds0[i] = CHSV(thishue, thissat, 20*brightness);
      }
      else if (i == iR2) {
        leds0[i] = CHSV(thishue, thissat, 16*brightness);
      }
      else if (i == iR3) {
        leds0[i] = CHSV(thishue, thissat, 12*brightness);
      }
      else if (i == iR4) {
        leds0[i] = CHSV(thishue, thissat, 7*brightness);
      }
      else if (i == iR5) {
        leds0[i] = CHSV(thishue, thissat, 2*brightness);
      }
      else {
        leds0[i] = CHSV(0, 0, 0);
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
  }
}
void one_color_red(){
  for (int i = 7 ; i < 12; i++ ) {
    leds1[i].setRGB( 255, 0, 0);
  }
}

