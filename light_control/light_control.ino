#include <SoftwareSerial.h>

#define SSerialRX        13  //Serial Receive pin
#define SSerialTX        12  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int light_kor1 = 11;  
int light_kor2 = 10;
int light_kor3 = 9;
int light_kor4 = 6;
int light_kor5 = 5;
int light_kor6 = 3;

int light_office = 4;

int rele_1 = 14;        //запасные реле
int rele_2 = 8;
int rele_3 = 7;

String string0 = "Master_Light_on#";
String string1 = "Master_Light_kor1#";
String string2 = "Master_Light_kor2#";
String string3 = "Master_Light_kor3#";
String string4 = "Master_Light_kor4#";
String string5 = "Master_Light_office#";
String string6 = "Master_Light_off#";

String string;
unsigned long i = 0;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX


void setup() {
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
    pinMode(light_kor1, OUTPUT);
    pinMode(light_kor2, OUTPUT);
    pinMode(light_kor3, OUTPUT);
    pinMode(light_kor4, OUTPUT);
    pinMode(light_kor5, OUTPUT);
    pinMode(light_kor6, OUTPUT);
    pinMode(light_office, OUTPUT);
    pinMode(rele_1, OUTPUT);
    pinMode(rele_2, OUTPUT);
    pinMode(rele_3, OUTPUT);
    analogWrite(light_kor1, 0);
    analogWrite(light_kor2, 0);
    analogWrite(light_kor3, 0);
    analogWrite(light_kor4, 0);
    analogWrite(light_kor5, 0);
    analogWrite(light_kor6, 0);
    digitalWrite(light_office, HIGH);
}

void loop() {  
  digitalWrite(SSerialTxControl, LOW);
  if (Serial.available()) {
    string = "";
    delay(100);
    tx();
 }
 
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
        message_kor1();
      }
      if (string.equals(string2))
      {
         message_kor2();
      }
      if (string.equals(string3))
      {
        message_kor3();
      }
      if (string.equals(string4) )
      {
        message_kor4();
      }
      if (string.equals(string5))
      {
         message_office();
      }
      if (string.equals(string6))
      {
         message_off();
      }
      
    string = "";
    }

  }

}


void message_on(){
  analogWrite(light_kor1, 255);
  analogWrite(light_kor2, 255);
  analogWrite(light_kor3, 255);
  analogWrite(light_kor4, 255);
  analogWrite(light_kor5, 255);
  analogWrite(light_kor6, 255);
  digitalWrite(light_office, LOW);
}

void message_kor1(){
  analogWrite(light_kor1, 50);
  analogWrite(light_kor2, 150);
}
void message_kor2(){
  analogWrite(light_kor3, 150);
  analogWrite(light_kor4, 150);
}
void message_kor3(){
  analogWrite(light_kor5, 150);
}
void message_kor4(){
  analogWrite(light_kor6, 150);
}
void message_office(){
  digitalWrite(light_office, LOW);
}
void message_off(){
  analogWrite(light_kor1, 0);
  analogWrite(light_kor2, 0);
  analogWrite(light_kor3, 0);
  analogWrite(light_kor4, 0);
  analogWrite(light_kor5, 0);
  analogWrite(light_kor6, 0);
  digitalWrite(light_office, HIGH);
}




