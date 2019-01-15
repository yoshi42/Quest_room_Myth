#include <IRremote.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define SSerialRX        8  //Serial Receive pin
#define SSerialTX        7  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

//int irsend = 3;

String string0 = "Master_Projector_on#";
String string1 = "Master_Projector_start1#";
String string2 = "Master_Projector_stop#";
String string3 = "Master_Projector_start2#";
String string4 = "Master_Projector_off#";
String string;

int servoPin = 9;

unsigned long time0 = 0;

Servo servo;
IRsend irsend;
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX



void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); // переводим устройство в режим приёмника
    
    RS485Serial.begin(9600); 
   // pinMode(irsend, OUTPUT);
    pinMode(13, OUTPUT);
    servo.attach(servoPin);
    servo.write(0);                    //закриття шторки
   
}

void irOn() //перша команда
{
    irsend.sendNEC(0xFF15EA, 32); //on
    delay(15000);
    irsend.sendNEC(0xFF59A6, 32); // down
    delay(1000);
    irsend.sendNEC(0xFF7986, 32); // ok
    delay(1000);
    irsend.sendNEC(0xFF7986, 32); // ok
    delay(1000);
    irsend.sendNEC(0xFF9966, 32); // ->
    delay(1000);
    irsend.sendNEC(0xFFC936, 32); // play
    delay(5000);
    irsend.sendNEC(0xFFC936, 32); // pause
    loop;
   /* 
    FFFFFFFF
FF15EA   on-off     4 sec
FF59A6   down      1 sec
FF7986   ok       1sec 
FF7986   ok       1sec
FF9966    ->      1 sec
FFC936   play-pause   1 sec
*/

}
 
void loop() 
{
 
  digitalWrite(SSerialTxControl, LOW);
  
 if (RS485Serial.available()) {
  string = "";
  delay(100);
  tx();
 }
}

void tx() {              //розпізнання команд
  digitalWrite(SSerialTxControl, LOW);
  while (RS485Serial.available())
  {
    char inChar = RS485Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(string0))
      {  
        irOn();
      }
      if (string.equals(string1))
      {
        irsend.sendNEC(0xFFC936, 32);      //включення відео
        servo.write(70);                    //відкриття шторки
      }
      if (string.equals(string2))
      {
        irsend.sendNEC(0xFFC936, 32);      //виключення відео
        servo.write(0);                      //закриття шторки
      }
      if (string.equals(string3))
      {
        irsend.sendNEC(0xFFC936, 32);      //включення відео
        servo.write(70);                    //відкриття шторки
      }
      if (string.equals(string4))
      {
          irsend.sendNEC(0xFF15EA, 32);      //виключення проектора
        servo.write(0);                    //закриття шторки
      }
    string = "";
    }

}
loop();
}




