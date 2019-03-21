#include <SoftwareSerial.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        2  //Serial Transmit pin
#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int dirOutPin = 5;
int stepOutPin = 6;
int enPin = 13;
int MHSens = 9;              //концевик
int a=0;                    //счетчик

String string0 = "Master_Photos2_change#";
String string1 = "Master_Photos2_back#";
String string;



SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
    pinMode(MHSens, INPUT);
    pinMode(dirOutPin, OUTPUT);
    pinMode(stepOutPin, OUTPUT);
    pinMode(enPin, OUTPUT);
    digitalWrite(enPin, LOW);
   
}


void loop() {
digitalWrite(SSerialTxControl, LOW);
 if (RS485Serial.available()) {
   string = "";
  delay(100);
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
        change();
      }
      if (string.equals(string1))
      {
        a=0;
        back();
      }
    string = "";
    }
}
loop();
}

void change() {

  //digitalWrite(enPin, HIGH);
  while (digitalRead(MHSens)==HIGH )
      {
       
     digitalWrite(dirOutPin, LOW);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(1600);

      digitalWrite(stepOutPin, HIGH);
      }
      //digitalWrite(enPin, LOW);
}

void back() {
  //digitalWrite(enPin, HIGH);
      while(a<4000 ){
        a++;
       digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(1600);

      digitalWrite(stepOutPin, HIGH);
      }
  //digitalWrite(enPin, LOW);
}

