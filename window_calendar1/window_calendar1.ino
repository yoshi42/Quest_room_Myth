/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com

 "

on 807C50AF
delay 5s
-> 807C1AE5
-> 807C1AE5
ok 807C5AA5
ok 807C5AA5
-> 807C1AE5
-> 807C1AE5
ok 807C5AA5

>>| 807C02FD

Off 807C50AF
 */

#include <IRremote.h>
#include <SoftwareSerial.h>

#define SSerialRX        8  //Serial Receive pin
#define SSerialTX        7  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

//int irsend = 3;

String string0 = "Master_Window1_on_vid1#";
String string1 = "Master_Window1_vid2#";
String string2 = "Master_Window1_off#";
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
}

void irblink() //перша команда
{
    irsend.sendNEC(0x807C50AF, 32); //on
    delay(8000);
    irsend.sendNEC(0x807C1AE5, 32); // ->
    delay(1000);
    irsend.sendNEC(0x807C1AE5, 32); // ->
    delay(1000);
    irsend.sendNEC(0x807C5AA5, 32); // ok
    delay(1000);
    irsend.sendNEC(0x807C5AA5, 32); // ok
    delay(1000);
    irsend.sendNEC(0x807C1AE5, 32); // ->
    delay(1000);
    irsend.sendNEC(0x807C1AE5, 32); // ->
    delay(1000);
    irsend.sendNEC(0x807C5AA5, 32); // ok
    //RS485Serial.write('s'); 
}
 
void loop() 
{
  
  digitalWrite(SSerialTxControl, LOW);
  //digitalWrite(13,LOW);
 if (RS485Serial.available()) {
   //digitalWrite(13,HIGH);
   //delay(500);
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
      //digitalWrite(SSerialTxControl, HIGH);
      //RS485Serial.write('t');                  
      irblink();
      }
      if (string.equals(string1))
      {
        //digitalWrite(SSerialTxControl, HIGH);
        //RS485Serial.write('l');
        irblink1();
      }
      if (string.equals(string2))
      {
        //digitalWrite(SSerialTxControl, HIGH);
        //RS485Serial.write('r');
        irblink2();
      }
    string = "";
    }

}
loop();
}


void irblink1()    // команда далі
{
    irsend.sendNEC(0x807C02FD, 32); 
    loop();
}

void irblink2()   //команда викл
{
    irsend.sendNEC(0x807C50AF, 32); 
    loop();
}
