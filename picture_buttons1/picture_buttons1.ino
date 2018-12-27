#include <SoftwareSerial.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

//int irsend = 3;
int MHSens1= 7;            //інфра червоний датчик  
int MHSens2= 8;
int MHSens3= 9;
int MHSens4= 10;
int MHSens5= 11;
int MHSens6= 12;

int led1 = 14;        //підсвітка
int led2 = 15;
int led3 = 16;
int led4 = 17;
int led5 = 18;

int dirOutPin = 5;
int stepOutPin = 6;

int light = 0;
int a = 0;
int p=0;              //флаги
int p1=0;
int p2=0;
int p3=0;
int p4=0;
int p5=0;
int p6=0;

String string0 = "Master_Photos1_on#";
String string1 = "Master_Photos1_change#";
String string2 = "Master_Photos1_back#";

String stringbad = "Slave_Photos1_badParole";
String stringgood = "Slave_Photos1_goodParole";
String string;


SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
   // pinMode(irsend, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(dirOutPin, OUTPUT);
    pinMode(stepOutPin, OUTPUT);
    pinMode(MHSens1, INPUT);
    pinMode(MHSens2, INPUT);
    pinMode(MHSens3, INPUT);
    pinMode(MHSens4, INPUT);
    pinMode(MHSens5, INPUT);
    pinMode(MHSens6, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
}


 
void loop() 
{ 
  if (light==1) {
  digitalWrite(led1, HIGH);
  }else if (light==0) {
  digitalWrite(led1, LOW);
  }
  
 if (p==1) {
  if (digitalRead(MHSens1) == LOW && p1==0 && p2==0 && p3==0 && p4==0 && p5==0) {
    while(digitalRead(MHSens1) == LOW){
      digitalWrite(led1, LOW);
     p1=1;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(1);
  }else if (digitalRead(MHSens1) == LOW && (p2==1 || p1==1 || p3==1 || p4==1 || p5==1)){
    while(digitalRead(MHSens1) == LOW){
     p1=0;p2=0;p3=0;p4=0;p5=0;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
  }
  
  if (digitalRead(MHSens2) == LOW && p1==1 && p2==0 && p3==0 && p4==0 && p5==0) {
     while(digitalRead(MHSens2) == LOW){
       digitalWrite(led1, LOW);
     p2=1;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(2);
   }else if (digitalRead(MHSens2) == LOW && (p1==0 || p2==1 || p3==1 || p4==1 || p5==1)){
    while(digitalRead(MHSens2) == LOW){
     p1=0;p2=0;p3=0;p4=0;p5=0;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
  }
  
   if (digitalRead(MHSens3) == LOW && p1==1 && p2==1 && p3==0 && p4==0 && p5==0) {
     while(digitalRead(MHSens3) == LOW){
       digitalWrite(led1, LOW);
     p3=1;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(3);
     }else if (digitalRead(MHSens3) == LOW && (p1==0 || p2==0 || p3==1 || p4==1 || p5==1)){
    while(digitalRead(MHSens3) == LOW){
     p1=0;p2=0;p3=0;p4=0;p5=0;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
  }
  
  if (digitalRead(MHSens4) == LOW && p1==1 && p2==1 && p3==1 && p4==0 && p5==0) {
     while(digitalRead(MHSens4) == LOW){
       digitalWrite(led1, LOW);
     p4=1;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(4);
     }else if (digitalRead(MHSens4) == LOW && (p1==0 || p2==0 || p3==0 || p4==1 || p5==1)){
    while(digitalRead(MHSens4) == LOW){
     p1=0;p2=0;p3=0;p4=0;p5=0;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
  }
  
   if (digitalRead(MHSens5) == LOW && p1==1 && p2==1 && p3==1 && p4==1 && p5==0) {
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringgood);
     p=0; light=0;
     }else if (digitalRead(MHSens5) == LOW && (p1==0 || p2==0 || p3==0 || p4==0 || p5==1)){
    while(digitalRead(MHSens5) == LOW){
     p1=0;p2=0;p3=0;p4=0;p5=0;
     }
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
  }
}
  
  digitalWrite(SSerialTxControl, LOW);
  digitalWrite(13,LOW);
   if (RS485Serial.available()) {
     digitalWrite(13,HIGH);
     delay(500);
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
         p=1;
         light=1;
      }
      if (string.equals(string1) )
      {
         stepDown();
      }
      if (string.equals(string2))
      {
         p=0;
         light=0;
         stepUp();
         
      }
      
    string = "";
    }

}
loop();
}

void stepDown() {   //зміна фоток
  while (a < 3200) 
      {
      a++;
      digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, HIGH);

      delayMicroseconds(500);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(500);
      }
}
void stepUp() {   //повернення фото в стартову позицію
  while (digitalRead(MHSens6)==HIGH )
      {
      digitalWrite(dirOutPin, LOW);

      digitalWrite(stepOutPin, HIGH);

      delayMicroseconds(500);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(500);
      }
      //else{loop();}
}



