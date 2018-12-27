#include <SoftwareSerial.h>
#define SSerialRX        8  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int Zamok=7;        //магнітний замок
int MHSens= 6;      //дарчик-кінцевик
int dirOutPin = 5;
int stepOutPin = 4;

int               a = 0;
int               p = 0;
int               c = 0;
String string0 = "Master_ShoeRack1_180deg#";
String string;


SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup() 
{ 
  pinMode(Zamok,OUTPUT);                     //   настраиваем порт на выход замка
  digitalWrite(Zamok,HIGH);

  pinMode(MHSens,INPUT);                 //   настраиваем порт на вход   для датчика
  Serial.begin(9600);                        // открываем последовательный порт на скорости 9600 бод
   pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
   
    pinMode(13, OUTPUT);
    pinMode(dirOutPin, OUTPUT);
    pinMode(stepOutPin, OUTPUT);
}

void stepleft() {   //рухи руками
if(a=0){
  digitalWrite(Zamok,LOW);
  delay(300);
} 

      while (digitalRead(MHSens)==HIGH || p<500)
      {
        p++;
        digitalWrite(Zamok,LOW);
      digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, HIGH);

      delayMicroseconds(1000);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(1000);
      
      }
   
}

void loop() {
digitalWrite(13,LOW);
digitalWrite(SSerialTxControl, LOW);
digitalWrite(Zamok,HIGH);
 if (RS485Serial.available()) {
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
      p=0;
      stepleft();
      }
    string = "";
    }
}
loop();
}

