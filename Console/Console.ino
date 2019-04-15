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
String string;

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
 digitalWrite(SSerialTxControl, LOW); // LOW - прием
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
  button_radio_message();
  keypad_message();
  button_message();
  resistor_message();
  tx();
}

void tx() {                          // розпізнання команди
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#')
    {
        digitalWrite(SSerialTxControl, HIGH); //включаем режим передачи
        RS485Serial.println(string);
        digitalWrite(SSerialTxControl, LOW); //выключаем режим передачи
    string = "";
    }
  }
}

void button_message() {
  if(digitalRead(green_button)==LOW && p_green_button==0){
    delay(100);
    if(digitalRead(switch_up)==LOW && p_switch_up==0) {
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("ru#");
      delay(100);
      digitalWrite(SSerialTxControl, LOW);
      p_switch_up=1;
    }
    if(digitalRead(switch_down)==LOW && p_switch_down==0) {
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("heb#");
      delay(100);
      digitalWrite(SSerialTxControl, LOW);
      p_switch_down=1;
    }
    if(digitalRead(switch_up)==HIGH && digitalRead(switch_down)==HIGH && p_switch==0) {
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("en#");
      delay(100);
      digitalWrite(SSerialTxControl, LOW);
      p_switch=1;
    }
    delay(100);
    digitalWrite(SSerialTxControl, HIGH);
    delay(100);
    RS485Serial.println("start#");
    delay(100);
    digitalWrite(SSerialTxControl, LOW);
    p_green_button=1;
  }
  if(digitalRead(green_button)==HIGH && p_green_button==1){
    p_green_button=0;
    p_switch_up=0;
    p_switch_down=0;
    p_switch=0;
  }
  if(digitalRead(red_button)==LOW && p_red_button==0){
    digitalWrite(SSerialTxControl, HIGH);
    RS485Serial.println("reset#");
    digitalWrite(SSerialTxControl, LOW);
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
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println(res1_2 + message_res1);
      digitalWrite(SSerialTxControl, LOW);
      time0=millis();
    }
    if((res2_1-res2_2)>2 || (res2_2-res2_1)>2){
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println(res2_2 + message_res2);
      digitalWrite(SSerialTxControl, LOW);
      time0=millis();
    }
    
  }
  
}
void button_radio_message() { 
    kod = RemoteReceiver::getData();
    if(kod==11679496  && p_A==0){        //A
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("radioA#");
      digitalWrite(SSerialTxControl, LOW);
      time_A=millis();
      p_A = 1;
    }else if(millis()-time_A>1000  && p_A==1){
      p_A = 0;
    }
    if(kod==11679492  && p_B==0){        //B
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("radioB#");
      digitalWrite(SSerialTxControl, LOW);
      time_B=millis();
      p_B = 1;
    }else if(millis()-time_B>1000  && p_B==1){
      p_B = 0;
    }
    if(kod==11679490  && p_C==0){        //C
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("radioC#");
      digitalWrite(SSerialTxControl, LOW);
      time_C=millis();
      p_C = 1;
    }else if(millis()-time_C>1000  && p_C==1){
      p_C = 0;
    }
    if(kod==11679489  && p_D==0){        //D
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println("radioD#");
      digitalWrite(SSerialTxControl, LOW);
      time_D=millis();
      p_D = 1;
    }else if(millis()-time_D>1000  && p_D==1){
      p_D = 0;
    }
}


void keypad_message() {
 char pressed=keypad.getKey();
 if(pressed=='1'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("1#");Serial.println("1#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='2'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("2#");Serial.println("2#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='3'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("3#");Serial.println("3#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='4'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("4#");Serial.println("4#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='5'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("5#");Serial.println("5#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='6'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("6#");Serial.println("6#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='7'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("7#");Serial.println("7#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='8'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("8#");Serial.println("8#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='9'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("9#");Serial.println("9#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='0'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("0#");Serial.println("0#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='A'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("A#");Serial.println("A#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='B'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("B#");Serial.println("B#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='C'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("C#");Serial.println("C#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='D'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("D#");Serial.println("D#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='E'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("E#");Serial.println("E#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='F'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("F#");Serial.println("F#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='G'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("G#");Serial.println("G#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='H'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("H#");Serial.println("H#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='I'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("I#");Serial.println("I#"); digitalWrite(SSerialTxControl, LOW);}
 if(pressed=='J'){digitalWrite(SSerialTxControl, HIGH);RS485Serial.println("J#");Serial.println("J#"); digitalWrite(SSerialTxControl, LOW);}
}