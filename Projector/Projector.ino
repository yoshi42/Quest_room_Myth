#include <IRremote.h>
#include <SoftwareSerial.h>
#include <Servo.h>
/*
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
*/
/*/Аналоговая коммуникация - замена RS485, коммуникация через жопу


        2   7   8 
on      0   0   1
start1  0   1   0
stop    0   1   1
start2  1   0   0
off     1   0   1


*/

#define anal_comm_a2 2
#define anal_comm_a7 7
#define anal_comm_a8 8 

int flag_on = 0;
 int   flag_start1 = 0;
 int   flag_start2 = 0;
 int   flag_stop = 0;
 int   flag_off = 0;
 
int servoPin = 9;

unsigned long time0 = 0;

Servo servo;
IRsend irsend;

void setup()
{
    pinMode(anal_comm_a2, INPUT_PULLUP);
    pinMode(anal_comm_a7, INPUT_PULLUP);
    pinMode(anal_comm_a8, INPUT_PULLUP);

    Serial.begin(9600);
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
 
  tx();
}

void tx() {              //розпізнання команд
  if (digitalRead(anal_comm_a2) == HIGH && digitalRead(anal_comm_a7) == HIGH && digitalRead(anal_comm_a8) == LOW && flag_on == 0)
 {
    irOn();
    flag_on = 1;
 }
 if (digitalRead(anal_comm_a2) == HIGH && digitalRead(anal_comm_a7) == LOW && digitalRead(anal_comm_a8) == HIGH && flag_start1 == 0)
 {
    irsend.sendNEC(0xFFC936, 32);      //включення відео
    servo.write(70);                    //відкриття шторки
    flag_start1 = 1;
 }
 if (digitalRead(anal_comm_a2) == HIGH && digitalRead(anal_comm_a7) == LOW && digitalRead(anal_comm_a8) == LOW && flag_stop == 0)
 {
   irsend.sendNEC(0xFFC936, 32);      //виключення відео
        servo.write(0);                      //закриття шторки
    flag_stop = 1;
 }
 if (digitalRead(anal_comm_a2) == LOW && digitalRead(anal_comm_a7) == HIGH && digitalRead(anal_comm_a8) == HIGH && flag_start2 == 0)
 {
    irsend.sendNEC(0xFFC936, 32);      //включення відео
    servo.write(70);                    //відкриття шторки
    flag_start2 = 1;
 
 }if (digitalRead(anal_comm_a2) == LOW && digitalRead(anal_comm_a7) == HIGH && digitalRead(anal_comm_a8) == LOW && flag_off == 0)
 {
     irsend.sendNEC(0xFF15EA, 32);      //виключення проектора
        servo.write(0);                    //закриття шторки
    flag_off = 1;
 }
 if (digitalRead(anal_comm_a2) == HIGH && digitalRead(anal_comm_a7) == HIGH && digitalRead(anal_comm_a8) == HIGH)
 {
    flag_on = 0;
    flag_start1 = 0;
    flag_start2 = 0;
    flag_stop = 0;
    flag_off = 0;
 }
 
      
}


