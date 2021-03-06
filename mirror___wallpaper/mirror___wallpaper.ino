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

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        5  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

//int irsend = 3;
int led1ru =12;        //підсвітка тексту 
int led2ru =11;
int led3ru =10;
int led1en =9;
int led2en =8;
int led3en =7;
int led1heb =6;
int led2heb =14;
int led3heb =15;

int lightTV =20;

String string0 = "Master_mirror_ru#";
String string1 = "Master_mirror_en#";
String string2 = "Master_mirror_heb#";
String string;

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
    
}

void irblink() //перша команда
{
    irsend.sendNEC(0x10EFA05F, 32); //on
    delay(8000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1000);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1000);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    //delay(1000);
    //irsend.sendNEC(0x10EFCC33, 32); // play
    //RS485Serial.write('s'); 
}
 
void loop() 
{
  
  digitalWrite(SSerialTxControl, LOW);
  digitalWrite(13,LOW);
 if (RS485Serial.available()) {
   digitalWrite(13,HIGH);
   delay(500);
  tx();
 }
}

void tx() {              //розпізнання команд
  digitalWrite(SSerialTxControl, LOW);
  while (RS485Serial.available())
  {
    char inChar = RS485Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(string0))
      {          
      ru();
      }
      if (string.equals(string1))
      {
       // en();
      }
      if (string.equals(string2))
      {
        
       // heb();
      }
    string = "";
    }

}
loop();
}


void ru() {
  irsend.sendNEC(0x10EFA05F, 32); //on
    delay(8000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
    delay(1000);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1000);
    irsend.sendNEC(0x10EF42BD, 32); // ok
    delay(1000);
    irsend.sendNEC(0x10EFC23D, 32); // ->
  delay(10000);
 digitalWrite(led1ru, HIGH);
  delay(10000); 
 digitalWrite(led2ru, HIGH);
  delay(10000); 
 digitalWrite(led3ru, HIGH);
  delay(10000); 
 digitalWrite(led1ru, LOW);
digitalWrite(led2ru, LOW);
digitalWrite(led3ru, LOW);
irsend.sendNEC(0x10EFCC33, 32); // play
loop();
}
void en() {
   delay(10000);
 digitalWrite(led1en, HIGH);
  delay(10000); 
 digitalWrite(led2en, HIGH);
  delay(10000); 
 digitalWrite(led3en, HIGH);
  delay(10000); 
 digitalWrite(led1en, LOW);
digitalWrite(led2en, LOW);
digitalWrite(led3en, LOW);
loop();
}
void heb() {
   delay(10000);
 digitalWrite(led1heb, HIGH);
  delay(10000); 
 digitalWrite(led2heb, HIGH);
  delay(10000); 
 digitalWrite(led3heb, HIGH);
  delay(10000); 
 digitalWrite(led1heb, LOW);
digitalWrite(led2heb, LOW);
digitalWrite(led3heb, LOW);
loop();
}

void off()    // виключити ТВ
{
    irsend.sendNEC(0x10EFA05F, 32); 
    loop();
}


