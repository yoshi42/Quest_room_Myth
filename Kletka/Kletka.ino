#include <SoftwareSerial.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW


String string0 = "Master_Lampa_on#";
String string1 = "Master_Lampa_start#";
String string2 = "Master_Lampa_off#";
String string3 = "Master_Kletka_open#";
String string4 = "Master_Kletka_open2#";

String stringbad = "Slave_Lampa_bad#";
String stringgood = "Slave_Lampa_good#";
String string;


int SensR = 4;        // датчики холла
int SensG = 5;
int SensB = 6;
int SensY = 7;

int sens =500;

int p = 0;
int k = 0;
int s = 0;    //счетчик
int r = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;
int p6 = 0;

int Zamok = 8;  
int Zamok2 = 9;
int Potolok = 10;
int Vibr = 11;

int lightR = 5;      //світлло в клітці
int lightG = 6;
int lightB = 7;

int lampR = 14;            //світло лампи
int lampG = 15;
int lampB = 16;
unsigned long time0 = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
int del = 3000;
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
   // pinMode(irsend, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(SensR, INPUT_PULLUP);
    pinMode(SensG, INPUT_PULLUP);
    pinMode(SensB, INPUT_PULLUP);
    pinMode(SensY, INPUT_PULLUP);
    pinMode(Zamok, OUTPUT);
    pinMode(Zamok2, OUTPUT);
    pinMode(Potolok, OUTPUT);
    pinMode(Vibr, OUTPUT);
    pinMode(lightR, OUTPUT);
    pinMode(lightG, OUTPUT);
    pinMode(lightB, OUTPUT);
    pinMode(lampR, OUTPUT);
    pinMode(lampG, OUTPUT);
    pinMode(lampB, OUTPUT);
    
    digitalWrite(Zamok, HIGH);
    digitalWrite(Zamok2, HIGH);
    digitalWrite(Potolok, HIGH);
    digitalWrite(Vibr, HIGH);
    LightOff();

}


void loop() {
  digitalWrite(SSerialTxControl, LOW);
if(RS485Serial.available()){
  string = "";
  delay(100);
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
          LightW();
          digitalWrite(Zamok, LOW);
          delay(1000);
          digitalWrite(Zamok, HIGH);
      }
      if (string.equals(string1) )
      {
         LightOff();
         LampW();
         time0=millis();
         s=0;
         r=0;
         p=0;
         game();
         
      }
      if (string.equals(string2))
      {
          p=1; 
         game();
                
      }  
      
      if (string.equals(string3))
      {
          digitalWrite(Zamok, LOW);
          delay(1000);
          digitalWrite(Zamok, HIGH);       
      } 
      if (string.equals(string4))
      {
          digitalWrite(Zamok2, LOW);
          delay(1000);
          digitalWrite(Zamok2, HIGH);       
      }    
    string = "";
    }
}
loop();
}

void game() {               //основна ігра
  if(p==1){LightOff();
         LampOff();}
  while(p==0){
    digitalWrite(SSerialTxControl, LOW);
    digitalWrite(Zamok, HIGH);
    digitalWrite(Zamok2, HIGH);
    digitalWrite(Potolok, HIGH);
    digitalWrite(Vibr, HIGH);
    if(Serial.available()){
     tx(); 
    }

    if(millis()-time0<del){              //включення першого кольору
       LightG();
    }
    if(millis()-time0<2*del){             // перевірка на правильність повторення першого кольору
       if(r==0){
          if(analogRead(SensG)<sens && s==0) {
            s=1;
            
          }
            if((analogRead(SensR)<sens || analogRead(SensB)<sens || analogRead(SensY)<sens) && s<1) {
            redBlink();
            
          }
       }
    }
    if(millis()-time0<(2*del) && millis()-time0>del){         //включення другого кольору
       LightB();
    }
    if(millis()-time0<(3*del) && millis()-time0>del){         // перевірка на правильність повторення 2 кольору
       if(r==0){
          if(analogRead(SensB)<sens && s==1) {
            s=2;
            
          }
            if((analogRead(SensR)<sens && millis()-time0<2*del ) || (analogRead(SensG)<sens && s<1) || analogRead(SensY)<sens || (analogRead(SensB)<sens && s<1)) {
        
            redBlink();
            
          }
       }
    }
    if(millis()-time0<(3*del) && millis()-time0>(2*del)){      //включення 3 кольору
       LightR();
       }
    if(millis()-time0<(4*del) && millis()-time0>2*del){         // перевірка на правильність повторення 3 кольору
       if(r==0){
          if(analogRead(SensR)<sens && s==2) {
            s=3;
            
          }
            if((analogRead(SensB)<sens && s<2) || (analogRead(SensG)<sens && millis()-time0<3*del ) || analogRead(SensY)<sens || (analogRead(SensR)<sens && s<2))  {
            redBlink();
            
          }
       }       
    }
    if(millis()-time0<(4*del) && millis()-time0>(3*del)){      //включення 4 кольору
       LightG();
      }
    if(millis()-time0<(5*del) && millis()-time0>3*del){         // перевірка на правильність повторення 4 кольору 
       if(r==0){
          if(analogRead(SensG)<sens && s==3) {
            s=4;
            
          }
            if((analogRead(SensR)<sens&& s<3) || analogRead(SensB)<sens || (analogRead(SensY)<sens && millis()-time0<4*del ) || (analogRead(SensG)<sens && s<3))  {
            redBlink();
            
          } 
       }       
    }
    if(millis()-time0<(5*del) && millis()-time0>(4*del)){      //включення 5 кольору
       LightY();
      }
    if(millis()-time0<(6*del) && millis()-time0>4*del){         // перевірка на правильність повторення 5 кольору 
       if(r==0){
          if(analogRead(SensY)<sens && s==4) {
            s=5;
            
          }
            if(analogRead(SensR)<sens || (analogRead(SensG)<sens && s<4) || (analogRead(SensB)<sens && millis()-time0<5*del ) || (analogRead(SensY)<sens && s<4)) {
            redBlink();
            
          } 
       }       
    }
    if(millis()-time0<(6*del) && millis()-time0>(5*del)){      //включення 6 кольору
       LightB(); 
       }
    if(millis()-time0<(7*del) && millis()-time0>5*del){         // перевірка на правильність повторення 6 кольору
       if(r==0){
          if(analogRead(SensB)<sens && s==5) {
            p=1;
            time2=millis();
            openDoor();
            
          }
            if(analogRead(SensR)<sens || analogRead(SensG)<sens || (analogRead(SensY)<sens&& s<5) || (analogRead(SensB)<sens && s<5)) {
            redBlink();
            
          } 
       }       
    }
    if(millis()-time0>(6*del) && millis()-time0<(8*del)){
      LightOff(); 
    }
    if(millis()-time0>=(8*del)){
     time0=millis(); 
    }
    
    if(k==0){ LampW(); }
    if((analogRead(SensR)<sens || analogRead(SensG)<sens || analogRead(SensB)<sens || analogRead(SensY)<sens) && k==0) { k=1;}
    if(k==1){
      if(analogRead(SensR)<sens && r==0) {
        LampR();
      }
      if(analogRead(SensG)<sens && r==0) {
        LampG();
      }
      if(analogRead(SensB)<sens && r==0) {
        LampB();
      }
      if(analogRead(SensY)<sens && r==0) {
        LampY();
      }
      if(analogRead(SensR)>sens && analogRead(SensG)>sens && analogRead(SensB)>sens && analogRead(SensY)>sens) {
        LampOff();
        r=0;
      }
    }
    
  }
}


