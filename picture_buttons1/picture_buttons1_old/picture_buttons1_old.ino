#include <SoftwareSerial.h>

#define SSerialRX        19  //pin4 Serial Receive pin
#define SSerialTX        20  //pin3 Serial Transmit pin
#define SSerialTxControl 21  //pin2 RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int anal_photos4 = 4;
int anal_photos3 = 3;
int anal_photos2 = 2;
int anal_photos13 = 13;

//int irsend = 3;
int button1= 9;            //інфра червоний датчик  
int button2= 7;
int button3= 8;
int button4= 11;
int button5= 10;


int MHSens= 12;

int led1 = 16;        //підсвітка
int led2 = 14;
int led3 = 15;
int led4 = 18;
int led5 = 17;

int dirOutPin = 5;
int stepOutPin = 6;

int light = 0;
int a = 0;
int p=0;              //флаги
int p1=0;
int p2=0;
int p3=0;
int p4=0;
int p5=0;
int p6=0;
int p0=0;

String string0 = "Master_Photos1_on#";
String string1 = "Master_Photos1_change#";
String string2 = "Master_Photos1_back#";

String stringbad = "Slave_Photos1_badParole#";
String stringgood = "Slave_Photos1_goodParole#";
String string;
unsigned long i = 0;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    RS485Serial.begin(9600); 
   // pinMode(irsend, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(dirOutPin, OUTPUT);
    pinMode(stepOutPin, OUTPUT);
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    pinMode(button4, INPUT_PULLUP);
    pinMode(button5, INPUT_PULLUP);
    pinMode(MHSens, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);

}

void loop() 
{ 
  
 digitalWrite(SSerialTxControl, LOW);

   if (Serial.available()) {
  string = "";
  delay(100);
  tx();
 }
  
  if (light==1) {
    if (digitalRead(button1) == LOW){digitalWrite(led1, HIGH);}else{digitalWrite(led1, LOW);}
    if (digitalRead(button2) == LOW){digitalWrite(led2, HIGH);}else{digitalWrite(led2, LOW);}
    if (digitalRead(button3) == LOW){digitalWrite(led3, HIGH);}else{digitalWrite(led3, LOW);}
    if (digitalRead(button4) == LOW){digitalWrite(led4, HIGH);}else{digitalWrite(led4, LOW);}
    if (digitalRead(button5) == LOW){digitalWrite(led5, HIGH);}else{digitalWrite(led5, LOW);}
  }if (light==0) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }

  
 if (p==1) {
  if (digitalRead(button1) == LOW && p1==0 && p2==0 && p3==0 && p4==0 && p5==0) {
     p1=1;
  }else if (digitalRead(button1) == LOW && (p2==1  || p3==1 || p4==1 || p5==1) && p0==0){
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
     p0=1;
     p1=0;p2=0;p3=0;p4=0;p5=0;
     
  }
  
  if (digitalRead(button2) == LOW && p1==1 && p2==0 && p3==0 && p4==0 && p5==0) {
     p2=1;
   }else if (digitalRead(button2) == LOW && (p1==0  || p3==1 || p4==1 || p5==1) && p0==0){
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
     p0=1;
     p1=0;p2=0;p3=0;p4=0;p5=0;
  }
  
   if (digitalRead(button3) == LOW && p1==1 && p2==1 && p3==0 && p4==0 && p5==0) {
     p3=1;
   }else if (digitalRead(button3) == LOW && (p1==0 || p2==0  || p4==1 || p5==1) && p0==0){
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
     p0=1;
     p1=0;p2=0;p3=0;p4=0;p5=0;
  }
  
  if (digitalRead(button4) == LOW && p1==1 && p2==1 && p3==1 && p4==0 && p5==0) {
     p4=1;
  }else if (digitalRead(button4) == LOW && (p1==0 || p2==0 || p3==0  || p5==1) && p0==0){
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
     p0=1;
     p1=0;p2=0;p3=0;p4=0;p5=0;
  }
  
   if (digitalRead(button5) == LOW && p1==1 && p2==1 && p3==1 && p4==1 && p5==0) {
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringgood);
     p5=1;
     p=0; light=0; p1=0;p2=0;p3=0;p4=0;p5=0;
     
   }else if (digitalRead(button5) == LOW && (p1==0 || p2==0 || p3==0 || p4==0 ) && p0==0){
     digitalWrite(SSerialTxControl, HIGH);
     RS485Serial.println(stringbad);
     p0=1;
     p1=0;p2=0;p3=0;p4=0;p5=0;
  }


  if(digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH && digitalRead(button4) == HIGH && digitalRead(button5) == HIGH && p0==1){
    p0=0;
  }
}
  
 
}

void tx() {                          // розпізнання команди
  digitalWrite(SSerialTxControl, LOW);
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(string0))
      {
         p=1;
         light=1;
      }
      if (string.equals(string1) )
      {
          p=0;
         light=0;
         stepDown();
      }
      if (string.equals(string2))
      {
         p=0;
         light=0;
         stepUp();
         i=0;
         
      }
      
    string = "";
    }

}
loop();
}

void stepDown() {   //зміна фоток
     while (digitalRead(MHSens)==HIGH )
      {
       
     digitalWrite(dirOutPin, HIGH);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(50);

      digitalWrite(stepOutPin, HIGH);
      
      }
}
void stepUp() {   //повернення фото в стартову позицію
 while(i<65000 ){
        i++;
       digitalWrite(dirOutPin, LOW);

      digitalWrite(stepOutPin, LOW);

      delayMicroseconds(50);

      digitalWrite(stepOutPin, HIGH);
      }
}



