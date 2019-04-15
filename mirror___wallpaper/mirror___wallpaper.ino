/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com

 "

on 10EFA05F
delay 5s
-> 10EFC23D
-> 10EFC23D
ok 10EF42BD
ok 10EF42BD
-> 10EFC23D
play 10EFCC33

Off 10EFA05F
 */

#include <IRremote.h>
#include <SoftwareSerial.h>

#define SSerialRX        16  //4 Serial Receive pin
#define SSerialTX        17  //5 Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define anal_comm_a6 4
#define anal_comm_a7 5


int led1ru =12;        //підсвітка тексту 
int led2ru =11;
int led3ru =10;

int led1en =6;
int led2en =8;
int led3en =7;

int led1heb =9;
int led2heb =14;
int led3heb =15;

int lightTV =13;

String string0 = "Master_mirror_ru#";
String string1 = "Master_mirror_en#";
String string2 = "Master_mirror_heb#";
String string;
unsigned long time0 = 0;

int flag_ru = 0;
int flag_en = 0;
int flag_heb = 0;

IRsend irsend;
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT); 
  digitalWrite(SSerialTxControl, LOW); // переводим устройство в режим приёмника
  RS485Serial.begin(9600); 
 // pinMode(irsend, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(led1ru, OUTPUT);
  pinMode(led2ru, OUTPUT);
  pinMode(led3ru, OUTPUT);
  pinMode(led1en, OUTPUT);
  pinMode(led2en, OUTPUT);
  pinMode(led3en, OUTPUT);
  pinMode(led1heb, OUTPUT);
  pinMode(led2heb, OUTPUT);
  pinMode(led3heb, OUTPUT);
  pinMode(lightTV, OUTPUT);
  digitalWrite(lightTV, LOW); 
 
  pinMode(anal_comm_a6, INPUT_PULLUP);
  pinMode(anal_comm_a7, INPUT_PULLUP);
  delay(1000);
  //Проверка
  //digitalWrite(lightTV, HIGH);
  //ru();
}

void(* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0
 
void loop() 
{
  digitalWrite(SSerialTxControl, LOW);
 
 if (Serial.available()) {
  string = "";
  delay(100);
  tx();
 }
 if (digitalRead(anal_comm_a6) == LOW && digitalRead(anal_comm_a7) == HIGH)
 {
    delay(200);
    flag_ru = 1;
 }
 if(flag_ru==1)
 {
    delay(200);
    ru();
    flag_ru = 2;
 }
 if (digitalRead(anal_comm_a6) == HIGH && digitalRead(anal_comm_a7) == LOW)
 {
    delay(200);
    flag_en = 1;
 }
 if(flag_en==1)
 {
    delay(50);
    en();
    flag_en = 2;
 }
 if (digitalRead(anal_comm_a6) == LOW && digitalRead(anal_comm_a7) == LOW)
 {
    delay(50);
    flag_heb = 1;
 }
 if(flag_heb==1)
 {
    delay(50);
    heb();
    flag_heb = 2;
 }
if(digitalRead(anal_comm_a6) == HIGH && digitalRead(anal_comm_a7) == HIGH){
  delay(50);
   flag_ru = 0;
   flag_en = 0;
   flag_heb = 0;
 }

}

void tx() {              //розпізнання команд
  digitalWrite(SSerialTxControl, LOW);
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(string0))
      {  
        digitalWrite(lightTV, HIGH);        
        ru();
      }
      if (string.equals(string1))
      {
        digitalWrite(lightTV, HIGH);
        en();
      }
      if (string.equals(string2))
      {
        digitalWrite(lightTV, HIGH);
        heb();
      }
    string = "";
    }

}
loop();
}

void ru() {
digitalWrite(lightTV, LOW);
  irsend.sendNEC(0x10EFA05F, 32); //on
    delay(13000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1500);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1500);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EFCC33, 32); // play
    delay(3000);
    irsend.sendNEC(0x10EFCC33, 32); // pause
  delay(20000);
 digitalWrite(led1ru, HIGH);
  delay(10500); 
 digitalWrite(led2ru, HIGH);
  delay(9500); 
 digitalWrite(led3ru, HIGH);
  delay(4000); 
 digitalWrite(led1ru, LOW);
digitalWrite(led2ru, LOW);
digitalWrite(led3ru, LOW);

irsend.sendNEC(0x10EFCC33, 32); // play
time0=millis();
delay(5000);
digitalWrite(lightTV, HIGH);
off();
}

void en() {
  digitalWrite(lightTV, LOW);
    irsend.sendNEC(0x10EFA05F, 32); //on
    delay(13000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1500);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1500);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EFCC33, 32); // play
    delay(3000);
    irsend.sendNEC(0x10EFCC33, 32); // pause
   delay(16000);
 digitalWrite(led2en, HIGH);
  delay(13000); 
 digitalWrite(led1en, HIGH);
  delay(9500); 
 digitalWrite(led3en, HIGH);
  delay(4000); 
 digitalWrite(led1en, LOW);
digitalWrite(led2en, LOW);
digitalWrite(led3en, LOW);
irsend.sendNEC(0x10EFCC33, 32); // play
time0=millis();
delay(5000);

digitalWrite(lightTV, HIGH);
off();
}
void heb() {
  digitalWrite(lightTV, LOW);
       irsend.sendNEC(0x10EFA05F, 32); //on
    delay(13000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1500);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1500);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1500);
    irsend.sendNEC(0x10EFCC33, 32); // play
    delay(3000);
    irsend.sendNEC(0x10EFCC33, 32); // pause
   delay(20000);
 digitalWrite(led3heb, HIGH);
  delay(10500); 
 digitalWrite(led1heb, HIGH);
  delay(9500); 
 digitalWrite(led2heb, HIGH);
  delay(4000); 
 digitalWrite(led1heb, LOW);
digitalWrite(led2heb, LOW);
digitalWrite(led3heb, LOW);
irsend.sendNEC(0x10EFCC33, 32); // play
time0=millis();
delay(5000);

digitalWrite(lightTV, HIGH);
off();
}

void off()    // виключити ТВ
{  flag_ru = 0;
   flag_en = 0;
   flag_heb = 0; 
  while(millis()-time0<80050){
    if(millis()-time0>80000){
    digitalWrite(lightTV, LOW);
    irsend.sendNEC(0x10EFA05F, 32); //off
    resetFunc();
    break;
    }
  }
}