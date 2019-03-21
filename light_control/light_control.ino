#include <SoftwareSerial.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        12  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int light_kor1 = 11;
int light_kor2 = 10;
int light_kor3 = 9;
int light_kor4 = 6;
int light_strob1 = 5;
int light_strob2 = 3;

int light_office = 15;

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
String string7 = "Master_Light_rele1#";         //дим машина
String string8 = "Master_Light_rele2#";
String string9 = "Master_Light_rele3#";
String string10 = "Master_Light_strob#";

String string;
unsigned long i = 0;
int delay_strob = 30;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX


void setup() {
    Serial.begin(9600);
    RS485Serial.begin(9600); 
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    pinMode(light_kor1, OUTPUT);
    pinMode(light_kor2, OUTPUT);
    pinMode(light_kor3, OUTPUT);
    pinMode(light_kor4, OUTPUT);
    pinMode(light_strob1, OUTPUT);
    pinMode(light_strob2, OUTPUT);
    pinMode(light_office, OUTPUT);
    pinMode(rele_1, OUTPUT);
    pinMode(rele_2, OUTPUT);
    pinMode(rele_3, OUTPUT);
    analogWrite(light_kor1, 255);
    analogWrite(light_kor2, 255);
    analogWrite(light_kor3, 255);
    analogWrite(light_kor4, 255);
    analogWrite(light_strob1, 0);
    analogWrite(light_strob2, 0);
    digitalWrite(light_office, HIGH);

    //message_strob();
}

void loop() {  

  digitalWrite(SSerialTxControl, LOW);
  if (RS485Serial.available()) {
    string = "";
    delay(100);
    tx();
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
      if (string.equals(string7))
      {
         message_rele1();
      }
      if (string.equals(string8))
      {
         message_rele2();
      }
      if (string.equals(string9))
      {
         message_rele3();
      }
      if (string.equals(string10))
      {
         message_strob();
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
  analogWrite(light_strob1, 0);
  analogWrite(light_strob2, 0);
  digitalWrite(light_office, LOW);
  digitalWrite(SSerialTxControl, HIGH);
  RS485Serial.println("ok_on");
  digitalWrite(SSerialTxControl, LOW);
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
  analogWrite(light_kor1, 255);
  analogWrite(light_kor2, 50);
}
void message_kor4(){
  analogWrite(light_kor3, 200);
  analogWrite(light_kor4, 200);
}
void message_office(){
  digitalWrite(light_office, LOW);
}
void message_rele1(){
  digitalWrite(rele_1, LOW);
  delay(500);
  digitalWrite(rele_1, HIGH);
}
void message_rele2(){
  digitalWrite(rele_2, LOW);
  delay(500);
  digitalWrite(rele_2, HIGH);
}
void message_rele3(){
  digitalWrite(rele_3, LOW);
  delay(500);
  digitalWrite(rele_3, HIGH);
}
void message_strob()
{
  analogWrite(light_kor1, 0);
  analogWrite(light_kor2, 0);
  delay(1000);
  for (int i=0; i<30; i++)
  {
    analogWrite(light_strob1, 255);
    delay(delay_strob);
    analogWrite(light_strob1, 0);
    delay(delay_strob);
  }

  delay(2000);

  for (int i=0; i<30; i++)
  {
    analogWrite(light_strob2, 255);
    delay(delay_strob);
    analogWrite(light_strob2, 0);
    delay(delay_strob);
  }
  delay(1000);
  analogWrite(light_kor1, 255);
  analogWrite(light_kor2, 255);
}

void message_off(){
  analogWrite(light_kor1, 0);
  analogWrite(light_kor2, 0);
  analogWrite(light_kor3, 0);
  analogWrite(light_kor4, 0);
  analogWrite(light_strob1, 0);
  analogWrite(light_strob2, 0);
  digitalWrite(light_office, HIGH);
  digitalWrite(SSerialTxControl, HIGH);
  RS485Serial.println("ok_off");
  digitalWrite(SSerialTxControl, LOW);
}