#include <SoftwareSerial.h>
#define SSerialRX       4  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 12   //RS485 Direction control
#define anal_comm 9 //analog_communication - коммуникация через жопу, т.к. RS485 не работает
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int Zamok=7;        //магнітний замок
int MHSens= 8;      //дарчик-кінцевик
int dirOutPin = 5;
int stepOutPin = 6;

int               a = 0;
int               p = 0;
int               c = 0;
String string0 = "Master_ShoeRack2_180deg#";
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
    pinMode(anal_comm, INPUT_PULLUP);
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
      digitalWrite(dirOutPin, LOW);

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
   string = "";
  delay(100);
  tx();
}
  if (digitalRead(anal_comm) == LOW)
 {  
  a=0;
  p=0;
  stepleft();
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

