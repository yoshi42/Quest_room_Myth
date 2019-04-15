#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        2  //Serial Transmit pin
#define SSerialTxControl 3   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

int solen = 5;              //соленоид
int sens = 10;              //концевик

int start = 0;              //флаг режимов 0,1,2
int a = 0;                  //счетчик
int p = 0;                  //счетчик включения аудио
int p1=0;                   //флаг в дежурном режиме
int mp_1 = 0;               //
int mp_2 = 0;               //
int mp_3 = 0;               //
int buzzer = 0;             //флаг для звонка
int q = 0;                  //флаг для трубки
int s = 0;                  //щетчик общий

/*/Аналоговая коммуникация - замена RS485, коммуникация через жопу
anal_comm_a9 INPUT_PULLUP
anal_comm_a10 INPUT_PULLUP
anal_comm_a10 OUTPUT

    a9 a10 a11
ru   1   0  -
en   0   1  -
heb  0   0  -

good -   -  0
*/

#define anal_comm_a9 7
#define anal_comm_a10 2
#define anal_comm_a11 3 //good

int flag_start = 0;
int flag_ring = 0;

String string0 = "Master_Phone2_start#";
String string1 = "Master_Phone2_ring#";
String string2 = "Master_Phone2_off#";
String string;


String stringgood = "Slave_Phone2_good#";

unsigned long time0 = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
unsigned long time4 = 0;


SoftwareSerial mySerial(13, 12); // RX, TX
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup() {

pinMode(solen, OUTPUT);
pinMode(A2, INPUT);
pinMode(sens, INPUT_PULLUP);
mySerial.begin(9600);                     // скорость софт Сериал
  
  mp3_set_serial (mySerial);                //   софтовый серийный порт для мп3
  delay (100);                              //  обязательная задержка между командами
  mp3_set_volume (30);
  Serial.begin(9600);
 pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, LOW);
  RS485Serial.begin(9600);

  
  pinMode(anal_comm_a9, INPUT_PULLUP);                     
  pinMode(anal_comm_a10, INPUT_PULLUP);                      
  pinMode(anal_comm_a11, OUTPUT);
  digitalWrite(anal_comm_a11,HIGH);

}

void loop() {
  digitalWrite(SSerialTxControl, LOW);
  if(RS485Serial.available())
  {
    string = "";
    delay(100);
   // tx();
    
  }
   if (digitalRead(anal_comm_a9) == HIGH && digitalRead(anal_comm_a10) == LOW && flag_start == 0)
 {
    start=1;
    time0=-10000;
    flag_start = 1;
 }
 if (digitalRead(anal_comm_a9) == LOW && digitalRead(anal_comm_a10) == HIGH && flag_ring == 0)
 {
    s=0;
    start=2;
    time3=millis();
    flag_ring=1;
 }
 if(digitalRead(anal_comm_a9) == LOW && digitalRead(anal_comm_a10) == LOW){
  start=0;
  flag_start = 0;
  flag_ring=0;
 }
 message_start();
    
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
        start=1;
        time0=-10000;
      }
      if (string.equals(string1) )
      {
        s=0;
        start=2;
        time3=millis();
      }
      if (string.equals(string2))
      {
        start=0;
      }
      string = "";
    }
  }
}