void openDoor() {                           //
  digitalWrite(SSerialTxControl, HIGH);
  RS485Serial.println(stringgood);
  while(millis()-time2<20000){
    LightW();
    LampOff();
    if(millis()-time2<1000 ) {
      digitalWrite(Potolok, LOW);
    }
    if(millis()-time2>6000 && millis()-time2<7000) {
      digitalWrite(Zamok, LOW);
      LampOff();
    }
     if(millis()-time2>15000)  {
      digitalWrite(Zamok, HIGH);
      LightOff();
    }
  }
  digitalWrite(SSerialTxControl, LOW);
}
void redBlink() {                       //неправильне виконання 
  digitalWrite(SSerialTxControl, HIGH);
  RS485Serial.println(stringbad);
  LampOff();
  time1=millis();
  time0=10*del;
  digitalWrite(Vibr, LOW);
  time3=millis();
  LightOff();
  while(millis()-time1<3000){
    if(millis()-time3<30){
    digitalWrite(lightR, HIGH);
    }
    if(millis()-time3>30 && millis()-time3<60){
    digitalWrite(lightR, LOW);
    }
    if(millis()-time3==60){
      time3=millis();
    }
       if(analogRead(SensR)<sens && r==0) {
        LampR();
      }
      if(analogRead(SensG)<sens && r==0) {
        LampG();
      }
      if(analogRead(SensB)<sens && r==0) {
        LampB();
      }
      if(analogRead(SensY)<sens && r==0) {
        LampY();
      }
      if(analogRead(SensR)>sens && analogRead(SensG)>sens && analogRead(SensB)>sens && analogRead(SensY)>sens) {
        LampOff();
      }
  }
    time0=millis();
    digitalWrite(Vibr, HIGH);
    r=1;
    s=0;
  digitalWrite(SSerialTxControl, LOW);
}

void LightW() {
  digitalWrite(lightR, HIGH);
  digitalWrite(lightG, HIGH);
  digitalWrite(lightB, HIGH);
}
void LightR() {
  digitalWrite(lightR, HIGH);
  digitalWrite(lightG, LOW);
  digitalWrite(lightB, LOW);
}
void LightG() {
  digitalWrite(lightR, LOW);
  digitalWrite(lightG, HIGH);
  digitalWrite(lightB, LOW);
}
void LightB() {
  digitalWrite(lightR, LOW);
  digitalWrite(lightG, LOW);
  digitalWrite(lightB, HIGH);
}
void LightY() {
  digitalWrite(lightR, HIGH);
  digitalWrite(lightG, LOW);
  digitalWrite(lightB, HIGH);
}
void LightOff() {
  digitalWrite(lightR, LOW);
  digitalWrite(lightG, LOW);
  digitalWrite(lightB, LOW);
}

void LampW() {
  digitalWrite(lampR, HIGH);
  digitalWrite(lampG, HIGH);
  digitalWrite(lampB, HIGH);
}
void LampR() {
  digitalWrite(lampR, HIGH);
  digitalWrite(lampG, LOW);
  digitalWrite(lampB, LOW);
}
void LampG() {
  digitalWrite(lampR, LOW);
  digitalWrite(lampG, HIGH);
  digitalWrite(lampB, LOW);
}
void LampB() {
  digitalWrite(lampR, LOW);
  digitalWrite(lampG, LOW);
  digitalWrite(lampB, HIGH);
}
void LampY() {
  digitalWrite(lampR, HIGH);
  digitalWrite(lampG, LOW);
  digitalWrite(lampB, HIGH);
}
void LampOff() {
  digitalWrite(lampR, LOW);
  digitalWrite(lampG, LOW);
  digitalWrite(lampB, LOW);
}
