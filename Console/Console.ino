#include <Keypad.h>
#include <SoftwareSerial.h>
#include <RemoteReceiver.h>

//A = 11679496            //коди кнопок радіо пульта
//B = 11679492
//C = 11679490
//D = 11679489

#define SSerialRX        14  //Serial Receive pin
#define SSerialTX        15  //Serial Transmit pin
#define SSerialTxControl 13   //RS485 Direction control

int res1 = A6;
int res2 = A7;

int green_button = 11;        //кнопка старта
int red_button = 12;          //кнопка стоп
int switch_up = 16;           //тумблер вверх
int switch_down= 17;          //тумблер вниз

int p_green_button = 0;      //флаги кнопок
int p_red_button = 0;
int p_switch_up = 0;
int p_switch_down= 0;
int p_switch = 0;
int p_A = 0;
int p_B = 0;
int p_C = 0;
int p_D = 0;

int res1_1 = 0;
int res1_2 = 0;
int res2_1 = 0;
int res2_2 = 0;

String message_res1 = "_res1#";
String message_res2 = "_res2#";

char keys[4][5]={
 {'1','2','3','4','5'},
 {'6','7','8','9','0'},
 {'A','B','C','D','E'},
 {'F','G','H','I','J'}};
 
byte rowPin[4]={7, 8, 9, 10};
byte colPin[5]={6, 5, 4, 3, 19};

unsigned long time0 = 0;
unsigned long kod = 0;
unsigned long time_A = 0;
unsigned long time_B = 0;
unsigned long time_C = 0;
unsigned long time_D = 0;
 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,5);

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
 
void setup()
{
 Serial.begin(9600);
 pinMode(SSerialTxControl, OUTPUT);
 digitalWrite(SSerialTxControl, HIGH);
 RS485Serial.begin(9600);

 pinMode(green_button, INPUT_PULLUP);
 pinMode(red_button, INPUT_PULLUP);
 pinMode(switch_up, INPUT_PULLUP);
 pinMode(switch_down, INPUT_PULLUP);
 pinMode(res1, INPUT);
 pinMode(res1, INPUT);
 
 // start the remote receiver using interrupt 0 (pin 2)
  RemoteReceiver::start(0);
}
 
void loop()
{
  digitalWrite(SSerialTxControl, HIGH);
  button_radio_message();
  keypad_message();
  button_message();
  resistor_message();
}

void button_message() {
  if(digitalRead(green_button)==LOW && p_green_button==0){
    if(digitalRead(switch_up)==LOW && p_switch_up==0) {
      RS485Serial.println("ru#");
      p_switch_up=1;
    }
    if(digitalRead(switch_down)==LOW && p_switch_down==0) {
      RS485Serial.println("heb#");
      p_switch_down=1;
    }
    if(digitalRead(switch_up)==HIGH && digitalRead(switch_down)==HIGH && p_switch==0) {
      RS485Serial.println("en#");
      p_switch=1;
    }
    RS485Serial.println("start#");
    p_green_button=1;
  }
  if(digitalRead(green_button)==HIGH && p_green_button==1){
    p_green_button=0;
    p_switch_up=0;
    p_switch_down=0;
    p_switch=0;
  }
  if(digitalRead(red_button)==LOW && p_red_button==0){
    RS485Serial.println("reset#");
    p_red_button=1;
  }
  if(digitalRead(red_button)==HIGH && p_red_button==1){
    p_red_button=0;
  }
  
}

void resistor_message() {
  if(millis()-time0<20){
     res1_1 = analogRead(res1)/34;
     res2_1 = analogRead(res2)/34;
  }
   res1_2 = analogRead(res1)/34;
   res2_2 = analogRead(res2)/34;
  if(millis()-time0>500){
    if((res1_1-res1_2)>2 || (res1_2-res1_1)>2){
      RS485Serial.println(res1_2 + message_res1);
      time0=millis();
    }
    if((res2_1-res2_2)>2 || (res2_2-res2_1)>2){
      RS485Serial.println(res2_2 + message_res2);
      time0=millis();
    }
    
  }
  
}
void button_radio_message() { 
    kod = RemoteReceiver::getData();
    if(kod==11679496  && p_A==0){        //A
      RS485Serial.println("radioA#");
      time_A=millis();
      p_A = 1;
    }else if(millis()-time_A>1000  && p_A==1){
      p_A = 0;
    }
    if(kod==11679492  && p_B==0){        //B
      RS485Serial.println("radioB#");
      time_B=millis();
      p_B = 1;
    }else if(millis()-time_B>1000  && p_B==1){
      p_B = 0;
    }
    if(kod==11679490  && p_C==0){        //C
      RS485Serial.println("radioC#");
      time_C=millis();
      p_C = 1;
    }else if(millis()-time_C>1000  && p_C==1){
      p_C = 0;
    }
    if(kod==11679489  && p_D==0){        //D
      RS485Serial.println("radioD#");
      time_D=millis();
      p_D = 1;
    }else if(millis()-time_D>1000  && p_D==1){
      p_D = 0;
    }
}


void keypad_message() {
 char pressed=keypad.getKey();
 if(pressed=='1'){RS485Serial.println("1#"); }
 if(pressed=='2'){RS485Serial.println("2#"); }
 if(pressed=='3'){RS485Serial.println("3#"); }
 if(pressed=='4'){RS485Serial.println("4#"); }
 if(pressed=='5'){RS485Serial.println("5#"); }
 if(pressed=='6'){RS485Serial.println("6#"); }
 if(pressed=='7'){RS485Serial.println("7#"); }
 if(pressed=='8'){RS485Serial.println("8#"); }
 if(pressed=='9'){RS485Serial.println("9#"); }
 if(pressed=='0'){RS485Serial.println("0#"); }
 if(pressed=='A'){RS485Serial.println("A#"); }
 if(pressed=='B'){RS485Serial.println("B#"); }
 if(pressed=='C'){RS485Serial.println("C#"); }
 if(pressed=='D'){RS485Serial.println("D#"); }
 if(pressed=='E'){RS485Serial.println("E#"); }
 if(pressed=='F'){RS485Serial.println("F#"); }
 if(pressed=='G'){RS485Serial.println("G#"); }
 if(pressed=='H'){RS485Serial.println("H#"); }
 if(pressed=='I'){RS485Serial.println("I#"); }
 if(pressed=='J'){RS485Serial.println("J#"); }
}

