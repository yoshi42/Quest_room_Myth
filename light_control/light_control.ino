#include <SoftwareSerial.h>

#define SSerialRX        4  //Serial Receive pin
#define SSerialTX        12  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Li_office A1

int Li_kor1 = 11;
int Li_kor2 = 10;
int Li_kor3 = 9;
int Li_kor4 = 6;
int Li_strob1 = 5;
int Li_strob2 = 3;

int rele_1 = 14;        //запасные реле
int rele_2 = 8;
int rele_3 = 7;

String Master_Li_on = "Master_Li_on#";
String Master_Li_kor1 = "Master_Li_kor1#";
String Master_Li_kor2 = "Master_Li_kor2#";
String Master_Li_kor3 = "Master_Li_kor3#";
String Master_Li_kor4 = "Master_Li_kor4#";
String Master_Li_office_on = "Master_Li_office_on#";
String Master_Li_office_off = "Master_Li_office_off#";
String Master_Li_off = "Master_Li_off#";
String Master_Li_rele1 = "Master_Li_rele1#";         //дим машина
String Master_Li_rele2 = "Master_Li_rele2#";
String Master_Li_rele3 = "Master_Li_rele3#";
String Master_Li_strob = "Master_Li_strob#";

String Master_Li_kor1_good = "Master_Li_kor1_good#";//просветление на 2сек при правильном выполнении
String Master_Li_kor2_good = "Master_Li_kor2_good#";//просветление на 2сек при правильном выполнении
String Master_Li_kor3_good = "Master_Li_kor3_good#";//просветление на 2сек при правильном выполнении
String Master_Li_kor4_good = "Master_Li_kor4_good#";//просветление на 2сек при правильном выполнении

String Master_Li_kor1_bad = "Master_Li_kor1_bad#";//мигание 1-2сек
String Master_Li_kor2_bad = "Master_Li_kor2_bad#";//мигание 1-2сек
String Master_Li_kor3_bad = "Master_Li_kor3_bad#";//мигание 1-2сек
String Master_Li_kor4_bad = "Master_Li_kor4_bad#";//мигание 1-2сек

String Master_Li_kor1_fading = "Master_Li_kor1_fading#"; //затухание
String Master_Li_kor2_fading = "Master_Li_kor2_fading#"; //затухание
String Master_Li_kor3_fading = "Master_Li_kor3_fading#"; //затухание
String Master_Li_kor4_fading = "Master_Li_kor4_fading#"; //затухание

String Master_Li_kor1_shimering = "Master_Li_kor1_shimering#"; //затухание

String Master_Li_stop_fading = "Master_Li_stop_fading#";//остановить затухание

unsigned int fade_k1 = 0; //флаг на включение затухания в К1
unsigned int fade_k2 = 0; //флаг на включение затухания в К2
unsigned int fade_k3 = 0; //флаг на включение затухания в К3
unsigned int fade_k4 = 0; //флаг на включение затухания в К4
unsigned int shim_k1 = 0; //флаг на включение мерцания в К1 вначале игры

String string;
unsigned long i = 0;
unsigned long time0 = 0;
int delay_strob = 30;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX


void setup() {
    Serial.begin(9600);
    RS485Serial.begin(9600); 
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    pinMode(Li_kor1, OUTPUT);
    pinMode(Li_kor2, OUTPUT);
    pinMode(Li_kor3, OUTPUT);
    pinMode(Li_kor4, OUTPUT);
    pinMode(Li_strob1, OUTPUT);
    pinMode(Li_strob2, OUTPUT);
    pinMode(Li_office, OUTPUT);
    pinMode(rele_1, OUTPUT);
    pinMode(rele_2, OUTPUT);
    pinMode(rele_3, OUTPUT);
    analogWrite(Li_kor1, 255);
    analogWrite(Li_kor3, 255);
    analogWrite(Li_kor2, 255);
    analogWrite(Li_kor4, 255);
    analogWrite(Li_strob1, 0);
    analogWrite(Li_strob2, 0);
    digitalWrite(Li_office, HIGH);

    //message_strob();
}

void loop() {  

  digitalWrite(SSerialTxControl, LOW);
  if (RS485Serial.available()) {
    string = "";
    delay(50);
    tx();
 }

 effects();
}

