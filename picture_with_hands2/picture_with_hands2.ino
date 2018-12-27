#include <SoftwareSerial.h>
#define SSerialRX        7  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
int dirOutPin = 12;
int stepOutPin = 13;

int mosfet = 9;             //мосфет
int MHSens = 8;              //концевик
int text;
String string0 = "Master_hands2_on#";

String string;
int a =0;
int b = 0;
unsigned long time0 = 0;
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX


void setup() {
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, LOW);
  
  RS485Serial.begin(9600); 
  pinMode(dirOutPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(mosfet, OUTPUT);
  pinMode(MHSens, INPUT);
  pinMode(stepOutPin, OUTPUT);
}

void stepleft() {   //рухи руками

  while (a < 19000) 
      {
        if (a==0){
        digitalWrite(mosfet, HIGH);
        delay(1000);
        digitalWrite(mosfet, LOW);
        
        }
      a++;
      digitalWrite(dirOutPin, LOW);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(400);

      digitalWrite(stepOutPin, HIGH);

      //delayMicroseconds(90);
      
      time0 = millis();
      }
      if(a==19000 ){     
       while( millis()-time0 < 20000){
         up();
         b=0;
         down();
         b=0;
         
       }
       
      if(millis()-time0>20000){
      while (digitalRead(MHSens)==HIGH )
      {
      digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(400);

      digitalWrite(stepOutPin, HIGH);

     // delayMicroseconds(100);
      }
      }
      }
}

void loop() {
digitalWrite(13,LOW);
digitalWrite(SSerialTxControl, LOW);

 if (RS485Serial.available()) {
   digitalWrite(13,HIGH);
   delay(500);
  tx();
 }
}

void tx() {   // розпізнання команд
  digitalWrite(SSerialTxControl, LOW);
  while (RS485Serial.available())
  {
    char inChar = RS485Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(string0))
      {
      a=0;
      b=0;
      stepleft();
      }
    string = "";
    }
}
loop();
}

void up() {
  while(b<10000) {
  b++;
      digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(400);

      digitalWrite(stepOutPin, HIGH);

      //delayMicroseconds(100); 
}
}

void down() {
  while(b<9500) {
  b++;
      digitalWrite(dirOutPin, LOW);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(400);

      digitalWrite(stepOutPin, HIGH);

      //delayMicroseconds(100); 
}
}





