#include <DFPlayer_Mini_Mp3.h>

#include <SoftwareSerial.h>

int SSerialTxControl = 40;   //RS485 Direction control

//=============================KОМАНДЫ=================================
String Master_Heart_on = "Master_Heart_on#";                    //серце
String Master_Heart_1 = "Master_Heart_1#";
String Master_Heart_2 = "Master_Heart_2#";
String Master_Heart_3 = "Master_Heart_3#";
String Master_Heart_dead = "Master_Heart_dead#";
String Master_Heart_off = "Master_Heart_off#";
String Master_Heart_open = "Master_Heart_open#";

String Master_Photos1_on = "Master_Photos1_on#";                  // фоторамKи
String Master_Photos1_change = "Master_Photos1_change#";
String Master_Photos1_back = "Master_Photos1_back#";
String Master_Photos1_off = "Master_Photos1_off#";
String Master_Photos2_change = "Master_Photos2_change#";
String Master_Photos2_back = "Master_Photos2_back#";

String Master_ShoeRack1_180deg="Master_ShoeRack1_180deg#";          //полKи
String Master_ShoeRack2_180deg="Master_ShoeRack2_180deg#";

String Master_Window1_on_vid1 = "Master_Window1_on_vid1#";          //оKна-Kалендари
String Master_Window1_vid2 = "Master_Window1_vid2#";
String Master_Window1_off = "Master_Window1_off#";
String Master_Window2_on_vid1 = "Master_Window2_on_vid1#";
String Master_Window2_vid2 = "Master_Window2_vid2#";
String Master_Window2_vid3 = "Master_Window2_vid3#";
String Master_Window2_off = "Master_Window2_off#";
String Master_Window2_pass = "Master_Window2_pass#";

String Master_Radio1_on_ru = "Master_Radio1_on_ru#";                //радиолы
String Master_Radio1_on_en = "Master_Radio1_on_en#";
String Master_Radio1_on_heb = "Master_Radio1_on_heb#";
String Master_Radio2_on_ru = "Master_Radio2_on_ru#";
String Master_Radio2_on_en = "Master_Radio2_on_en#";
String Master_Radio2_on_heb = "Master_Radio2_on_heb#";

String Master_Phone2_start = "Master_Phone2_start#";                 //телефон
String Master_Phone2_ring = "Master_Phone2_ring#";
String Master_Phone2_off = "Master_Phone2_off#";

String Master_mirror_ru = "Master_mirror_ru#";                        //зерKало+теKст под обоями
String Master_mirror_en = "Master_mirror_en#";
String Master_mirror_heb = "Master_mirror_heb#";

String Master_hands1_on = "Master_hands1_on#";                        //Kартины с руKами
String Master_hands2_on = "Master_hands2_on#";

String Master_Burzh_on = "Master_Burzh_on#";                         //буржуйKа
String Master_Burzh_off = "Master_Burzh_off#";
String Master_Burzh_open = "Master_Burzh_open#";

String Master_Maski_on = "Master_Maski_on#";                        //масKи майя

String Master_Lampa_on = "Master_Lampa_on#";                        //лампа джойстиK + KлетKа
String Master_Lampa_start = "Master_Lampa_start#";
String Master_Lampa_off = "Master_Lampa_off#";
String Master_Lampa_open1 = "Master_Kletka_open#";
String Master_Lampa_open2 = "Master_Kletka_open2#";

String Master_Projector_on = "Master_Projector_on#";                  //проеKтор
String Master_Projector_start1 = "Master_Projector_start1#";
String Master_Projector_stop = "Master_Projector_stop#";
String Master_Projector_start2 = "Master_Projector_start2#";
String Master_Projector_off = "Master_Projector_off#";

String Master_Light_on = "Master_Light_on#";                          //управление светом
String Master_Light_kor1 = "Master_Light_kor1#";
String Master_Light_kor2 = "Master_Light_kor2#";
String Master_Light_kor3 = "Master_Light_kor3#";
String Master_Light_kor4 = "Master_Light_kor4#";
String Master_Light_office = "Master_Light_office#";
String Master_Light_off = "Master_Light_off#";
String Master_Light_rele1 = "Master_Light_rele1#";         //дим машина
String Master_Light_rele2 = "Master_Light_rele2#";
String Master_Light_rele3 = "Master_Light_rele3#";
//=================================================================================================

//========================ОТВЕТЫ================================

String Slave_Heart_itemInside = "Slave_Heart_itemInside#";            //серце

String Slave_Photos1_goodParole = "Slave_Photos1_goodParole#";        //фоторамKи-KнопKи
String Slave_Photos1_badParole = "Slave_Photos1_badParole#";

