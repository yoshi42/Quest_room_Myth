#include <SoftwareSerial.h>

#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        12  //Serial Transmit pin
#define SSerialTxControl 11   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

unsigned long time0 = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
unsigned long time4 = 0;
unsigned long time5 = 0;
unsigned long time6 = 0;
unsigned long time7 = 0;


int Sens7= 0;          //фоторезистори
int Sens6= 1;
int Sens5= 2;
int Sens4= 3;
int Sens3= 4;            
int Sens2= 5;
int Sens1= 6;
int Sens0= 7;

int val = 200;


int led0=2;              //підсвітка очей
int led1=3; 
int led2=4; 
int led3=5; 
int led4=6; 
int led5=7; 
int led6=8; 
int led7=9; 

int p = 0;
int s=0;
int p0 = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;
int p6 = 0;
int p7 = 0;


String string0 = "Master_Maski_on#";

String stringgood = "Slave_Maski_good#";
String stringbad = "Slave_Maski_bad#";
String string;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
    pinMode(13, OUTPUT);
    pinMode(Sens0, INPUT);
    pinMode(Sens1, INPUT);
    pinMode(Sens2, INPUT);
    pinMode(Sens3, INPUT);
    pinMode(Sens4, INPUT);
    pinMode(Sens5, INPUT);
    pinMode(Sens6, INPUT);
    pinMode(Sens7, INPUT);
    
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
}


 
void loop() 
{ 
 if(p==1) {
  
  
  if (analogRead(Sens0)< val) {p0=1;digitalWrite(led0, LOW); time0 = millis();} else if (analogRead(Sens0) > val) {p0=0; if(millis() - time0>1000){digitalWrite(led0, HIGH);}}
  if (analogRead(Sens1)< 300) {p1=1;digitalWrite(led1, LOW); time1 = millis();} else if (analogRead(Sens1) > 300) {p1=0; if(millis() - time1>1000){digitalWrite(led1, HIGH);}}
  if (analogRead(Sens4)< 250) {p4=1;digitalWrite(led4, LOW); time4 = millis();} else if (analogRead(Sens4) > 250) {p4=0; if(millis() - time4>1000){digitalWrite(led4, HIGH);}}
  if (analogRead(Sens6)< val) {p6=1;digitalWrite(led6, LOW); time6 = millis();} else if (analogRead(Sens6) > val) {p6=0; if(millis() - time6>1000){digitalWrite(led6, HIGH);}}
  
  if (analogRead(Sens2)< val) {p2=1;digitalWrite(led2, LOW); time2 = millis();} else if (analogRead(Sens2) > val) {p2=0; if(millis() - time2>1000){digitalWrite(led2, HIGH);}}
  if (analogRead(Sens3)< val) {p3=1;digitalWrite(led3, LOW); time3 = millis();} else if (analogRead(Sens3) > val) {p3=0; if(millis() - time3>1000){digitalWrite(led3, HIGH);}}
  if (analogRead(Sens5)< val) {p5=1;digitalWrite(led5, LOW); time5 = millis();} else if (analogRead(Sens5) > val) {p5=0; if(millis() - time5>1000){digitalWrite(led5, HIGH);}}
  if (analogRead(Sens7)< val) {p7=1;digitalWrite(led7, LOW); time7 = millis();} else if (analogRead(Sens7) > val) {p7=0; if(millis() - time7>1000){digitalWrite(led7, HIGH);}}
  
  s=p1+p2+p3+p4+p5+p6+p7+p0;
  if( s == 4) {
    if( p0==1 && p1==1 && p4==1 && p6==1){ lightOff();digitalWrite(SSerialTxControl, HIGH); RS485Serial.println(stringgood); s=0; p=0;}
    else{digitalWrite(SSerialTxControl, HIGH);RS485Serial.println(stringbad); delay(1000); lightOff();  lightOn();  lightOff();  lightOn();  lightOff();  lightOn(); s=0;}
  }
  if(s>4) {digitalWrite(SSerialTxControl, HIGH);RS485Serial.println(stringbad); delay(1000); lightOff(); lightOn();  lightOff();  lightOn(); lightOff();  lightOn(); s=0;}
    
  
  }
  
  digitalWrite(SSerialTxControl, LOW);
   if (RS485Serial.available()) {
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
        p=1;
      }
      
    string = "";
    }

}
loop();
}

void lightOff() {
    digitalWrite(led0, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    delay(300);
}

void lightOn() {
    digitalWrite(led0, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    delay(300);
}


