#include <DFPlayer_Mini_Mp3.h>

#include <SoftwareSerial.h>

#define SSerialRX        7  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
int dirOutPin = 12;
int stepOutPin = 8;

int mosfet = 9;             //мосфет
int MHSens = 10;              //концевик
int led = 13;                 //подсветка
int text;
String string0 = "Master_hands1_on#";

String string;
int thisdelay = 400;        //скорость рук
int p = 0;                  //флаг плеера
int a =0;
int b = 0;
unsigned long time0 = 0;
SoftwareSerial mySerial(5, 4);                    // MP3 плеер
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);                     // скорость софт Сериал
  mp3_set_serial (mySerial);                //   софтовый серийный порт для мп3
  delay (100);                              //  обязательная задержка между командами
  mp3_set_volume (30);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, LOW);
  
  RS485Serial.begin(9600); 
  pinMode(dirOutPin, OUTPUT);
  pinMode(led, OUTPUT);
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

      delayMicroseconds(thisdelay);

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

      delayMicroseconds(100);

      digitalWrite(stepOutPin, HIGH);

      }

      
      }
      }
}

void loop() {
  if(p=1){
   mp3_stop ();
    p=0;
  }
  
digitalWrite(led, LOW);
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
      a=0;
      b=0;
      mp3_play (1);
      p=1;
      digitalWrite(led, HIGH);
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

      delayMicroseconds(thisdelay);

      digitalWrite(stepOutPin, HIGH);

      //delayMicroseconds(100); 
}
}

void down() {
  while(b<10000) {
  b++;
      digitalWrite(dirOutPin, LOW);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(thisdelay);

      digitalWrite(stepOutPin, HIGH);

      //delayMicroseconds(100); 
}
}
