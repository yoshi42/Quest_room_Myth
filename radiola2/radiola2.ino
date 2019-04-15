#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

/*/Аналоговая коммуникация - замена RS485, коммуникация через жопу
anal_comm_d48 INPUT_PULLUP
anal_comm_d50 INPUT_PULLUP

    a9 a10 a11
ru   1   0  -
en   0   1  -
heb  0   0  -

*/

#define anal_comm_d48 4
#define anal_comm_d50 2

int flag_ru = 0;
int flag_en = 0;
int flag_heb = 0;


int Svet = 5;

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

void setup() {
  Serial.begin(9600);
  mp3_set_serial (Serial);  //   софтовый серийный порт для мп3
  delay (100);                              //  обязательная задержка между командами
  mp3_set_volume (30);
  pinMode(Svet, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(anal_comm_d48, INPUT_PULLUP);                     
  pinMode(anal_comm_d50, INPUT_PULLUP);  

  delay(1000);
}



void loop() {
  
  
  if (digitalRead(anal_comm_d48) == HIGH && digitalRead(anal_comm_d50) == LOW && flag_ru == 0)
 {
    delay(200);
    flag_ru = 1;
 }
 if(flag_ru==1){
    mp3_play (1);
    p=1;
    time0=millis();
    flag_ru = 2;
 }
 if (digitalRead(anal_comm_d48) == LOW && digitalRead(anal_comm_d50) == HIGH && flag_en == 0)
 {
    delay(200);
    flag_en = 1;
 }
 if(flag_en==1){
    mp3_play (2); 
        p=1;
        time0=millis();
     flag_en = 2;
 }
 if (digitalRead(anal_comm_d48) == LOW && digitalRead(anal_comm_d50) == LOW && flag_heb == 0)
 {
    delay(200);
    flag_heb = 1;
 }
 if(flag_heb==1){
    mp3_play (3);
        p=1;
        time0=millis();
    flag_heb = 2;
 }
 if(digitalRead(anal_comm_d48) == HIGH && digitalRead(anal_comm_d50) == HIGH){
  delay(200);
   flag_ru = 0;
   flag_en = 0;
   flag_heb = 0;
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