void tx() {                          // розпізнання команди
  digitalWrite(SSerialTxControl, LOW);
  while (RS485Serial.available())
  {
    char inChar = RS485Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(Master_Li_on))
      {
        analogWrite(Li_kor1, 255);
        analogWrite(Li_kor2, 255);
        analogWrite(Li_kor3, 255);
        analogWrite(Li_kor4, 255);
        digitalWrite(Li_office, LOW);
        digitalWrite(SSerialTxControl, HIGH);
        RS485Serial.println("ok_on");
        digitalWrite(SSerialTxControl, LOW);
      }

      if (string.equals(Master_Li_kor1) )
      {
        analogWrite(Li_kor1, 50);
        analogWrite(Li_kor2, 80);
        analogWrite(Li_kor3, 0);
        analogWrite(Li_kor4, 0);
        digitalWrite(Li_office, HIGH);
        shim_k1=0;
      }
      if (string.equals(Master_Li_kor2))
      {
        analogWrite(Li_kor1, 0);
        analogWrite(Li_kor2, 0);
        analogWrite(Li_kor3, 50);
        analogWrite(Li_kor4, 50);
        digitalWrite(Li_office, HIGH);
      }
      if (string.equals(Master_Li_kor3))
      {
        analogWrite(Li_kor1, 20);
        analogWrite(Li_kor2, 50);
        analogWrite(Li_kor3, 0);
        analogWrite(Li_kor4, 0);
        digitalWrite(Li_office, HIGH);
      }
      if (string.equals(Master_Li_kor4) )
      {
        analogWrite(Li_kor1, 0);
        analogWrite(Li_kor2, 0);
        analogWrite(Li_kor3, 50);
        analogWrite(Li_kor4, 0);
        digitalWrite(Li_office, HIGH);
      }
      if (string.equals(Master_Li_office_on))
      {
        digitalWrite(Li_office, LOW);
        analogWrite(Li_kor1, 0);
        analogWrite(Li_kor2, 0);
        analogWrite(Li_kor3, 15);
        analogWrite(Li_kor4, 15);
      }
      if (string.equals(Master_Li_office_off))
      {
         digitalWrite(Li_office, HIGH);
      }
      if (string.equals(Master_Li_off))
      {
        analogWrite(Li_kor1, 0);
        analogWrite(Li_kor2, 0);
        analogWrite(Li_kor3, 0);
        analogWrite(Li_kor4, 0);
        digitalWrite(Li_office, HIGH);
        digitalWrite(SSerialTxControl, HIGH);
        RS485Serial.println("ok_off");
        digitalWrite(SSerialTxControl, LOW);
      }
      if (string.equals(Master_Li_rele1))
      {
        digitalWrite(rele_1, LOW);
        delay(500);
        digitalWrite(rele_1, HIGH);
      }
      if (string.equals(Master_Li_rele2))
      {
        digitalWrite(rele_2, LOW);
        delay(500);
        digitalWrite(rele_2, HIGH);
      }
      if (string.equals(Master_Li_rele3))
      {
        digitalWrite(rele_3, LOW);
        delay(500);
        digitalWrite(rele_3, HIGH);
      }
      if (string.equals(Master_Li_strob))
      {
         message_strob();
      }







      if (string.equals(Master_Li_kor1_good) )
      {
        delay(1000);
        for(int i = 0; i < 100; i++)
          {
            int li = 50+i;
            analogWrite(Li_kor1, li);
            delay(15);
          }
        for(int i = 100; i > 0; i--)
        {
          int li = 50+i;
          analogWrite(Li_kor1, li);
          delay(10);
        }
      }

      if (string.equals(Master_Li_kor2_good) )
      {
        for(int i = 0; i < 100; i++)
          {
            int li = 70+i;
            analogWrite(Li_kor3, li);
            delay(15);
          }
        for(int i = 100; i > 0; i--)
        {
          int li = 70+i;
          analogWrite(Li_kor3, li);
          delay(10);
        }
      }

      if (string.equals(Master_Li_kor3_good) )
      {
        for(int i = 0; i < 100; i++)
          {
            int li = 50+i;
            analogWrite(Li_kor2, li);
            delay(15);
          }
        for(int i = 100; i > 0; i--)
        {
          int li = 50+i;
          analogWrite(Li_kor2, li);
          delay(10);
        }
      }

      if (string.equals(Master_Li_kor4_good) )
      {
        for(int i = 0; i < 100; i++)
          {
            int li = 15+i;
            analogWrite(Li_kor3, li);
            delay(15);
          }
        for(int i = 100; i > 0; i--)
        {
          int li = 15+i;
          analogWrite(Li_kor3, li);
          delay(10);
        }
      }








      if (string.equals(Master_Li_kor1_bad) )
      {
        for (int i=0; i<10;i++)
         { 
           int del = random(20, 80);
           analogWrite(Li_kor1, 5);
           analogWrite(Li_kor2, 5);
           delay(del);
           analogWrite(Li_kor1, 50);
           analogWrite(Li_kor2, 80);
           delay(del);
         }
         analogWrite(Li_kor1, 50);
         analogWrite(Li_kor2, 80);
      }

      if (string.equals(Master_Li_kor2_bad) )
      {
        for (int i=0; i<10;i++)
         { 
           int del = random(20, 80);
           analogWrite(Li_kor3, 5);
           analogWrite(Li_kor4, 5);
           delay(del);
           analogWrite(Li_kor3, 70);
           analogWrite(Li_kor4, 50);
           delay(del);
         }
         analogWrite(Li_kor3, 70);
         analogWrite(Li_kor4, 50);
      }

      if (string.equals(Master_Li_kor3_bad) )
      {
        for (int i=0; i<10;i++)
         { 
           int del = random(20, 80);
           analogWrite(Li_kor1, 5);
           analogWrite(Li_kor2, 5);
           delay(del);
           analogWrite(Li_kor1, 50);
           analogWrite(Li_kor2, 0);
           delay(del);
         }
         analogWrite(Li_kor1, 50);
         analogWrite(Li_kor2, 0);
      }

      if (string.equals(Master_Li_kor4_bad) )
      {
        for (int i=0; i<10;i++)
         { 
           int del = random(20, 80);
           analogWrite(Li_kor3, 0);
           analogWrite(Li_kor4, 0);
           delay(del);
           analogWrite(Li_kor3, 15);
           analogWrite(Li_kor4, 15);
           delay(del);
         }
         analogWrite(Li_kor3, 15);
         analogWrite(Li_kor4, 15);
      }








      if (string.equals(Master_Li_kor1_fading))
      {
        fade_k1 = 50;
      }

      if (string.equals(Master_Li_kor2_fading))
      {
        fade_k2 = 50;
      }

      if (string.equals(Master_Li_kor3_fading))
      {
        fade_k3 = 50;
      }

      if (string.equals(Master_Li_kor4_fading))
      {
        fade_k4 = 50;
      }

      if (string.equals(Master_Li_stop_fading))
      {
        fade_k1 = 0;
        fade_k2 = 0;
        fade_k3 = 0;
        fade_k4 = 0;
      }

      if (string.equals(Master_Li_kor1_shimering))
      {
        shim_k1 = 1;
      }

    string = "";
    }
  }
}