String Slave_Window2_good = "Slave_Window2_good#";                    //оKно-Kаленда
String Slave_Window2_bad = "Slave_Window2_bad#";

String Slave_Radio1_goodKnock = "Slave_Radio1_goodKnock#";            //радиола

String Slave_Phone2_good = "Slave_Phone2_good#";                      //телефон

String Slave_Burzh_goode = "Slave_Burzh_good#";                       //буржуйKа

String Slave_Maski_good = "Slave_Maski_good#";                        //масKи майя
String Slave_Maski_bad = "Slave_Maski_bad#";  

String Slave_Lampa_good = "Slave_Lampa_good#";                        //лампа джойстиK + KлетKа
String Slave_Lampa_bad = "Slave_Lampa_bad#";
//=================================================================

//====================КОМАНДЫ С ПУЛЬТА=============================
String Console_1 = "1#";
String Console_2 = "2#";
String Console_3 = "3#";
String Console_4 = "4#";
String Console_5 = "5#";
String Console_6 = "6#";
String Console_7 = "7#";
String Console_8 = "8#";
String Console_9 = "9#";
String Console_0 = "0#";
String Console_A = "A#";
String Console_B = "B#";
String Console_C = "C#";
String Console_D = "D#";
String Console_E = "E#";
String Console_F = "F#";
String Console_G = "G#";
String Console_H = "H#";
String Console_I = "I#";
String Console_J = "J#";
String Console_radioA = "radioA#";
String Console_radioB = "radioB#";
String Console_radioC = "radioC#";
String Console_radioD = "radioD#";
String Console_reset = "reset#";
String Console_start = "start#";
String Console_ru = "ru#";
String Console_en = "en#";
String Console_heb = "heb#";
String Console_res1 = "_res1#";
String Console_res2 = "_res2#";


//=================================================================

String string;
String string_reply;

//=======================ВЫВОДЫ С ОСУ==============================
int K12_stolik_lock = 13;         //столиK под радиолу
int K4_tel_sol = 12;             //телефон 1
int K8_balls_lock = 11;          //замоK шара в стене
int K9_balls_sol = 10;           //соленоид шара
int S2_viselitsa = 23;           //вход от виселицы
int K16_cal_maya_lock = 9;        //замоK Kалендаря майя
int K5_balka1 = 8;               //Падающая часть потолKа
int K6_balka2 = 7;               //------//------
int K7_balka3 = 6;               //------//------
int K2_doors1 = 5;               //Двери в офис - 12В ЕМЗ двери
int K3_doors1_led = 4;           //подсветKа  - 12В LED лампа
int K10_doors2 = 3;
int K11_doors2_led = 2;           // - 12В LED лампа
int K1_stenka_k0k1 = 32;         //фальш стенKи - 12В стенKаKух-K1
int K15_stenka_k2of = 34;         //- 12B стенKаK2-Оф
int K16_stenka_k0of = 36;         //- 12В стенKа Kух-Оф
int K17_stenka4_k2ex = 38;        //- 12 стенKа K2-Вых
int S1_vikl = 25;               //вход от выKлючателя
int S3_led = 29;                //5В светодиод
int SSTxD22_pl_music = 22;    //
int SSRxD24_pl_music = 24;    //- плеер музыKа
int K18_kor1_mute = 26;           //
int K19_kor2_mute = 28;           //
int K20_off_mute = 30;            //- выводы на mute
int K13_XO_lock = 27;             //- 12В на замоK Kартины KрестиKи-нолиKи
int stroboscope1 = 31;            // стробоскоп 
int stroboscope2 = 33;
int sens1_doors1 = 40;            //геркон на двери 1
int sens1_doors2 = 42;            //геркон на двери 2
int sens2_doors1 = 44;            //датчик движения двери 1
int sens2_doors2 = 44;            //датчик движения двери 2
//==============================================================================


//=========================ФЛАГИ==========================
int flag = 0;                    //флаг последовательности
int language = 0;
int flag_final = 0;
int flag_photo_bad = 0;         //флаг фоторамки-кнопки
int flag_photo_good = 0;
int flag_radiola = 0;           
int flag_window_good = 0;
int flag_window_bad = 0;
int flag_stroboscope = 0;
int flag_XO_good = 0;
int flag_XO_bad = 0;
int flag_phone_good = 0;
int flag_lampa_start = 0;
int flag_lampa_bad = 0;
int flag_lampa_good = 0;
int flag_maski_bad = 0;
int flag_maski_good = 0;
int flag_heart = 0;
int flag_burzh_good = 0;
int flag_reset = 0;
//========================================================

unsigned long time_viselitsa = 0;
unsigned long time_stroboscope = 0;
unsigned long time_phone = 0;

