#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // RX, TX

//підключаємо бібліотеки
  #include <DFPlayer_Mini_Mp3.h> // Бібліотека МП3хи
    
     boolean q_sunduk_done = 0; // флаг, що сундук відстукав
     int dotDuration = 200; //dot duration time

     byte micPin = A0;        // PIN MICROPHONE

     int threshold = 150;
     boolean listenFlag = false;
     boolean w_open_sunduk = 0;
     
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




const uint8_t     PIN_direction_TX_RX = 2;  // указываем номер вывода arduino, к которому подключены выводы RE и DE конвертирующего модуля
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



void setup() 
{ 
  mySerial.begin(9600);                     // скорость софт Сериал
  
  
  
  mp3_set_serial (mySerial);                //   софтовый серийный порт для мп3
  delay (100);                              //  обязательная задержка между командами
  mp3_set_volume (20);
  
  pinMode(micPin,INPUT);                    // порт микрофона


  
  pinMode(Svet,OUTPUT);                     //   настраиваем порт на выход для подсветки
  digitalWrite(Svet, LOW);                  // выключаем подсветку

 // pinMode(Dat,INPUT_PULLUP);              //   настраиваем порт на вход   для датчика
  
  Serial.begin(9600);                       // открываем последовательный порт на скорости 9600 бод

  pinMode(stp, OUTPUT);                      // управление шаговым движком
  pinMode(dir, OUTPUT);                      // пин управления напрвланием вращения
  pinMode(enable,OUTPUT);                    // для свободного вращения вала ШД
  digitalWrite(enable,LOW); 

 
}

void loop() 
{
    
if(isLineReady())             // есть готовая строка?
{ 
        if(startsWith(input_buff,"Master_Radio1_on"))    // строка на которую среагирует устройство
                {
     Serial.println("Command OK");                       //      для отладки
          state1();                                      //   ОСНОВНАЯ ФУНКЦИЯ-СЦЕНАРИЙ ВСЕГО УСТРОЙСТВА 
        if(Serial.available()>0)                         // если в последовательном порту есть данные для чтения, то ...
        {                  
   Serial.write(Serial.read());
        }
    
        }
  }
}    




    
void state1()
{
  //  int i = 0;
   //--------------------------------------

   digitalWrite(Svet,HIGH);                 // ВКЛЮЧАЕМ ПОДСВЕТКУ 
   Serial.println("SVET ON");               // для отладки
   delay (100);
   mp3_play (1);                            // Произрываем "mp3/0001.mp3"
   dvizhok ();                              //   обороты ручкой частоты и мигание подсветкой 
   delay (8500);                            // длинна первого трека -(необходимо изменить) -  ?
   digitalWrite(enable, HIGH);              //  сключаем свободное вращение ручки частоты
   mp3_play (2);                            // Произрываем "mp3/0002.mp3"
   delay(3000);
   while(1)                                 // бесконечный цикл 
   { Serial.println("SVET 1ON");
   sunduk();
   //-----------------------------
            if(q_sunduk_done == 1) // якщо завдання 3 виконане
              { Serial.println("SVET 2ON");
                while(w_open_sunduk == 0) // [щоб виконувалося 1 раз]
                  {
                    open_sunduk(); //відкрити сундук
                    w_open_sunduk++;
                  }
              }
    //----------------------------
    if(isLineReady())             // есть готовая строка?
{ 
        if(startsWith(input_buff,"Master_Radio1_on"))    // строка на которую среагирует устройство
                {
     Serial.println("Command OK");                              //      для отладки
          //state1();
                   if(Serial.available()>0)                   // если в последовательном порту есть данные для чтения, то ...
        {                  
   Serial.write(Serial.read());
        }
            }
  }
    //----------------------------          
   }
}

//=============================================//
// ФУНКЦИЯ ЧТЕНИЯ СТРОК//
bool isLineReady(){         
  static byte inputBuffIndex=0;
  if (Serial.available()){
    byte t = Serial.read();
      switch(t){
  case '\n':
  input_buff[inputBuffIndex] = 0; 
        inputBuffIndex=0; 
        return true; 
  break;
  case '\r':
        break;
         default:
          if (inputBuffIndex < INPUT_BUF_SIZE){
          input_buff[inputBuffIndex] = t; 
          inputBuffIndex++;
         }  
      }
  }
  return false;
}

