/*on FF15EA (32 bits)
source FFE916 (32 bits)
right FF9966 (32 bits)
left FFD926 (32 bits)
up FFA956 (32 bits)

down FF59A6 (32 bits)

ok FF7986 (32 bits)
play FFC936 (32 bits)
exit FF25DA (32 bits)
*/

#include <IRremote.h>

#define SerialTxControl 2
#define RS485Transmit HIGH
#define RS485Receive LOW

char buffer[100];
byte state = 0;

IRsend irsend;

void setup()
{
    Serial.begin(9600);
    pinMode(SerialTxControl, OUTPUT); 
    digitalWrite(SerialTxControl, RS485Receive); // переводим устройство в режим приёмника
    irblink();
}

void irblink() 
{
	irsend.sendNEC(0xFF15EA, 32); //on
    delay(8000);
    irsend.sendNEC(0xFF59A6, 32); // down
    delay(1000);
    irsend.sendNEC(0xFF9966, 32); // ->
    delay(1000);
    irsend.sendNEC(0xFF7986, 32); // ok
    delay(1000);
    irsend.sendNEC(0xFF9966, 32); // ->
    delay(1000);
    irsend.sendNEC(0xFFC936, 32); // play
    delay(5000);
    irsend.sendNEC(0xFFC936, 32); // pause
    Serial.println("done");
}
 
void loop(void) 
{
    int i=0;
    if( Serial.available() )
    { // если в порт пришли какие-то данные
        delay(5); // немного ждём, чтобы вся пачка данных была принята портом
        while( Serial.available() )
        {
            buffer[i++] = Serial.read(); // считываем данные и записываем их в буфер
        }
    }
    if(i>0)
    { // если в буфере что-то есть
        buffer[i++]='\0'; // превращаем содержимое буфера в строку, добавляя нулевой символ
        if( strcmp(buffer, "Master_Window1_on_vid1") )
        { // если принятая строка равна тексту
        	Serial.println("ok Master_Window1_on_vid1");
            //irblink(); //do a program
            delay(1000);
        }

        else if( strcmp(buffer, "Master_Window1_vid2") )
        { // если принятая строка равна тексту
        	Serial.println("ok Master_Window1_vid2");
            irsend.sendNEC(0x807C02FD, 32); // next
   			delay(1000);
        }

        else if( strcmp(buffer, "") )
        { // если принятая строка равна тексту ping
        	Serial.println("ok Master_Window1_off");
            irsend.sendNEC(0x807C50AF, 32); // off
   			delay(1000);
        }
    }
}