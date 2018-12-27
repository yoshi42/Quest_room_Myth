const uint8_t     TX                  = 12;  // защелка
const uint8_t     Zamok               = 7;  // защелка

const uint8_t     DatHol              = 4;  // датчик магнита
const uint8_t     DatGerk             = 5;  // датчик дверь

const uint8_t     ColorR              = 11;  // диммер красного цвета лента 1
const uint8_t     ColorG              = 10;  // диммер зеленого цвета лента 1
//const uint8_t     ColorB            = 11;  // диммер

const uint8_t     ColorRn             = 9;  // диммер  красный лента 2
const uint8_t     ColorGn             = 6;  // диммер зеленый лента 2

const uint8_t     Dym                 = 8;  // дым машина

int                finish  = 0 ; 

long previousMillis = 0;           // храним время последнего переключения светодиода
 
long interval = 100000;           // интервал между включение/выключением светодиода (1 секунда)


#define           INPUT_BUF_SIZE 30 // размер входного буфера
char              input_buff[INPUT_BUF_SIZE+1]; // место под хранение входящих из серийного порта данных

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(TX,OUTPUT);                       // TX RX - 485 

pinMode(ColorR,OUTPUT);                   // PWM R
pinMode(ColorG,OUTPUT);                   // PWM G

pinMode(ColorRn,OUTPUT);                  // PWM R
pinMode(ColorGn,OUTPUT);                  // PWM G


//pinMode(ColorB,OUTPUT);                 // PWM B
//analogWrite(ColorB, 0);     // 

pinMode(Dym,OUTPUT);                      //Dym

pinMode(DatHol,INPUT_PULLUP);             // datchik Hola
pinMode(DatGerk,INPUT_PULLUP);            // datchik Hola
Serial.println(digitalRead(DatHol));
Serial.println(digitalRead(DatGerk));

pinMode(Zamok,OUTPUT);                    // zamok нужно   поменять  хай и лов -  для правильности открытия закрытия
digitalWrite(Zamok,HIGH);                 // уровень ХАЙ  открывает, нам нужно на старте закрыть
}


void loop() {
  
long x = 0 ; 
if(isLineReady())
{ // есть готовая строка?
        if(startsWith(input_buff,"Slave_Burzh_good"))      //  команда в серийный порт для выполнения сценария функции 
        
        {
     Serial.println("Command OK");
     Serial.println("Command OK my 1");
     Serial.println( "");
        state1();                                         // ОСНОВНАЯ ФУНКЦИЯ СЦЕНАРИЙ 
              if(Serial.available()>0)
        {                                                 // если в последовательном порту есть данные для чтения, то ...
   Serial.write(Serial.read());
        }
    
        }
  }

  
  // put your main code here, to run repeatedly:

if(finish == 2)                                   // РАБОТА ПОДСВЕТКИ ПОСЛЕ ВЫПОЛНЕНИЯ СЦЕНАРИЯ
{
 fire();                                          // ЛЕНТА 1
 fire1();                                         // ЛЕНТА 2
}




}


// ============================================//
void fire()   //  имитация горящей свечи
  { 
    analogWrite(ColorR, random(120)+135);
    analogWrite(ColorG, random(120)+0);
    delay(random(100));
  }
  //============================================//


void clearLed() // ВЫКЛЮЧЕНИЕ ПОДСВЕТКИ
{
  analogWrite(11,0);
  analogWrite(10,0);
  analogWrite(9,0);
  analogWrite(6,0);
  }  

  //=====================================
  bool isLineReady()
  {
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


//=================================================//


// ============================================//
void fire1()   //  имитация горящей свечи
  { 
    analogWrite(ColorRn, random(120)+135);
    analogWrite(ColorGn, random(120)+0);
    delay(random(100));
  }
  //============================================//

//=================================================//

void state1()
{ 
  long timenow= millis();
Serial.println(millis());
Serial.println(timenow);

while((millis()-timenow)<500)  // ВКЛЮЧАЕМ  ДЫМ НА 0,5 СЕК 
   { Serial.println(millis()-timenow);
    fire();                     // ПОДСВЕТКА  1
    digitalWrite(Dym,HIGH);     // вкл дым
   }
    fire();
    digitalWrite(Zamok,LOW);     //  поменять на хай( открыть замок)
    digitalWrite(Dym,LOW);
    Serial.println("zamok low and zamok");
    //clearLed();
     // delay(3000);
//----------------------------------------------------------------
   while(finish==0)
   {  fire();
   
      if(digitalRead(DatHol)==0&&digitalRead(DatGerk)==0)  // если дневник внутри и если дверца закрыта 
      { 
         Serial.println("dat4iki vporyade");
      //1.  // otpravka signala na OSU
      long timenow1= millis();
      while((millis()-timenow1)<2000)                     //  дым на 2 сек 
      {finish= 1;
        digitalWrite(Dym,HIGH);
        fire1();
        
        unsigned long currentMillis = millis();
        
            // clearLed();
             digitalWrite(Dym,LOW);
             Serial.println("dnevnik vnutri ");
        fire();
        fire1();
     }
     
        
        
   }
   finish = 2;
  
//----------------------------------------------------------------- 


}