void effects()
{
  if (fade_k1 != 0)
  {
    analogWrite(Li_kor1, fade_k1);
    analogWrite(Li_kor2, fade_k1);
    fade_k1--;
    delay(200);

    /*digitalWrite(SSerialTxControl, HIGH);
    RS485Serial.println(fade_k1);
    digitalWrite(SSerialTxControl, LOW);*/
  }

  if (fade_k2 != 0)
  {
    analogWrite(Li_kor3, fade_k2);
    analogWrite(Li_kor4, fade_k2);
    fade_k2--;
    delay(200);

    /*digitalWrite(SSerialTxControl, HIGH);
    RS485Serial.println(fade_k2);
    digitalWrite(SSerialTxControl, LOW);*/
  }

  if (fade_k3 != 0)
  {
    analogWrite(Li_kor1, fade_k3);
    analogWrite(Li_kor2, fade_k3);
    fade_k3--;
    delay(200);

    /*digitalWrite(SSerialTxControl, HIGH);
    RS485Serial.println(fade_k1);
    digitalWrite(SSerialTxControl, LOW);*/
  }

  if (fade_k1 != 0)
  {
    analogWrite(Li_kor3, fade_k4);
    fade_k4--;
    delay(200);

    /*digitalWrite(SSerialTxControl, HIGH);
    RS485Serial.println(fade_k4);
    digitalWrite(SSerialTxControl, LOW);*/
  }

  if (shim_k1!=0)
      {
       int del = random(20, 80);
       int del2 = random(500, 3000);
       int i = random(1,7);
       for(i; i>=0; i--)
       {
        analogWrite(Li_kor1, 5);
        analogWrite(Li_kor2, 5);
        delay(del);
        analogWrite(Li_kor1, 30);
        analogWrite(Li_kor2, 30);
        delay(del);
      }
       delay(del2);
    }
}









void message_strob()
{
  analogWrite(Li_kor1, 0);
  analogWrite(Li_kor2, 0);
  delay(1000);
  for (int i=0; i<70; i++)
  {
    analogWrite(Li_strob2, 255);
    delay(delay_strob);
    analogWrite(Li_strob2, 0);
    delay(delay_strob);
  }

  delay(1000);

  for (int i=0; i<30; i++)
  {
    analogWrite(Li_strob1, 255);
    delay(delay_strob);
    analogWrite(Li_strob1, 0);
    delay(delay_strob);
  }
}