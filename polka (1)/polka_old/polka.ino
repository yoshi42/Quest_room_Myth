




const uint8_t     PIN_direction_TX_RX = 9;  // указываем номер вывода arduino, к которому подключены выводы RE и DE конвертирующего модуля
const uint8_t     Zamok               = 7;  // защелка
const uint8_t     Dat                 = 6;  // датчик - концевик
byte              state = 0;

/// buffer[100];
//byte state2 = 0;
#define           INPUT_BUF_SIZE 40 // размер входного буфера
char              input_buff[INPUT_BUF_SIZE+1]; // место под хранение входящих из серийного порта данных

int               stp = 4; //подключите 4 пин к step

int               dir = 5; //подключите 5 пин к dir  ,//используется для смены направления

int               a = 0;
int               b = 0;
int               c = 0;


void setup() 
{ 
  pinMode(Zamok,OUTPUT);                     //   настраиваем порт на выход замка
  digitalWrite(Zamok, HIGH);                 // включаем замок

  pinMode(Dat,INPUT_PULLUP);                 //   настраиваем порт на вход   для датчика
  
  Serial.begin(9600);                        // открываем последовательный порт на скорости 9600 бод
digitalWrite(PIN_direction_TX_RX,LOW);
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
 pinMode(13, OUTPUT);
 Serial.println("++==++");
}

void loop() 
{
//  int d=0;
//    if( Serial.available() ){
//        delay(5);
//       //  state1();
//       // Serial.println("++==++");
//        while( Serial.available() ){
//             input_buff[d++] = Serial.read();
//        }
//        if(d>0){
//            input_buff[d++]='\0';
//            if( !strcmp( input_buff, "Master_ShoeRack1_180deg") ){
//               // digitalWrite(13, state2);
//              //  state2 = !state2;
//                Serial.print("++==++");
//                 state1();
//            }
//        }
//    }
//}

//=========================================
if(isLineReady())             // есть готовая строка?
{ 
        if(startsWith(input_buff,"Master_ShoeRack1_180deg"))    // строка на которую среагирует устройство
        
        {
     Serial.println("Command OK");                              //      для отладки
  
        state1();
        
              if(Serial.available()>0)                   // если в последовательном порту есть данные для чтения, то ...
        {                  
   Serial.write(Serial.read());
        }
    
        }
  }
}    


//  ////   Serial.println(digitalRead(Dat));
//  if (Serial.available()) 
//     {
//   Serial.println("Command OK");
//       Oborot = Serial.read();
//    // Serial.write(Oborot);
//       if( Oborot  == 'c')                      // если в последовательном порту есть данные для чтения, то ...
//       {     Serial.println("Command ddOK");
//        //Serial.write(stringOne);  
//       state1();
//       }
//   }




    
void state1()
{int i = 0;
   //--------------------------------------
Serial.println("++==++");
   digitalWrite(Zamok,LOW);                 //отключаем замок
   delay(200);  
Serial.println(digitalRead(Dat));
digitalWrite(dir,HIGH);

while(c<30)                       //  сработал датчик и ШД делает пару оборотов в ту же сторону
{ 
  
    c++;
    digitalWrite(stp, HIGH);
    delayMicroseconds(2200);
    digitalWrite(stp, LOW);
    delayMicroseconds(2200);
  }
 c= 0;
 delay(500);
  
    
while(digitalRead(Dat)==1)         //  включается ШД и работает пока не сработает датчик
{digitalWrite(dir,HIGH);
  
    
    digitalWrite(stp, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stp, LOW);
    delayMicroseconds(1500);
  }
delay(500);
while(a<100)                       //  сработал датчик и ШД делает пару оборотов в ту же сторону
{ 
  
    a++;
    digitalWrite(stp, HIGH);
    delayMicroseconds(2200);
    digitalWrite(stp, LOW);
    delayMicroseconds(2200);
  }
 a= 0;
 delay(500);
while(b<176)                             //  и в обратную для фиксации 
{ b++;
   digitalWrite(dir, LOW);               // меняет направление ШД

    
    digitalWrite(stp, HIGH);
    delayMicroseconds(2200);
    digitalWrite(stp, LOW);
    delayMicroseconds(2200);
  }
  b=0;
    digitalWrite(dir, HIGH);
    digitalWrite(Zamok,HIGH);                 //включаем замок 
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