bool startsWith (char* inputString, char* prefix) {
    return (strstr(inputString, prefix) - inputString) == 0;
}









//=================================================================//

void sunduk()
  {
    if(q_sunduk_done == 0)
      {
        say();
        delay(50);
        listen();
      }
  }
 //тіло проги "сундук мертвеца"

    
  void say()
  {
    //set led state
    String sayString = encode("O"); // codeword: "tuk tuk tuk"
    Serial.println(sayString);
    for(int i=0;i<=sayString.length();i++)
    {
      switch(sayString[i])
      {
      case '.': //dot
        mp3_set_serial(Serial);
        mp3_set_volume(20);
        mp3_play(55); //Файл тук короткий
        delay(dotDuration);
        delay(dotDuration);
      break;
      case '-': //dash
        mp3_set_serial(Serial);
        mp3_set_volume(20);      
        mp3_play(55); //Файл тук довгий
        delay(dotDuration*3);
        delay(dotDuration);
      break;
      //case ' ': //gap
      //  delay(dotDuration);
      }
    } 
  }

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

  String decode(String morse)
  {
    String msg = ""; 
    int lastPos = 0;
    int pos = morse.indexOf(' ');
    while( lastPos <= morse.lastIndexOf(' ') )
    {    
      for( int i = 0; i < sizeof MorseMap / sizeof *MorseMap; ++i )
      {
        if( morse.substring(lastPos, pos) == MorseMap[i].code )
        {
          msg += MorseMap[i].letter;
        }
      }
      lastPos = pos+1;
      pos = morse.indexOf(' ', lastPos);
      
      // Handle white-spaces between words (7 spaces)
      while( morse[lastPos] == ' ' && morse[pos+1] == ' ' )
      {
        pos ++;
      }
    }
    return msg;
  } 
   void listen()
  {
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
        delay(50);
        knockFlag = true;
        diff = millisNow-millisPrew;      
        Serial.print("diff = ");
        Serial.println(diff);
        mp3_set_serial(Serial);
        mp3_set_volume(40);
        mp3_play(66);
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
    Serial.println("Listen string is:");
    Serial.println(listenString);
    String cmpString = "--"; // 
    boolean  result=(listenString == cmpString);
    Serial.print("cmp_q_sunduk_done ");
    Serial.println(result);
    if (result)
    {
       q_sunduk_done = 1;
    }
  }
//=================================================================//



void open_sunduk()
  {
    mp3_set_serial(Serial);
    mp3_set_volume(20);
    mp3_play(61);// fx sunduk opening

   // digitalWrite(rel_sunduk, LOW);
    //digitalWrite(rel_lampa, LOW);
  }
//=======================================================//
void dvizhok ()
{
while(a<280)                       //  ШД делает пару оборотов(280) в сторону
{ 
  
    a++;
    digitalWrite(stp, HIGH);
    
    digitalWrite(Svet, LOW);
    delayMicroseconds(12200);
    digitalWrite(stp, LOW);
    
     digitalWrite(Svet, HIGH);
    delayMicroseconds(12200);
  }
 a= 0;
 delay(1200);
while(b<220)                             //  и в обратную  
{ b++;
   digitalWrite(dir, HIGH);               // меняет направление ШД

    
    digitalWrite(stp, HIGH);
     digitalWrite(Svet, LOW);
    delayMicroseconds(12200);
    digitalWrite(stp, LOW);
     digitalWrite(Svet, HIGH);
    delayMicroseconds(12200);
  }
  b=0;
    digitalWrite(dir, LOW);
    delay(1000);
//--------------------------//
while(a<180)                       //  повторяем движения ручки
{ 
  
    a++;
    digitalWrite(stp, HIGH);         
     digitalWrite(Svet, LOW);
    delayMicroseconds(15200);       // нужно поиграться с делей   , для безшумности движка
    digitalWrite(stp, LOW);
     digitalWrite(Svet, HIGH);
    delayMicroseconds(15200);
  }
 a= 0;
 delay(1100);
while(b<140)                             //  и в обратную для фиксации 
{ b++;
   digitalWrite(dir, HIGH);               // меняет направление ШД

    
    digitalWrite(stp, HIGH);
     digitalWrite(Svet, LOW);
    delayMicroseconds(8800);
    digitalWrite(stp, LOW);
     digitalWrite(Svet, HIGH);
    delayMicroseconds(8800);
  }
  b=0;
    digitalWrite(dir, LOW);
    
}