SoftwareSerial pl_musicSerial(SSRxD24_pl_music, SSTxD22_pl_music); // RX, TX плеер музыKа
void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);                      //RS485
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    pl_musicSerial.begin(9600);               //плеер музыKа
    Serial2.begin(9600);                      // плеер эффеKты+теKст
    mp3_set_serial (Serial2);                //   софтовый серийный порт для мп3
    delay (100);                              //  обязательная задержка между командами
    mp3_set_volume (30);
    pinMode(S2_viselitsa, INPUT_PULLUP); 
    pinMode(S1_vikl, INPUT_PULLUP); 
    pinMode(sens1_doors1, INPUT_PULLUP); 
    pinMode(sens2_doors1, INPUT); 
    pinMode(sens1_doors2, INPUT_PULLUP); 
    pinMode(sens2_doors2, INPUT); 
    pinMode(S3_led, OUTPUT);   
    pinMode(K12_stolik_lock, OUTPUT);          
    pinMode(K4_tel_sol, OUTPUT);
    pinMode(K8_balls_lock, OUTPUT);
    pinMode(K9_balls_sol, OUTPUT);
    pinMode(K16_cal_maya_lock, OUTPUT);
    pinMode(K5_balka1, OUTPUT);
    pinMode(K6_balka2, OUTPUT);
    pinMode(K7_balka3, OUTPUT);
    pinMode(K2_doors1, OUTPUT);
    pinMode(K3_doors1_led, OUTPUT);
  pinMode(K10_doors2, OUTPUT);
  pinMode(K11_doors2_led, OUTPUT);
  pinMode(K1_stenka_k0k1, OUTPUT);
  pinMode(K15_stenka_k2of, OUTPUT);
  pinMode(K16_stenka_k0of, OUTPUT);
  pinMode(K17_stenka4_k2ex, OUTPUT);
  pinMode(K18_kor1_mute, OUTPUT);
  pinMode(K19_kor2_mute, OUTPUT);
  pinMode(K20_off_mute, OUTPUT);
  pinMode(K13_XO_lock, OUTPUT);
    
    

}

void loop() {
  functionStart();
  if (Serial1.available()) {
    string_reply = "";
    delay(100);
    tx();
 }
 

}

void tx() {                          // розпізнання Kоманди по RS485
  digitalWrite(SSerialTxControl, LOW);
  while (Serial1.available())
  {
    char inChar = Serial1.read();
    string_reply += inChar;
    if (inChar == '#') 
    {
      if (string_reply.equals(Console_start)&& flag == 0)                                           //пришла команда start с пульта первый раз
      {
        flag = 1;
        string_reply = "";
      }
      if ((string_reply.equals(Console_start) || string_reply.equals(Console_radioA)) && flag == 1)      //пришла команда start с пульта второй раз или команда А с радио пульта
      {
        flag = 2 ;
      }
      if (string_reply.equals(Console_reset))
      {
        flag_reset = 1;
      }
      if (string_reply.equals(Console_ru))          //выбоз языка для квеста 
      {
        language = 1;
      }
      if (string_reply.equals(Console_en))
      {
        language = 2;
      }
      if (string_reply.equals(Console_heb))
      {
        language = 3;
      }
      if (string_reply.equals(Console_1))
      {
        
      }
      if (string_reply.equals(Console_2))
      {
        
      }
      if (string_reply.equals(Console_3))
      {
        flag_lampa_start=1;
      }
      if (string_reply.equals(Console_4))
      {
        flag_final = 1;
      }
      if (string_reply.equals(Console_5))
      {
        
      }
      if (string_reply.equals(Console_6))
      {
        
      }
      if (string_reply.equals(Console_7))
      {
        
      }
      if (string_reply.equals(Console_8))
      {
        
      }
      if (string_reply.equals(Console_9))
      {
        
      }
      if (string_reply.equals(Console_0))
      {
        
      }
      if (string_reply.equals(Console_A))
      {
        
      }
      if (string_reply.equals(Console_B))
      {
        
      }
      if (string_reply.equals(Console_C))
      {
        
      }
      if (string_reply.equals(Console_D))
      {
        
      }
      if (string_reply.equals(Console_E))
      {
        
      }
      if (string_reply.equals(Console_F))
      {
        
      }
      if (string_reply.equals(Console_G))
      {
        
      }
      if (string_reply.equals(Console_H))
      {
        
      }
      if (string_reply.equals(Console_I))
      {
        
      }
      if (string_reply.equals(Console_J))
      {
        
      }
      if (string_reply.equals(Console_radioB))
      {
        flag_stroboscope = 1;
      }
      if (string_reply.equals(Console_radioC))
      {
        flag_XO_bad = 1;
      }
      if (string_reply.equals(Console_radioD))
      {
        flag_XO_good = 1;
      }
      if (string_reply.equals(Console_res1))
      {
        
      }
      if (string_reply.equals(Console_res2))
      {
        
      }
      if (string_reply.equals(Slave_Heart_itemInside))
      {
        flag_heart = 1;
      }
      if (string_reply.equals(Slave_Photos1_goodParole))
      {
        flag_photo_good = 1;
      }
      if (string_reply.equals(Slave_Photos1_badParole))
      {
        flag_photo_bad = 1;
      }
      if (string_reply.equals(Slave_Window2_good))
      {
        flag_window_good = 1;
      }
      if (string_reply.equals(Slave_Window2_bad))
      {
        flag_window_bad = 1;
      }
      if (string_reply.equals(Slave_Radio1_goodKnock))
      {
        flag_radiola = 1;
      }
      if (string_reply.equals(Slave_Phone2_good))
      {
        flag_phone_good = 1;
      }
      if (string_reply.equals(Slave_Burzh_goode))
      {
        flag_burzh_good = 1;
      }
      if (string_reply.equals(Slave_Maski_good))
      {
        flag_maski_good = 1;
      }
      if (string_reply.equals(Slave_Maski_bad))
      {
        flag_maski_bad = 1;
      }
      if (string_reply.equals(Slave_Lampa_good))
      {
        flag_lampa_good = 1;
      }
      if (string_reply.equals(Slave_Lampa_bad))
      {
        flag_lampa_bad = 1;
      }
      
    string_reply = "";
    }

  }

}


