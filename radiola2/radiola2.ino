#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        2  //Serial Transmit pin
#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int dir = 6;
int stp = 7;
int Svet = 5;
int enable = 8;

int brightness = 6;    // how bright the LED is
int fadeAmount = 50;    // how many points to fade the LED by


String string0 = "Master_Radio2_on_ru#";
String string1 = "Master_Radio2_on_en#";
String string2 = "Master_Radio2_on_heb#";
String string;
int a = 0;
int b = 0;
int p = 0;

unsigned long time0 = 0;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup() {
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, LOW);
  RS485Serial.begin(9600);
  mp3_set_serial (Serial);  //   софтовый серийный порт для мп3
  delay (100);                              //  обязательная задержка между командами
  mp3_set_volume (30);
  pinMode(dir, OUTPUT);
  pinMode(stp, OUTPUT);
  pinMode(Svet, OUTPUT);
  digitalWrite(enable, LOW);
  pinMode(13, OUTPUT);

}

void state1(int s)
{
  if(s==1){
  mp3_play (1);                            // Произрываем "mp3/0001.mp3"
  }
   if(s==2){
  mp3_play (2);                            // Произрываем "mp3/0001.mp3"
  }
   if(s==3){
  mp3_play (3);                            // Произрываем "mp3/0001.mp3"
  }
 loop();

}

void loop() {
  if (RS485Serial.available()) {
     tx();
  }
  
  
  
  if(p==1 && millis() - time0<60000){
  analogWrite(Svet, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 50 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(100); 
  }
  if(p==0 ||  millis() - time0>60000){
   digitalWrite(Svet, LOW);
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
        state1(1);
        p=1;
        time0=millis();
      }
      if (string.equals(string1))
      {
        state1(2);
        p=1;
        time0=millis();
      }
      if (string.equals(string2))
      {
        state1(3);
        p=1;
        time0=millis();
      }

      string = "";
    }

  }
  loop();
}




