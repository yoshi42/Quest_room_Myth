#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h> // Бібліотека МП3хи

//SoftwareSerial mySerial(3, 4); // RX, TX

#define SSerialRX        7  //Serial Receive pin
#define SSerialTX        3  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control


#define mp3SerialTX        4  //Serial Transmit pin
#define mp3SerialRX        5  //Serial Receive pin

#define RS485Transmit    HIGH
#define RS485Receive     LOW


SoftwareSerial mp3Serial(mp3SerialRX, mp3SerialTX); // RX, TX

String string0 = "Master_Radio1_on_ru#";
String string1 = "Master_Radio1_on_en#";
String string2 = "Master_Radio1_on_heb#";
String stringgood = "Slave_Radio1_goodKnock";

String string;


//змінні на завдання зі стуком
unsigned long time0 = 0;
int dotDuration = 200; //dot duration time
byte micPin = A0;        // PIN MICROPHONE
int threshold = 150;
boolean listenFlag = false;
boolean knock_run_flag = true;
     
//Створюємо таблицю морзе для декодера-енкодера
  static const struct {const char letter, *code;} MorseMap[] =
  {
    { 'A', ".-" },
    { 'B', "-..." },
    { 'C', "-.-." },
    { 'D', "-.." },
    { 'E', "." },
    { 'F', "..-." },
    { 'G', "--." },
    { 'H', "...." },
    { 'I', ".." },
    { 'J', ".---" },
    { 'K', ".-.-" },
    { 'L', ".-.." },
    { 'M', "--" },
    { 'N', "-." },
    { 'O', "---" },
    { 'P', ".--." },
    { 'Q', "--.-" },
    { 'R', ".-." },
    { 'S', "..." },
    { 'T', "-" },
    { 'U', "..-" },
    { 'V', "...-" },
    { 'W', ".--" },
    { 'X', "-..-" },
    { 'Y', "-.--" },
    { 'Z', "--.." },
    { ' ', "     " }, //Gap between word, seven units 
      
    { '1', ".----" },
    { '2', "..---" },
    { '3', "...--" },
    { '4', "....-" },
    { '5', "....." },
    { '6', "-...." },
    { '7', "--..." },
    { '8', "---.." },
    { '9', "----." },
    { '0', "-----" },
      
    { '.', ".-.-.-" },
    { ',', "--..--" },
    { '?', "..--.." },
    { '!', "-.-.--" },
    { ':', "---..." },
    { ';', "-.-.-." },
    { '(', "-.--." },
    { ')', "-.--.-" },
    { '"', ".-..-." },
    { '@', ".--.-." },
    { '&', ".-..." },
  };

 
//===========================================//


const uint8_t     Svet               = 9;  //  podsvetka
//const uint8_t     Dat                 = 6;  // датчик - концевик
byte              state = 0;


#define           INPUT_BUF_SIZE 30 // размер входного буфера
char              input_buff[INPUT_BUF_SIZE+1]; // место под хранение входящих из серийного порта данных

int               stp = 13; //подключите 4 пин к step
int               dir = 12; //подключите 5 пин к dir  ,//используется для смены направления

int               enable = 11; //подключите 5 пин к dir  ,//используется для смены направления

int               a = 0;  // переменная для шагов двигателя в одну сторону
int               b = 0;  // переменная для шагов двигателя в другую сторону
int 			  p = 0;

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
void setup() 
{ 
 // mySerial.begin(9600);                     // скорость софт Сериал
  
	mp3_set_serial(mp3Serial);                //   софтовый серийный порт для мп3
	delay (100);                              //  обязательная задержка между командами
	mp3_set_volume (30);

	pinMode(micPin,INPUT);                    // порт микрофона

	pinMode(Svet,OUTPUT);                     //   настраиваем порт на выход для подсветки
	// digitalWrite(Svet, LOW);                  // выключаем подсветку

	// pinMode(Dat,INPUT_PULLUP);              //   настраиваем порт на вход   для датчика

	Serial.begin(9600);                       // открываем последовательный порт на скорости 9600 бод
	
	mp3Serial.begin(9600);

	pinMode(SSerialTxControl, OUTPUT);
	digitalWrite(SSerialTxControl, LOW);
        RS485Serial.begin(9600);
	pinMode(stp, OUTPUT);                      // управление шаговым движком
	pinMode(dir, OUTPUT);                      // пин управления напрвланием вращения
	pinMode(enable,OUTPUT);                    // для свободного вращения вала ШД
	digitalWrite(enable,LOW); 

 
}

void loop() 
{
  if(RS485Serial.available()) 
  {
      delay(100);
       tx(); 
  }

  if (!knock_run_flag)
      {
        knock();
        delay(100);
        listen();
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
        mp3_play (6);                            // Произрываем "mp3/0006.mp3"  ефект помєхи
        dvizhok ();                              //   обороты ручкой частоты и мигание подсветкой
        stat(1);
      }
      if (string.equals(string1))
      {
        
        p=1;
        time0=millis();
        mp3_play (6);                            // Произрываем "mp3/0006.mp3"  ефект помєхи
        dvizhok (); 
        stat(2);
      }
      if (string.equals(string2))
      {
        
        p=1;
        time0=millis();
        mp3_play (6);                            // Произрываем "mp3/0006.mp3"  ефект помєхи
        dvizhok (); 
        stat(3);
      }

      string = "";
    }

  }
  loop();
}

