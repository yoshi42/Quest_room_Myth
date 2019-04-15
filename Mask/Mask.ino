#include <SoftwareSerial.h>
#include "Arduino.h"

//#define SSerialRX        10  // pin 10 Serial Receive pin
//#define SSerialTX        12  //pin 12 Serial Transmit pin
//#define SSerialTxControl 11   //pin 11 RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define D23_maski_Tx 10
#define D25_maski_Rx 12
#define D31_maski_Rx 11

unsigned long time0 = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
unsigned long time4 = 0;
unsigned long time5 = 0;
unsigned long time6 = 0;
unsigned long time7 = 0;


#define Sens7 A0         //фоторезистори
#define Sens6 A1
#define Sens5 A2
#define Sens4 A3
#define Sens3 A4           
#define Sens2 A5
#define Sens1 A6
#define Sens0 A7

int val = 200;


int led0=2;              //підсвітка очей
int led1=3; 
int led2=4; 
int led3=5; 
int led4=6; 
int led5=7; 
int led6=8; 
int led7=9; 

int p = 0;
int s=0;
int p0 = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;
int p6 = 0;
int p7 = 0;


String string0 = "Master_Maski_on#";

String string;

//SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    //pinMode(SSerialTxControl, OUTPUT); 
    //digitalWrite(SSerialTxControl, LOW); 
    Serial.begin(9600); 
    //RS485Serial.begin(9600); 
    pinMode(13, OUTPUT);
    pinMode(Sens0, INPUT);
    pinMode(Sens1, INPUT);
    pinMode(Sens2, INPUT);
    pinMode(Sens3, INPUT);
    pinMode(Sens4, INPUT);
    pinMode(Sens5, INPUT);
    pinMode(Sens6, INPUT);
    pinMode(Sens7, INPUT);
    
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);

    pinMode(D23_maski_Tx, INPUT_PULLUP);

    pinMode(D25_maski_Rx, OUTPUT);
    pinMode(D31_maski_Rx, OUTPUT);
    digitalWrite(D25_maski_Rx, HIGH);
    digitalWrite(D31_maski_Rx, HIGH);
}



/*/analog comm

d23: 0 = on
d25, 31: 0,1 = good  digitalWrite(D25_maski_Rx, LOW); digitalWrite(D31_maski_Rx, HIGH); delay (500); digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, HIGH);
d25, 31: 1,0 = bad   digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, LOW); delay (500); digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, HIGH);

*/
void loop() 
{ 
  /*
  Serial.print("m1 ");
  Serial.print(analogRead(Sens0));

  Serial.print("    m2 ");
  Serial.print(analogRead(Sens1));

  Serial.print("    m3 ");
  Serial.print(analogRead(Sens2));

  Serial.print("    m4 ");
  Serial.print(analogRead(Sens3));

  Serial.print("    m5 ");
  Serial.print(analogRead(Sens4));

  Serial.print("    m6 ");
  Serial.print(analogRead(Sens5));

  Serial.print("    m7 ");
  Serial.print(analogRead(Sens6));

  Serial.print("    m8 ");
  Serial.println(analogRead(Sens7));
  delay(300);*/

  if(digitalRead(D23_maski_Tx) == LOW) //запустить задание с масками
  {
    delay(50);
    p=1;
  }

 if(p==1) {
  
  if (analogRead(Sens0)< 150) {p0=1;digitalWrite(led0, LOW); time0 = millis();} else if (analogRead(Sens0) > 150) {p0=0; if(millis() - time0>1000){digitalWrite(led0, HIGH);}}
  if (analogRead(Sens1)< 120) {p1=1;analogWrite(led1, 0); time1 = millis();} else if (analogRead(Sens1) > 120) {p1=0; if(millis() - time1>1000){analogWrite(led1, 40);}}
  if (analogRead(Sens4)< 80) {p4=1;digitalWrite(led4, LOW); time4 = millis();} else if (analogRead(Sens4) > 80) {p4=0; if(millis() - time4>1000){digitalWrite(led4, HIGH);}}
  if (analogRead(Sens6)< 50) {p6=1;digitalWrite(led6, LOW); time6 = millis();} else if (analogRead(Sens6) > 50) {p6=0; if(millis() - time6>1000){digitalWrite(led6, HIGH);}}
  
  if (analogRead(Sens2)< 70) {p2=1;digitalWrite(led2, LOW); time2 = millis();} else if (analogRead(Sens2) > 70) {p2=0; if(millis() - time2>1000){digitalWrite(led2, HIGH);}}
  if (analogRead(Sens3)< 35) {p3=1;digitalWrite(led3, LOW); time3 = millis();} else if (analogRead(Sens3) > 35) {p3=0; if(millis() - time3>1000){digitalWrite(led3, HIGH);}}
  if (analogRead(Sens5)< 45) {p5=1;digitalWrite(led5, LOW); time5 = millis();} else if (analogRead(Sens5) > 45) {p5=0; if(millis() - time5>1000){digitalWrite(led5, HIGH);}}
  if (analogRead(Sens7)< 5) {p7=1;analogWrite(led7, 0); time7 = millis();} else if (analogRead(Sens7) > 5) {p7=0; if(millis() - time7>1000){analogWrite(led7, 40);}}
  
  s=p1+p2+p3+p4+p5+p6+p7+p0;
  if( s == 4) {
    if( p0==1 && p1==1 && p4==1 && p6==1){ lightOff(); 
      Serial.println("goood, very good");
      digitalWrite(D25_maski_Rx, LOW); digitalWrite(D31_maski_Rx, HIGH); delay (300); digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, HIGH);  //good
      delay(2000);
      s=0; p=0;}

    else{
      Serial.println("bad boy");
      digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, LOW); delay (300); digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, HIGH); //bad
     delay(1000); lightOff();  lightOn();  lightOff();  lightOn();  lightOff();  lightOn(); s=0;}
  }
  if(s>4) {
    Serial.println("bad boy");
      digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, LOW); delay (300); digitalWrite(D25_maski_Rx, HIGH); digitalWrite(D31_maski_Rx, HIGH);// bad
    delay(1000); lightOff(); lightOn();  lightOff();  lightOn(); lightOff();  lightOn(); s=0;}
  }
  
   if (Serial.available()) {
    string = "";
  delay(100);
  tx();

  /*if(digitalRead(D23_maski_Tx) == HIGH) //выключить маски
  {
    p=0;
  }*/

 }
}

void tx() {     // розпізнання команди
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#') 
    { 
      if (string.equals(string0))
      {
        p=1;
      }
      
    string = "";
    }

}
loop();
}

void lightOff() {
    digitalWrite(led0, LOW);
    analogWrite(led1, 0);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    analogWrite(led7, 0);
    delay(300);
}

void lightOn() {
    digitalWrite(led0, HIGH);
    analogWrite(led1, 40);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    analogWrite(led7, 40);
    delay(300);
}