void functionStart(){                                  
  digitalWrite(SSerialTxControl, LOW);

  if(flag==0){
    flag_reset = 0;
  }
  
  if(flag == 1){                                        //настройки перед запуском
    Serial1.println(Master_Projector_on);
    
  }

  //================================КУХНЯ===========================================
  if(flag == 2){                                          //начало игры
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    delay(50);                                            //нужно проверить нужна ли здесь задержка
    Serial1.println(Master_Projector_start1);             //включение проектора
    delay(100);                                           //нужно проверить нужна задержка между командами или нет
    Serial1.println(Master_Window1_on_vid1);              //включение телевизора в коридоре 1
    Serial1.println(Master_Window2_on_vid1);              //включение телевизора в коридоре 2
    delay(60000);                                         //задержка для просмотра видео
    Serial1.println(Master_Projector_stop);              //роектора на паузу
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);
    mp3_play (1);                                         //вкл плеєр з эффектами Слышен гул, шум, скрипы (НОМЕР УТОЧНИТЬ)
    flag=3;
  }
  if(flag == 3){
    digitalWrite(K1_stenka_k0k1, HIGH);                   //открывается дверь кух-к1 откр на 2сек (ПРОВЕРИТЬ ТA ЛИ ДВЕРЬ)
    delay(2000);
    digitalWrite(K1_stenka_k0k1, LOW);
    Serial1.println(Master_Projector_start2);             //включение проектора
    delay(60000);                                         //настроить задержку
    Serial1.println(Master_Projector_off);                //выключение проектора
    digitalWrite(K1_stenka_k0k1, HIGH);                   //открывается дверь кух-к1 откр на 2сек (ПРОВЕРИТЬ ТA ЛИ ДВЕРЬ)
    delay(2000);
    digitalWrite(K1_stenka_k0k1, LOW);
    digitalWrite(S3_led, HIGH);                           //Включается свет  s3_led над выключателем s1_switch
    flag=4;
  }
  //=================================КОРИДОР 1==========================================
  if(flag == 4){
    if(digitalRead(S1_vikl)==LOW){                         //включили выключатель
      digitalWrite(S3_led, LOW);                          //выкл свет над выключат
      Serial1.println(Master_Light_kor1);                 //вкл свет в коридоре 1
      Serial1.println(Master_Photos1_on);                 //активировать фоторамки
      flag=5;
    }
  }
  if(flag==5){
    if(flag_photo_bad == 1){                              //от фоторамок пришел сигнал bad
    digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);  
      if(language==1){                                    //в зависимости от языка прохождения вкл вкл плеер и эффектами аудио "нет не правильно" (НОМЕР УТОЧНИТЬ)
        mp3_play(0);
      }
      if(language==2){
        mp3_play(0);
      }
      if(language==3){
        mp3_play(0);
      }
      //- Запускається світловий ефект - мигання світла
      flag_photo_bad =0;
    }
    if(flag_photo_good == 1){                             //от фоторамок пришел сигнал good
      if(language==1){                                    //в зависимости от языка прохождения вкл радиола1
        Serial1.println(Master_Radio1_on_ru);
        flag=6;
      }
      if(language==2){
        Serial1.println(Master_Radio1_on_en);
        flag=6;
      }
      if(language==3){
        Serial1.println(Master_Radio1_on_heb);
        flag=6;
      }
    }
  }
  if(flag==6 && flag_radiola == 1){                   //если постучали в дверь
    digitalWrite(K11_doors2_led, HIGH);               //вкл подсветка над дверью2
    digitalWrite(K10_doors2, HIGH);                   //открывается дверь 2
    delay(2000);
    digitalWrite(K10_doors2, LOW);
    flag = 7;
  }
  if(flag == 7){
    while(digitalRead(sens1_doors2)==HIGH){           //пока дверь2 открыта
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);
      if(language==1){                                    //в зависимости от языка прохождения вкл плеер и эффектами аудио "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (2);
      }
      if(language==2){
        mp3_play (3);
      }
      if(language==3){
        mp3_play (4);
      }                                         
      delay(10000);                                         //ПОДОБРАТЬ ЗНАЧЕНИЕ
      //затухание света кор1
    }
    if(digitalRead(sens1_doors2)==LOW){                 //если дверь закрылась(ДОБАВИТЬ ДАТЧИК ДВИЖЕНИЯ)
      mp3_stop();
      flag = 8;
      
    }
  }
  //======================================КОРИДОР 2===========================================
  if(flag==8){
    //плавное включение света кор2
    Serial1.println(Master_Light_kor2);                 //вкл свет в коридоре 2
    delay(10000);
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    Serial1.println(Master_Photos1_change);               //фоторамки в коридоре 1 вниз
    Serial1.println(Master_ShoeRack1_180deg);             //полка в коридоре 1 перевернуть
    Serial1.println(Master_Window1_vid2);                 //в окне коридора 1 сменить видео
    digitalWrite(K18_kor1_mute, LOW);                     //выкл эфекты в кор1
    digitalWrite(K19_kor2_mute, HIGH);                     //вкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);                                 
    mp3_play (5);                                          // вкл плеєр с эффектами аудио " "кто-то бежит по втором этаже"" (НОМЕР УТОЧНИТЬ)
    delay(5000);
    digitalWrite(K5_balka1, HIGH);                         //выпадает 1 балка
    delay(5000);
    digitalWrite(K6_balka2, HIGH);                         //выпадает 2 балка
    delay(5000);
    digitalWrite(K7_balka3, HIGH);                         //выпадает 3 балка
    flag = 9;
  }
  if(flag == 9){
    time_viselitsa=millis();
    while(digitalRead(S2_viselitsa)==LOW){                //пока кнопка нажата
      if((millis()-time_viselitsa)>1000){                 //если держать больше 1с
        flag = 10;
        break;
      }
    }
  }
  if(flag==10){
    digitalWrite(K9_balls_sol, HIGH);                   // вкл соленоид на 5с
    delay(5000);
    digitalWrite(K9_balls_sol, LOW);
    delay(40000);                                       //задержку настроить
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    Serial1.println(Master_Phone2_ring);                  //звонит телефон 2
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);
      if(language==1){                                    //в зависимости от языка прохождения вкл плеер с эффектами аудио "он сошел с ума, спасите его" (НОМЕР УТОЧНИТЬ)
        mp3_play (6);
      }
      if(language==2){
        mp3_play (7);
      }
      if(language==3){
        mp3_play (8);
      }
      Serial1.println(Master_Window2_pass);             //вкл датчики на окне2
      flag = 11;
  }
  if(flag == 11){
    if(flag_window_bad == 1){
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);  
      if(language==1){                                    //в зависимости от языка прохождения вкл вкл плеер и эффектами аудио "нет не правильно" (НОМЕР УТОЧНИТЬ)
        mp3_play(0);
      }
      if(language==2){
        mp3_play(0);
      }
      if(language==3){
        mp3_play(0);
      }
      //- Запускається світловий ефект - мигання світла
      flag_window_bad = 0;
    }
    if(flag_window_good == 1){
      digitalWrite(K3_doors1_led, HIGH);               //вкл подсветка над дверью1
      digitalWrite(K2_doors1, HIGH);                   //открывается дверь 1
      delay(2000);
      digitalWrite(K2_doors1, LOW);
      flag = 12;
    }
  }
  if(flag == 12){
    while(digitalRead(sens1_doors1)==HIGH){           //пока дверь1 открыта
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);
      if(language==1){                                    //в зависимости от языка прохождения вкл плеер c эффектами аудио "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (2);
      }
      if(language==2){
        mp3_play (3);
      }
      if(language==3){
        mp3_play (4);
      }                                         
      delay(10000);                                         //ПОДОБРАТЬ ЗНАЧЕНИЕ
      //затухание света кор2
    }
    if(digitalRead(sens1_doors1)==LOW){                 //если дверь закрылась(ДОБАВИТЬ ДАТЧИК ДВИЖЕНИЯ)
      mp3_stop();
      flag = 13;
    }
  }
  //===========================КОРИДОР 1===========================================
  if(flag == 13 && flag_stroboscope == 1){
    digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);                                   
    mp3_play (9);                                     // вкл плеєр з эффектами аудbо "крик" (НОМЕР УТОЧНИТЬ)
    time_stroboscope=millis();
    functionStroboscope();                              //эфект стробоскопа
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    Serial1.println(Master_Photos2_change);               //фоторамки в коридоре 1 вниз
    Serial1.println(Master_ShoeRack2_180deg);             //полка в коридоре 1 перевернуть
    Serial1.println(Master_Window2_vid2);                 //в окне коридора 1 сменить видео
    delay(60000);
    digitalWrite(K13_XO_lock, HIGH);                      //открытие картины Х/0
    delay(2000);
    digitalWrite(K13_XO_lock, LOW);
    flag = 14;
  }
  if(flag==14){
    if(flag_XO_bad == 1){
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (10);                                     // вкл плеєр з эффектами аудио "детский плач" (НОМЕР УТОЧНИТЬ)
      //- Запускається світловий ефект - мигання світла
      flag_XO_bad = 0;
    }
    if(flag_XO_good == 1){
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (10);                                     // вкл плеєр з эффектами аудио "детский смех" (НОМЕР УТОЧНИТЬ)
      delay(10000);
      time_phone = millis();
      functionPhoneRing();
      flag=15;
    }
  }
  if(flag==15){
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);                                       // вкл плеєр з эффектами аудио "исповедь женщины" (НОМЕР УТОЧНИТЬ)
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    if(language==1){                                    //в зависимости от языка прохождения вкл плеєр c эффектами аудіо "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (11);
        Serial1.println(Master_mirror_ru);               //текст под обоями
        flag=16;
      }
      if(language==2){
        mp3_play (12);
        Serial1.println(Master_mirror_en);
        flag=16;
      }
      if(language==3){
        mp3_play (13);
        Serial1.println(Master_mirror_heb);
        flag=16;
      }           
  }
  if(flag==16){
    delay(30000);
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    Serial1.println(Master_Light_off);               //выкл свет
    delay(1000);
    Serial1.println(Master_Light_kor1);             //вкл свет кор1
    delay(5000);
    Serial1.println(Master_Light_rele1);             //вкл дым машина на 4с
    delay(15000);
    digitalWrite(K11_doors2_led, HIGH);               //вкл подсветка над дверью2
    digitalWrite(K10_doors2, HIGH);                   //открывается дверь 2
    delay(2000);
    digitalWrite(K10_doors2, LOW);
    flag =17;
  }
  if(flag==17){
     digitalWrite(SSerialTxControl, HIGH);                 //передача даних
     Serial1.println(Master_Light_kor2);               //тусклый свет кор2
     while(digitalRead(sens1_doors2)==HIGH){           //пока дверь2 открыта
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);
      if(language==1){                                    //в зависимости от языка прохождения вкл плеєр c эффектами аудио "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (2);
      }
      if(language==2){
        mp3_play (3);
      }
      if(language==3){
        mp3_play (4);
      }                                         
      delay(10000);                                         //ПОДОБРАТЬ ЗНАЧЕНИЕ
      //затухание света кор1
    }
    if(digitalRead(sens1_doors2)==LOW){                 //если дверь закрылась(ДОБАВИТЬ ДАТЧИК ДВИЖЕНИЯ)
      mp3_stop();                                     //остановить аудио
      flag = 18;
    }
  }


  //================================КОРИДОР 2==========================================
  if(flag==19){
    digitalWrite(K18_kor1_mute, LOW);                     //выкл эфекты в кор1
    digitalWrite(K19_kor2_mute, HIGH);                     //вкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    Serial1.println(Master_Light_kor2);             //вкл свет кор2
    //свет мигает
    Serial1.println(Master_Phone2_start);             //звонок телефона
    flag=20;
  }
  if(flag==20){
    if(flag_phone_good == 1){                         //если от телефона пришел сигнал good
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    if(language==1){                                    //в зависимости от языка прохождения вкл радиола 2
        Serial1.println(Master_Radio2_on_ru);              
        flag=21;
      }
      if(language==2){
        Serial1.println(Master_Radio2_on_en);
        flag=21;
      }
      if(language==3){
        Serial1.println(Master_Radio2_on_heb);
        flag=21;
      }
    }
  }
  if(flag==21){
    digitalWrite(K1_stenka_k0k1,HIGH);                  //открывается фальш-стенка кор1-кухня
    digitalWrite(K15_stenka_k2of,HIGH);                 //открывается фальш-стенка кор1-офис
    delay(1000);
    digitalWrite(K1_stenka_k0k1,LOW);
    digitalWrite(K15_stenka_k2of,LOW);
    delay(40000);
    digitalWrite(SSerialTxControl, HIGH);                 //передача даних
    Serial1.println(Master_Lampa_on);                 //открывается нижняя часть вешалки
    flag=22;
  }
  if(flag==22){
    if(flag_lampa_start==1){
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
      Serial1.println(Master_Lampa_start);                  //старт задания с лампой
      flag=23;      
    }
  }
  if(flag==23){
    if(flag_lampa_bad == 1){
      //звук
      flag_lampa_bad = 0;
    }
    if(flag_lampa_good == 1){
      flag=24;
    }
  }
  if(flag==24){
    digitalWrite(K3_doors1_led, HIGH);               //вкл подсветка над дверью1
    digitalWrite(K2_doors1, HIGH);                   //открывается дверь 1
    digitalWrite(K15_stenka_k2of,HIGH);                 //открывается фальш-стенка кор1-офис
    delay(2000);
    digitalWrite(K2_doors1, LOW);
    digitalWrite(K15_stenka_k2of,LOW);   
    flag=25;             
  }

 //===============================КОРИДОР 1======================================
  if(flag==25){
     if(digitalRead(sens1_doors1)==LOW){                 //если дверь закрылась (ДОБАВИТЬ ДАТЧИК ДВИЖЕНИЯ)
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
      Serial1.println(Master_Light_office);               //вкл свет в офисе
      Serial1.println(Master_Heart_1);                    //вкл серце скорость 1
      Serial1.println(Master_Maski_on);                   //вкл маски майя
      digitalWrite(K18_kor1_mute, LOW);                     //выкл эфекты в кор1
      digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
      digitalWrite(K20_off_mute, HIGH);                      //вкл эфекты в офисе
      mp3_set_serial (pl_musicSerial);                       //переключить на мп3 музыка
      delay (100);                                            
      mp3_play (2);                                         //фоновая музыка                                         
      flag=26;
    }
  }
  //==============================ОФИС===============================================
  if(flag==26){
    if(flag_maski_bad == 1){
      //эффекты
      flag_maski_bad = 0;
    }
    if(flag_maski_good == 1){                                 //если выполнили задание с масками
      digitalWrite(K16_cal_maya_lock, HIGH);                  //открывается календарь майя
      delay(1000);
      digitalWrite(K16_cal_maya_lock, LOW);
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
      Serial1.println(Master_Heart_3);                    //вкл серце режиме 3
      flag=27;
    }
  }
  if(flag==27){
    if(flag_heart==1){
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (15);                                     // вкл плеєр c эффектами аудио "смерть" (НОМЕР УТОЧНИТЬ)
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
      Serial1.println(Master_Burzh_on);                  //вкл буржуйка
      flag=28;
    }
  }
  if(flag==28){
    delay(30000);                       //подобрать задержку 
    mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
    delay (100);                                   
    mp3_play (15);                                     // вкл плеєр c эффектами аудио "брось в огонь, сожги" (НОМЕР УТОЧНИТЬ)
    flag=29;
  }
  if(flag==29){
    if(flag_burzh_good = 1){
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (16);                                     // вкл плеєр c финальным аудио  (НОМЕР УТОЧНИТЬ)
      flag=30;
    }
  }

  //=================================ФИНАЛ===============================
  if(flag==30){
    if(flag_final=1){
      digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
      digitalWrite(K19_kor2_mute, HIGH);                     //вкл эфекты в кор2
      digitalWrite(K20_off_mute, HIGH);                      //вкл эфекты в офисе
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
      Serial1.println(Master_Window2_vid2);                        //переключить видео в кор2
      digitalWrite(K16_stenka_k0of, HIGH);               //открывается фальш-стенка кух-офис
      digitalWrite(K15_stenka_k2of,HIGH);                 //открывается фальш-стенка кор1-офис
      digitalWrite(K10_doors2, HIGH);                     //открывается дверь с кор1 в кор2
      digitalWrite(K17_stenka4_k2ex, HIGH);               //открывается фальш-стенка кор-вых
      delay(1000);
      digitalWrite(K16_stenka_k0of, LOW);
      digitalWrite(K15_stenka_k2of,LOW);
      digitalWrite(K10_doors2, LOW);
      digitalWrite(K17_stenka4_k2ex, LOW);
      Serial1.println(Master_hands1_on);                  //вкл картина с руками 1
      Serial1.println(Master_hands2_on);                  //вкл картина с руками 2
      Serial1.println(Master_Light_rele1);               //вкл дым машина на 4с
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (17);                                     // вкл плеєр c  аудио "к выходу"  (НОМЕР УТОЧНИТЬ)
      flag=31;
    }
  }
   
  if(flag==31){
    if(digitalRead(sens2_doors2)==HIGH){                             //если сработал датчик движения в кор2
      digitalWrite(K5_balka1, HIGH);                         //выпадает 1 балка
      delay(1000);
      digitalWrite(K6_balka2, HIGH);                         //выпадает 2 балка
      delay(1000);
      digitalWrite(K7_balka3, HIGH);                         //выпадает 3 балка
      flag=32;
    }
  }