void message_start(){


  if(start==0){                                                         //в дежурном режиме

  if(digitalRead(sens)==LOW  && p1==0){                          
     mp3_play (4);
     p1=1;
  }else if(digitalRead(sens)==HIGH  && p1==1){
     mp3_stop ();
     p1=0;
  }
  p=0;
  mp_1=0;
  mp_2=0;
  mp_3=0;
  buzzer=0;
  s=0;
  }



  
  if(millis()-time0>10000 && start==1){                                     //при поступлении сигнала start
    
      while( buzzer==0){                          //телефон звонит    
        if(digitalRead(sens)==HIGH){q=1;}         //
        if(digitalRead(sens)==LOW && q==1){q=0;p=1;buzzer=1; break;}
        mp3_stop ();
        if(mp_3 == 2){
          mp_1=0;
          mp_2=0;
          mp_3=0;
        }
        while(millis()-time4<2000){
            digitalWrite(solen, HIGH);
            delay(20);
            digitalWrite(solen, LOW);
            delay(20);
            if(digitalRead(sens)==HIGH){q=1;}
            if(digitalRead(sens)==LOW && q==1){q=0;p=1;buzzer=1; break;}
        }
        if(millis()-time4>4000){
          time4=millis();
        }
      }
      
    time1=millis(); 

    
    while(digitalRead(sens)==LOW  && p==1){                                   //включение аудио 1,2,3
      buzzer=1;
      if(mp_1==0 && mp_2==0 && mp_3==0){ mp3_play (1);  mp_1 = 1; s++;} 
      if(mp_1==2 && mp_2==0 && mp_3==0){ mp3_play (2);  mp_2 = 1; s++;} 
      if(mp_1==2 && mp_2==2 && mp_3==0){ mp3_play (3);  mp_3 = 1; s++;}
        
      if(mp_1==1 && (millis()-time1>15000)){mp3_stop ();p=2;}
      if(mp_2==1 && (millis()-time1>20000)){mp3_stop ();p=2;}
      if(mp_3==1 && (millis()-time1>9000)){mp3_stop ();p=2;}
      
      if(digitalRead(sens)==HIGH && mp_1==1){mp_1 = 2; mp3_stop (); buzzer=0; p=0;  time0=millis();}
      if(digitalRead(sens)==HIGH && mp_2==1){mp_2 = 2; mp3_stop (); buzzer=0; p=0;  time0=millis();}
      if(digitalRead(sens)==HIGH && mp_3==1){mp_3 = 2; mp3_stop (); buzzer=0; p=0;  time0=millis();}
      
      if(millis()-time1>3000 && s>2){                 //проверка есть ли ответ
        while(analogRead(A2)<50){
            a++;
            int k = 0;
              if(a>20){
                if(k==0){
                  digitalWrite(anal_comm_a11, HIGH);
                  delay(300);
                  RS485Serial.println(stringgood); 
                  k=1;
                }
                mp3_stop (); 
                delay(2000);
                mp3_play (5);
                delay(100);
                digitalWrite(SSerialTxControl, LOW);
                p1=1;
                start=0;
                a=0;
                p=0;
                break;
              }
            }
            if(analogRead(A2)>50){ a=0;}
        }
    }
    time2=millis();
    
    while(digitalRead(sens)==LOW  && p==2){                               // короткие гудки
      if(mp_1==1 && mp_2==0 && mp_3==0){ mp3_play (5); mp_1 = 2; } 
      if(mp_1==2 && mp_2==1 && mp_3==0){ mp3_play (5); mp_2 = 2; } 
      if(mp_1==2 && mp_2==2 && mp_3==1){ mp3_play (5); mp_3 = 2; }
      while(millis()-time2>30000 && digitalRead(sens)==LOW){
        digitalWrite(solen, HIGH);
        delay(20);
        digitalWrite(solen, LOW);
        delay(20);
      }
      if(digitalRead(sens)==HIGH){mp3_stop (); buzzer=0; p=0;  time0=millis();}

    }
     
  }
  
  if(start==2){                                               //при поступлении сигнала singl
    mp3_stop ();
   while(millis()-time3<2000){
        digitalWrite(solen, HIGH);
        delay(20);
        digitalWrite(solen, LOW);
        delay(20);
   }
   while(millis()-time3>4000 && millis()-time3<6000){
        digitalWrite(solen, HIGH);
        delay(20);
        digitalWrite(solen, LOW);
        delay(20);
   }  
   while(millis()-time3>10000 && millis()-time3<12000){
        digitalWrite(solen, HIGH);
        delay(20);
        digitalWrite(solen, LOW);
        delay(20);
   }
   if(millis()-time3>12000){
        start=0;
   }
  }
}
  


