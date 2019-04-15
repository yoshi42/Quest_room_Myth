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

#define SSerialRX        13  //12 Serial Receive pin
#define SSerialTX        14  //11 Serial Transmit pin
#define SSerialTxControl 15   //2 RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

/*/ analog_communication: 
A2,A3 - INput
A4, A5 - output
on: a2=1; a3=0
next: a2=0;a3=1
off: a2=0;a3=0

good: a4=0
bad: a5=0
/*/
#define anal_comm_a2 12
#define anal_comm_a3 11
#define anal_comm_a4 2
#define anal_comm_a5 A5

//int irsend = 3;
int hollSens1= 4;            //датчик хола 
int hollSens2= 5;
int hollSens3= 8;
int hollSens4= 7;
int hollSens5= 6;
int hollSens6= 9;

int p=0;              //флаги
int p1=0;
int p2=0;
int p3=0;
int p4=0;
int p5=0;
int p6=0;

String string0 = "Master_Window2_on_vid1#";
String string1 = "Master_Window2_vid2#";
String string2 = "Master_Window2_vid3#";
String string3 = "Master_Window2_off#";
String string4 = "Master_Window2_pass#";

String stringbad = "Slave_Window2_bad#";
String stringgood = "Slave_Window2_good#";
String string;

IRsend irsend;
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
   // pinMode(irsend, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(hollSens1, INPUT_PULLUP);
    pinMode(hollSens2, INPUT_PULLUP);
    pinMode(hollSens3, INPUT_PULLUP);
    pinMode(hollSens4, INPUT_PULLUP);
    pinMode(hollSens5, INPUT_PULLUP);
    pinMode(hollSens6, INPUT_PULLUP);

    pinMode(anal_comm_a2, INPUT_PULLUP);
    pinMode(anal_comm_a3, INPUT_PULLUP); 

    pinMode(anal_comm_a4, OUTPUT); //good
    pinMode(anal_comm_a5, OUTPUT); //bad
    digitalWrite(anal_comm_a4, HIGH); 
    digitalWrite(anal_comm_a5, HIGH); 
}

void irblink()                               // перша команда
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
}
 
void loop() 
{ 
  if(p==1) {
  if (digitalRead(hollSens1) == LOW && p1==0){digitalWrite(SSerialTxControl, HIGH); RS485Serial.println(stringbad); digitalWrite(anal_comm_a5,LOW);delay(500);digitalWrite(anal_comm_a5,HIGH);digitalWrite(SSerialTxControl, LOW); p1=1;p4=0;p5=0;p6=0;}
  if (digitalRead(hollSens1) == HIGH) {p1=0;}
  if (digitalRead(hollSens2) == LOW && p2==0){digitalWrite(SSerialTxControl, HIGH); RS485Serial.println(stringbad);digitalWrite(anal_comm_a5,LOW);delay(500);digitalWrite(anal_comm_a5,HIGH);digitalWrite(SSerialTxControl, LOW); p2=1;p4=0;p5=0;p6=0;}
  if (digitalRead(hollSens2) == HIGH) {p2=0;}
  if (digitalRead(hollSens3) == LOW && p3==0){digitalWrite(SSerialTxControl, HIGH); RS485Serial.println(stringbad);digitalWrite(anal_comm_a5,LOW);delay(500);digitalWrite(anal_comm_a5,HIGH);digitalWrite(SSerialTxControl, LOW); p3=1;p4=0;p5=0;p6=0;}
  if (digitalRead(hollSens3) == HIGH) {p3=0;}
  
  if (digitalRead(hollSens4) == LOW) {p4=1;}
  if (digitalRead(hollSens5) == LOW) {p5=1;}
  if (digitalRead(hollSens6) == LOW) {p6=1;}
   
  if( p4==1 && p5==1 && p6==1) {digitalWrite(SSerialTxControl, HIGH); RS485Serial.println(stringgood);digitalWrite(anal_comm_a4,LOW);delay(200);digitalWrite(anal_comm_a4,HIGH);digitalWrite(SSerialTxControl, LOW); p=0;p4=0;p5=0;p6=0;}
  }
  
  digitalWrite(SSerialTxControl, LOW);
  
   if (RS485Serial.available()) {
    string = "";
    delay(100);
    tx();
 }

 if (digitalRead(anal_comm_a2) == HIGH && digitalRead(anal_comm_a3) == LOW)
 {
    delay(50);
    irblink();
    p=1;
 }
 if (digitalRead(anal_comm_a2) == LOW && digitalRead(anal_comm_a3) == HIGH)
 {
    delay(50);
    irblink2();
 }
 if (digitalRead(anal_comm_a2) == LOW && digitalRead(anal_comm_a3) == LOW)
 {
    delay(50);
    irblink1();
 }

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
      irblink();
      }
      if (string.equals(string1) || string.equals(string2))
      {
        irblink1();
      }
      if (string.equals(string3))
      {
        irblink2();
      }
      if (string.equals(string4))
      {
        p=1;
      }
      
    string = "";
    }

}
loop();
}


void irblink1() //команда далі
{
    irsend.sendNEC(0x807C02FD, 32); 
    loop();
}

void irblink2()   // команда виключення
{
    irsend.sendNEC(0x807C50AF, 32); 
    loop();
}