////================================РЕЖИМ RESET=================================
  if(flag==32){
    if(flag_reset==1){
      mp3_set_serial (Serial2);                             //переключить на мп3 эфектов
      delay (100);
      mp3_stop();                                           //остановить аудио
      delay(100);
      mp3_set_serial (pl_musicSerial);                      //переключить на мп3 музыка
      delay (100);                                            
      mp3_stop ();                                         //остановить аудио
      digitalWrite(SSerialTxControl, HIGH);                 //передача даних
      Serial1.println(Master_Light_on);                     //вкл света
      Serial1.println(Master_Heart_off);                    //выкл серце
      Serial1.println(Master_Photos1_back);                 //фоторамки вверх
      Serial1.println(Master_Photos2_back);
      Serial1.println(Master_ShoeRack1_180deg);             //полки перевернуть
      Serial1.println(Master_ShoeRack2_180deg);
      Serial1.println(Master_Window1_off);                  //выкл TV
      Serial1.println(Master_Window2_off);                   
      Serial1.println(Master_Burzh_off);
      Serial1.println(Master_Lampa_off);
      Serial1.println(Master_Phone2_off);
      language = 0;
      flag_final = 0;
      flag_photo_bad = 0;         
      flag_photo_good = 0;
      flag_radiola = 0;           
      flag_window_good = 0;
      flag_window_bad = 0;
      flag_stroboscope = 0;
      flag_XO_good = 0;
      flag_XO_bad = 0;
      flag_phone_good = 0;
      flag_lampa_start = 0;
      flag_lampa_bad = 0;
      flag_lampa_good = 0;
      flag_maski_bad = 0;
      flag_maski_good = 0;
      flag_heart = 0;
      flag_burzh_good = 0;
    }
  }
  
  
}


