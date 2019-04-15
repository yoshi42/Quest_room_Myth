#include <SoftwareSerial.h>

#define SSerialRX        15  //pin4Serial Receive pin
#define SSerialTX        2  //Serial Transmit pin
#define SSerialTxControl 14   //pin3 RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define anal_comm_D3 3
#define anal_comm_D4 4

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

    pinMode(anal_comm_D3, INPUT_PULLUP);
    pinMode(anal_comm_D4, INPUT_PULLUP);
}

void(* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0

void loop() {
digitalWrite(SSerialTxControl, LOW);
 if (RS485Serial.available()) {
   string = "";
  delay(100);
  tx();
 }

if (digitalRead(anal_comm_D4) == HIGH && digitalRead(anal_comm_D3) == LOW)
 {  
    delay(50);
    change();
    delay(1000);
    resetFunc();
 }

 if (digitalRead(anal_comm_D4) == LOW && digitalRead(anal_comm_D3) == HIGH)
 {  
    delay(50);
    back();
    delay(1000);
    resetFunc();
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
  if (digitalRead(MHSens)== LOW)
  {
    while(a<4000 )
    {
      a++;
      digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(1600);

      digitalWrite(stepOutPin, HIGH);
    }
  }
  //digitalWrite(enPin, LOW);
}

