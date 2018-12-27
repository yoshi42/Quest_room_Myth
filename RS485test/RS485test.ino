#define SerialTxControl 2
#define RS485Transmit HIGH
#define RS485Receive LOW

char buffer[100];
byte state = 0;

void setup(void) {
    Serial.begin(9600);
    pinMode(13, OUTPUT); 
    pinMode(SerialTxControl, OUTPUT); 
    digitalWrite(SerialTxControl, RS485Receive); // переводим устройство в режим приёмника
}
 
void loop(void) {
    int i=0;
    if( Serial.available() ){ // если в порт пришли какие-то данные
        delay(5); // немного ждём, чтобы вся пачка данных была принята портом
        while( Serial.available() ){
            buffer[i++] = Serial.read(); // считываем данные и записываем их в буфер
        }
    }
    if(i>0){ // если в буфере что-то есть
        buffer[i++]='\0'; // превращаем содержимое буфера в строку, добавляя нулевой символ
        if( strcmp(buffer, "ping") ){ // если принятая строка равна тексту ping
            digitalWrite(13, state); // мигаем светодиодом
            delay(500);
            Serial.println("done");
            state = !state;
        }
    }
}