void functionPhoneRing(){                           //звонок телефона
  while(millis()-time_phone<10000){
     while(millis()-time_phone<2000){
          digitalWrite(K4_tel_sol, HIGH);
          delay(20);
          digitalWrite(K4_tel_sol, LOW);
          delay(20);
     }
     while(millis()-time_phone>4000 && millis()-time_phone<6000){
          digitalWrite(K4_tel_sol, HIGH);
          delay(20);
          digitalWrite(K4_tel_sol, LOW);
          delay(20);
     }  
     while(millis()-time_phone>8000 && millis()-time_phone<10000){
          digitalWrite(K4_tel_sol, HIGH);
          delay(20);
          digitalWrite(K4_tel_sol, LOW);
          delay(20);
     }
  }
}

void functionStroboscope(){                           //стробоскоп
  while(millis()-time_stroboscope<10000){             //режим 1
    if(millis()-time_stroboscope<2000){               //
      digitalWrite(K10_doors2, HIGH);                 //открывание двери между кор1 и кор2
      digitalWrite(K1_stenka_k0k1, HIGH);             //открывание фальш стенки (ПРОВЕРИТЬ ТА ЛИ ДВЕРЬ)
    }
    if(millis()-time_stroboscope<2000){
      digitalWrite(K10_doors2, LOW);
      digitalWrite(K1_stenka_k0k1, LOW);
    }
    
    digitalWrite(stroboscope1, HIGH);
    delay(100);
    digitalWrite(stroboscope1, LOW);
    delay(100);
  }
  digitalWrite(stroboscope1, LOW);
  while(millis()-time_stroboscope>10000 && millis()-time_stroboscope<15000){
    digitalWrite(stroboscope2, HIGH);
    delay(50);
    digitalWrite(stroboscope2, LOW);
    delay(50);
  }
  digitalWrite(stroboscope2, LOW);
  
}

