#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define SSerialRX        7  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 – 500 Ohm resistor on first pixel’s data input
// and minimize distance between Arduino and first pixel. Avoid connecting
// on a live circuit…if you must, connect GND first.

String string0 = "Master_Burzh_on#";
String string1 = "Master_Burzh_off#";
String string2 = "Master_Burzh_open#";

String stringgood = "Slave_Burzh_good";

String string;

int hollSens= 4;            //датчик хола 
int rele = 8;
int zamok = 9;
int a =0;
int p=0;
int r;

unsigned long time0 = 0;
unsigned long time1 = 0;
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup() {
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, LOW);\
  pinMode(zamok, OUTPUT);
  digitalWrite(zamok, HIGH);
  pinMode(hollSens, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  RS485Serial.begin(9600); 
// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
// End of trinket special code

strip.begin();
strip.show(); // Initialize all pixels to ‘off’

}

void loop() {
digitalWrite(SSerialTxControl, LOW);
   if (RS485Serial.available()) {
  tx();
 } 
if (p==0){      //викл лєнту
  int r = 0;
    int b = 0;
    int g = 0;
    for(int x = 0; x <30; x++)
    {
      int flicker = random(0,40);
      int r1 = r-flicker;
      int g1 = g-flicker;
      int b1 = b-flicker;
      if(g1<0) g1=0;
      if(r1<0) r1=0;
      if(b1<0) b1=0;
      strip.setPixelColor(x,r1,g1, b1);
    }
    strip.show();
}
if (p==1) {
  if (a==0){          //перший режим
    if(millis()-time0<1000){
      digitalWrite(rele, HIGH);
    }else if(millis()-time0>1000){
      digitalWrite(rele, LOW);
    }
    int r = 150;
    int b = 50;
    int g = 0;
    for(int x = 0; x <30; x++)
    {
      int flicker = random(0,40);
      int r1 = r-flicker;
      int g1 = g-flicker;
      int b1 = b-flicker;
      if(g1<0) g1=0;
      if(r1<0) r1=0;
      if(b1<0) b1=0;
      strip.setPixelColor(x,r1,g1, b1);
    }
    strip.show();
    delay(random(50,150)); 
  }
  if (digitalRead(hollSens) == LOW && a==0){digitalWrite(SSerialTxControl, HIGH); RS485Serial.println(stringgood); a=1; time0=millis();}
  
  if (a==1){                //другий режим
    if(millis()-time0<4000){
      digitalWrite(rele, HIGH);
    }else if(millis()-time0>4000){
      digitalWrite(rele, LOW);
    }
      int r = 255;
      int b = 80;
      int g = 5; 
      for(int x = 0; x <30; x++)
      {
        int flicker = random(0,40);
        int r1 = r-flicker;
        int g1 = g-flicker;
        int b1 = b-flicker;
        if(g1<0) g1=0;
        if(r1<0) r1=0;
        if(b1<0) b1=0;
        strip.setPixelColor(x,r1,g1, b1);
      }
      strip.show();
      delay(random(50,150)); 
  }


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
        time0=millis();
      }
      if (string.equals(string1) )
      {  
        p=0; 
      }
      if (string.equals(string2) )
      {  
       digitalWrite(zamok, LOW);   
      delay(1000);
     digitalWrite(zamok, HIGH);  
      }   
    string = "";
    }

}
loop();
}