void stat(int s)
{
    //Serial.println(millis());
    //Serial.println(time0);
   //delay (5000); 
  
    if(s==1){
    mp3_play (1);                            // Произрываем "mp3/0001.mp3"  ru
    delay(35000);                            //ждем пока отыграет трек
    knock_run_flag = false;
    }

     if(s==2){
    mp3_play (2);                            // Произрываем "mp3/0002.mp3"  en
    delay(32000);                            //ждем пока отыграет трек
    knock_run_flag = false;
    }

     if(s==3){
    mp3_play (3);                            // Произрываем "mp3/0003.mp3"  heb
    delay(31000);                            //ждем пока отыграет трек
    knock_run_flag = false;
    }
}
    
void dvizhok ()
{
while(millis()-time0<3000)                       //  ШД делает пару оборотов(280) в сторону
{ 
    digitalWrite(dir, LOW);
    digitalWrite(stp, HIGH);
    
    digitalWrite(Svet, LOW);
    delayMicroseconds(12200);
    digitalWrite(stp, LOW);
    
     digitalWrite(Svet, HIGH);
    delayMicroseconds(12200);
  }
while(millis()-time0>3000 && millis()-time0<6000)                             //  и в обратную  
{
   digitalWrite(dir, HIGH);               // меняет направление ШД

    
    digitalWrite(stp, HIGH);
     digitalWrite(Svet, LOW);
    delayMicroseconds(12200);
    digitalWrite(stp, LOW);
     digitalWrite(Svet, HIGH);
    delayMicroseconds(12200);
  }
   
}
//=================================================================//

void knock()
{
        mp3_set_serial(mp3Serial);
        mp3_set_volume(30);
        mp3_play(4); //Файл тук
        delay(dotDuration*4);
        mp3_stop();

        mp3_set_serial(mp3Serial);
        mp3_set_volume(30);
        mp3_play(4); //Файл тук
        delay(dotDuration*4);
        mp3_stop();
        
        mp3_set_serial(mp3Serial);
        mp3_set_volume(30);
        mp3_play(4); //Файл тук
        delay(dotDuration*4);
        mp3_stop();
}

  /*void say()
  {
    //set led state
    String sayString = encode("I"); // codeword: "tuk tuk tuk"
    Serial.println(sayString);
    for(int i=0;i<=sayString.length();i++)
    {
      switch(sayString[i])
      {
      case '.': 
      	//dot
        mp3_set_serial(mp3Serial);
        mp3_set_volume(30);
        mp3_play(4); //Файл тук короткий
        delay(dotDuration);
        delay(dotDuration);
      break;
      case '-': //dash
        mp3_set_serial(mp3Serial);
        mp3_set_volume(30);      
        mp3_play(4); //Файл тук довгий
        delay(dotDuration*3);
        delay(dotDuration);
      break;
      //case ' ': //gap
      //  delay(dotDuration);
      }
    } 
  }*/

  String encode(const char *string)
  {  
    size_t i, j;
    String morseWord = "";
    for( i = 0; string[i]; ++i )
    {
      for( j = 0; j < sizeof MorseMap / sizeof *MorseMap; ++j )
      {
        if( toupper(string[i]) == MorseMap[j].letter )
        {
          morseWord += MorseMap[j].code;
          break;
        }
      }
      //morseWord += " "; //Add tailing space to seperate the chars
    }
    return morseWord;
  }

   void listen()
  {
  	mp3_set_serial(Serial);
    unsigned long millisNow = 0;
    unsigned long millisPrew = 0;
    boolean knockFlag = false;
    boolean first = true;
    String listenString = "";
    long diff = 0;
    for (int i = 0;i<=2500;i++)
    {
      if (analogRead(micPin)>=200) //налаштування чутливості мікрофону
      {
        if (first)
        {
          first = false;
          millisNow = millis();
          millisPrew = millisNow;
        }
        millisPrew = millisNow;
        millisNow = millis();   
        delay(50); //debounce
        knockFlag = true;
        diff = millisNow-millisPrew;      
        Serial.print("diff = ");
        Serial.println(diff);

        digitalWrite(Svet, LOW); // сигнализация о стуке
        delay(100);
        digitalWrite(Svet, HIGH);
      }

      if ((diff>=dotDuration*2-threshold)&&(diff<=dotDuration*2+threshold)&&knockFlag)
      {
        listenString=listenString+'.';
        knockFlag = false;
        millisPrew = millisNow;
      }
      if ((diff>=dotDuration*4-threshold)&&(diff<=dotDuration*4+threshold)&&knockFlag)
      {

        listenString=listenString+'-';
        knockFlag = false;
        millisPrew = millisNow;
      }
    delay(2);
    }
    Serial.println("Listen string is: ");
    Serial.println(listenString);
    String cmpString = "--"; // 
    boolean  result=(listenString == cmpString);
    Serial.print("cmp_q_sunduk_done ");
    Serial.println(result);
    if (result)
    {
      digitalWrite(SSerialTxControl, HIGH);
      RS485Serial.println(stringgood);
      delay(50);
      digitalWrite(SSerialTxControl, LOW);
      knock_run_flag = true;
    }
  }
//=================================================================//
