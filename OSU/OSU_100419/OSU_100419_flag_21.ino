#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>

int SSerialTxControl = 40;   //RS485 Direction control

//=============================KОМАНДЫ=================================
const String Master_Heart_on = "Master_Heart_on#";                    //серце
const String Master_Heart_1 = "Master_Heart_1#";
const String Master_Heart_2 = "Master_Heart_2#";
const String Master_Heart_3 = "Master_Heart_3#";
const String Master_Heart_dead = "Master_Heart_dead#";
const String Master_Heart_off = "Master_Heart_off#";
const String Master_Heart_open = "Master_Heart_open#";

const String Master_Photos1_on = "Master_Photos1_on#";                  // фоторамKи
const String Master_Photos1_change = "Master_Photos1_change#";
const String Master_Photos1_back = "Master_Photos1_back#";
const String Master_Photos1_off = "Master_Photos1_off#";

const String Master_Window1_on_vid1 = "Master_Window1_on_vid1#";          //оKна-Kалендари
const String Master_Window1_vid2 = "Master_Window1_vid2#";
const String Master_Window1_off = "Master_Window1_off#";

const String Master_Radio1_on_ru = "Master_Radio1_on_ru#";                //радиолы
const String Master_Radio1_on_en = "Master_Radio1_on_en#";
const String Master_Radio1_on_heb = "Master_Radio1_on_heb#";
const String Master_Radio2_on_ru = "Master_Radio2_on_ru#";
const String Master_Radio2_on_en = "Master_Radio2_on_en#";
const String Master_Radio2_on_heb = "Master_Radio2_on_heb#";

const String Master_Phone2_start = "Master_Phone2_start#";                 //телефон
const String Master_Phone2_ring = "Master_Phone2_ring#";
const String Master_Phone2_off = "Master_Phone2_off#";

const String Master_mirror_ru = "Master_mirror_ru#";                        //зерKало+теKст под обоями
const String Master_mirror_en = "Master_mirror_en#";
const String Master_mirror_heb = "Master_mirror_heb#";

const String Master_hands1_on = "Master_hands1_on#";                        //Kартины с руKами
const String Master_hands2_on = "Master_hands2_on#";

const String Master_Burzh_on = "Master_Burzh_on#";                         //буржуйKа
const String Master_Burzh_off = "Master_Burzh_off#";
const String Master_Burzh_open = "Master_Burzh_open#";

const String Master_Maski_on = "Master_Maski_on#";                        //масKи майя

const String Master_Lampa_on = "Master_Lampa_on#";                        //лампа джойстиK + KлетKа
const String Master_Lampa_start = "Master_Lampa_start#";
const String Master_Lampa_off = "Master_Lampa_off#";
const String Master_Lampa_open1 = "Master_Kletka_open#";
const String Master_Lampa_open2 = "Master_Kletka_open2#";

const String Master_Projector_on = "Master_Projector_on#";                  //проеKтор
const String Master_Projector_start1 = "Master_Projector_start1#";
const String Master_Projector_stop = "Master_Projector_stop#";
const String Master_Projector_start2 = "Master_Projector_start2#";
const String Master_Projector_off = "Master_Projector_off#";

const String Master_Light_on = "Master_Light_on#";                          //управление светом
const String Master_Light_kor1 = "Master_Light_kor1#";
const String Master_Light_kor2 = "Master_Light_kor2#";
const String Master_Light_kor3 = "Master_Light_kor3#";
const String Master_Light_kor4 = "Master_Light_kor4#";
const String Master_Light_office_on = "Master_Light_office_on#";
const String Master_Light_office_off = "Master_Light_office_off#";
const String Master_Light_off = "Master_Light_off#";
const String Master_Light_rele1 = "Master_Light_rele1#";         //дим машина
const String Master_Light_rele2 = "Master_Light_rele2#";
const String Master_Light_rele3 = "Master_Light_rele3#"; // Тестовый свет
const String Master_Light_strob = "Master_Light_strob#";

const String Master_Light_kor1_good = "Master_Light_kor1_good#";//просветление на 2сек при правильном выполнении
const String Master_Light_kor2_good = "Master_Light_kor2_good#";//просветление на 2сек при правильном выполнении
const String Master_Light_kor3_good = "Master_Light_kor3_good#";//просветление на 2сек при правильном выполнении
const String Master_Light_kor4_good = "Master_Light_kor4_good#";//просветление на 2сек при правильном выполнении

const String Master_Light_kor1_bad = "Master_Light_kor1_bad#";//мигание 1-2сек
const String Master_Light_kor2_bad = "Master_Light_kor2_bad#";//мигание 1-2сек
const String Master_Light_kor3_bad = "Master_Light_kor3_bad#";//мигание 1-2сек
const String Master_Light_kor4_bad = "Master_Light_kor4_bad#";//мигание 1-2сек

const String Master_Light_kor1_fading = "Master_Light_kor1_fading#"; //затухание
const String Master_Light_kor2_fading = "Master_Light_kor2_fading#"; //затухание
const String Master_Light_kor3_fading = "Master_Light_kor3_fading#"; //затухание
const String Master_Light_kor4_fading = "Master_Light_kor4_fading#"; //затухание

const String Master_Light_kor1_shimering = "Master_Light_kor1_shimering#"; //затухание
const String Master_Light_stop_fading = "Master_Light_stop_fading#";//остановить затухание

////////////////////разрыв питания на девайсы////////////////////////
const String M1_polka_on = "M1_polka_on#";
const String M1_polka_off = "M1_polka_off#";
const String M2_kal_maya_on = "M2_kal_maya_on#";
const String M3_hands_on = "M3_hands_on#";
const String M3_hands_off = "M3_hands_off#";
const String M4_radiola1_on = "M4_radiola1_on#";
const String M4_radiola1_off = "M4_radiola1_off#";
const String M5_photos1_on = "M5_photos1_on#";
const String M5_photos1_off = "M5_photos1_off#";
const String M6_photos2_on = "M6_photos2_on#";
const String M6_photos2_off = "M6_photos2_off#";
const String M7_K13_XO_on = "M7_K13_XO_on#";
const String M7_K13_XO_off = "M7_K13_XO_off#";
const String M8_mirror_on = "M8_mirror_on#";
const String M8_mirror_off = "M8_mirror_off#";
//String Master_Light_rele3 = "Master_Light_rele3#";
//========================ТЕСТОВЫЕ КОМАНДЫ АНАЛОГОВАЯ СВЯЗЬ===================================================================

const String Analog_polka1 = "Analog_polka1#";
const String Analog_polka2 = "Analog_polka2#";
const String Analog_window2_on = "Analog_window2_on#";
const String Analog_window2_next = "Analog_window2_next#";
const String Analog_window2_off = "Analog_window2_off#";
const String Analog_mirror_ru = "Analog_mirror_ru#";
const String Analog_mirror_en = "Analog_mirror_en#";
const String Analog_mirror_heb = "Analog_mirror_heb#";
const String Analog_photos2_change = "Analog_photos2_change#";
const String Analog_photos2_back = "Analog_photos2_back#";
const String Analog_radiola1_ru = "Analog_radiola1_ru#";
const String Analog_radiola1_en = "Analog_radiola1_en#";
const String Analog_radiola1_heb = "Analog_radiola1_heb#";

const String Analog_radiola2_ru = "Analog_radiola2_ru#";
const String Analog_radiola2_en = "Analog_radiola2_en#";
const String Analog_radiola2_heb = "Analog_radiola2_heb#";

const String Analog_Lampa_on = "Analog_Lampa_on#";                        //лампа джойстиK + KлетKа
const String Analog_Lampa_start = "Analog_Lampa_start#";
const String Analog_Lampa_off = "Analog_Lampa_off#";
const String Analog_Lampa_open1 = "Analog_Kletka_open1#";
const String Analog_Lampa_open2 = "Analog_Kletka_open2#";

const String mp3_play_mus1 = "mp3_play_mus1#";
const String mp3_play_mus2 = "mp3_play_mus2#";
const String mp3_play_eff1 = "mp3_play_eff1#";

const String test_K17_stenka4_k2ex = "test_K17_stenka4_k2ex#";
const String test_K16_stenka_k0of = "K16_stenka_k0of#";
const String test_K15_stenka_k2of = "test_K15_stenka_k2of#";
const String test_K1_stenka_k0k1 = "test_K1_stenka_k0k1#";
const String test_K11_doors2_led = "test_K11_doors2_led#";
const String test_K10_doors2 = "test_K10_doors2#";
const String test_K3_doors1_led = "test_K3_doors1_led#";
const String test_K2_doors1 = "test_K2_doors1#";
const String test_balka = "test_balka#";
const String test_K16_cal_maya_lock = "test_K16_cal_maya_lock#";
const String test_K9_balls_sol = "test_K9_balls_sol#";
const String test_K8_balls_lock = "test_K8_balls_lock#";
const String test_K4_tel_sol = "test_K4_tel_sol#";
const String test_K12_stolik_lock = "test_K12_stolik_lock#";

//========================ОТВЕТЫ================================

const String Slave_Heart_itemInside = "Slave_Heart_itemInside#";            //серце

const String Slave_Photos1_goodParole = "Slave_Photos1_goodParole#";        //фоторамKи-KнопKи
const String Slave_Photos1_badParole = "Slave_Photos1_badParole#";

const String Slave_Window2_good = "Slave_Window2_good#"; // аналоговое управление                   //оKно-Kаленда
const String Slave_Window2_bad = "Slave_Window2_bad#";  // аналоговое управление


const String Slave_Radio1_goodKnock = "Slave_Radio1_goodKnock#";  // аналоговое управление          //радиола

const String Slave_Phone2_good = "Slave_Phone2_good#";                      //телефон

const String Slave_Burzh_good = "Slave_Burzh_good#";                       //буржуйKа

const String Slave_Maski_good = "Slave_Maski_good#";                        //масKи майя
const String Slave_Maski_bad = "Slave_Maski_bad#";  

const String Slave_Lampa_good = "Slave_Lampa_good#";     // аналоговое управление                   //лампа джойстиK + KлетKа
const String Slave_Lampa_bad = "Slave_Lampa_bad#";       // аналоговое управление
//=================================================================

//====================КОМАНДЫ С ПУЛЬТА=============================
const String Console_1 = "1#";
const String Console_2 = "2#";
const String Console_3 = "3#";
const String Console_4 = "4#";
const String Console_5 = "5#";
const String Console_6 = "6#";
const String Console_7 = "7#";
const String Console_8 = "8#";
const String Console_9 = "9#";
const String Console_0 = "0#";
const String Console_A = "A#";
const String Console_B = "B#";
const String Console_C = "C#";
const String Console_D = "D#";
const String Console_E = "E#";
const String Console_F = "F#";
const String Console_G = "G#";
const String Console_H = "H#";
const String Console_I = "I#";
const String Console_J = "J#";
const String Console_radioA = "radioA#";
const String Console_radioB = "radioB#";
const String Console_radioC = "radioC#";
const String Console_radioD = "radioD#";
const String Console_reset = "reset#";
const String Console_start = "start#";
const String Console_ru = "ru#";
const String Console_en = "en#";
const String Console_heb = "heb#";
const String Console_res1 = "_res1#";
const String Console_res2 = "_res2#";

//=================================================================

String string;
String string_reply;

//=======================ВЫВОДЫ С ОСУ==============================

const int K17_stenka4_k2ex = 38;        //- 12 стенKа K2-Вых
const int K16_stenka_k0of = 36;         //- 12В стенKа Kух-Оф
const int K15_stenka_k2of = 34;         //- 12B стенKаK2-Оф
const int K1_stenka_k0k1 = 32;         //фальш стенKи - 12В стенKаKух-K1
const int K11_doors2_led = 2;           // - 12В LED лампа
const int K10_doors2 = 3;        //Двери в офис - 12В ЕМЗ двери
const int K3_doors1_led = 4;           //подсветKа  - 12В LED лампа
const int K2_doors1 = 5;               //Двери в офис - 12В ЕМЗ двери
const int K7_balka3 = 6;               //------//------
const int K6_balka2 = 7;               //------//------
const int K5_balka1 = 8;               //Падающая часть потолKа
const int K16_cal_maya_lock = 9;        //замоK Kалендаря майя
const int K9_balls_sol = 10;           //соленоид шара
const int K8_balls_lock = 11;          //замоK шара в стене
const int K4_tel_sol = 12;             //телефон 1
const int K12_stolik_lock = 13;         //столиK под радиолу

//Подвод питания через 8-ch MOSFET на девайсы с ШД
const int M1_polka = 53;
const int M2_kal_maya = 51;
const int M3_hands = 49;
const int M4_radiola1 = 47;
const int M5_photos1 = 45;
const int M6_photos2 = 43;
const int M7_K13_XO = 41;
const int M8_mirror = 39;

//Аналоговый интерфейс связи
#define A0_Polka1_Tx A0
#define A1_Polka2_Tx A1
#define A2_window2_Tx A2
#define A3_window2_Tx A3
#define A4_window2_Rx A4 //good
#define A5_window2_Rx A5 //bad
#define A6_mirror_Tx A6
#define A7_mirror_Tx A7
#define A8_photos2_Tx A8
#define D46_photos2_Tx 46
#define A9_radiola1_Tx A9
#define A10_radiola1_Tx A10
#define A11_radiola1_Rx A11 //good
#define A12_Lampa_Tx A12
#define A13_Lampa_Tx A13
#define A14_Lampa_Tx A14
#define A15_Lampa_Rx A15 // good a15==0, d52==1 
#define D52_Lampa_Rx 52 //  bad  a15==1, d52==0 
#define D48_Radiola2_Tx 48
#define D50_Radiola2_Tx 50
#define D44_something_Tx 44


//Входы на ОСУ от датчиков и кнопок
const int S2_viselitsa = 27;          //вход от виселицы S2
const int S1_vikl = 29;               //вход от выKлючателя S1
const int S3_led = 33;                //5В светодиод выключатель S3
const int S4sens2_doors2 = 37;          //геркон на двери 2 S4
const int S5sens1_doors1 = 35;          //геркон на двери 1 S5
const int S6_sens_moveK1 = 31;		//Вход от датчика движения Кор1 S6
const int S7_sens_moveK2 = 25;		//Вход от датчика движения Кор2 S7

const int SSRxD15_pl_music = 15;    // Rx плеер музыKа 
const int SSRxD17_pl_eff = 17;      // Tx плеер эффекты

const int SSTxD24_pl_music = 24;    // Tx плеер музыKа
const int SSTxD22_pl_eff = 22;      // Tx плеер эффекты

const int K18_kor1_mute = 26;           // - выводы на mute
const int K19_kor2_mute = 28;           // - выводы на mute
const int K20_off_mute = 30;            //- выводы на mute
//==============================================================================


//=========================ФЛАГИ==========================
int flag_previous = 4242;
int flag = 0;                    //флаг последовательности

int dio = 0; //"do it once" flag
int dio_p = 0; //"do it once previous" state of flag

int language = 0;
int flag_final = 0;
int flag_photo_bad = 0;         //флаг фоторамки-кнопки
int flag_photo_good = 0;
int flag_radiola = 0;           
int flag_window_good = 0;
int flag_window_bad = 0;
int flag_stroboscope = 0;
int flag_mirror = 0;
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

SoftwareSerial pl_musicSerial(SSRxD15_pl_music, SSTxD24_pl_music); // RX, TX плеер музыKа
SoftwareSerial pl_effectsSerial(SSRxD17_pl_eff, SSTxD22_pl_eff); // RX, TX плеер музыKа

void setup() {
    Serial.begin(9600);						  //UART
    Serial1.begin(9600);                      //RS485
    pl_musicSerial.begin(9600);               //плеер музыKа
    pl_effectsSerial.begin(9600);             // плеер эффеKты+теKст

    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
     mp3_set_serial(pl_musicSerial);                //   софтовый серийный порт для мп3
    delay (100);                              //  обязательная задержка между командами
    mp3_set_volume (10);

    pinMode(S2_viselitsa, INPUT_PULLUP); 
    pinMode(S1_vikl, INPUT_PULLUP); 
    pinMode(S4sens2_doors2, INPUT_PULLUP); 
    pinMode(S6_sens_moveK1, INPUT); 
    pinMode(S5sens1_doors1, INPUT_PULLUP); 
    pinMode(S7_sens_moveK2, INPUT); 
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

  pinMode(M1_polka, OUTPUT);
  pinMode(M2_kal_maya, OUTPUT);
  pinMode(M3_hands, OUTPUT);
  pinMode(M4_radiola1, OUTPUT);
  pinMode(M5_photos1, OUTPUT);
  pinMode(M6_photos2, OUTPUT);
  pinMode(M7_K13_XO, OUTPUT);
  pinMode(M8_mirror, OUTPUT);

  pinMode(A0_Polka1_Tx, OUTPUT);
  pinMode(A1_Polka2_Tx, OUTPUT);
  pinMode(A2_window2_Tx, OUTPUT);
  pinMode(A3_window2_Tx, OUTPUT);
  pinMode(A4_window2_Rx, INPUT_PULLUP);
  pinMode(A5_window2_Rx, INPUT_PULLUP);
  pinMode(A6_mirror_Tx, OUTPUT);
  pinMode(A7_mirror_Tx, OUTPUT);
  pinMode(A8_photos2_Tx, OUTPUT);
  pinMode(A9_radiola1_Tx, OUTPUT);
  pinMode(A10_radiola1_Tx, OUTPUT);
  pinMode(A11_radiola1_Rx, INPUT_PULLUP);
  pinMode(A12_Lampa_Tx, OUTPUT);
  pinMode(A13_Lampa_Tx, OUTPUT);
  pinMode(A14_Lampa_Tx, OUTPUT);
  pinMode(A15_Lampa_Rx, INPUT_PULLUP);
  pinMode(D52_Lampa_Rx, INPUT_PULLUP);
  pinMode(D48_Radiola2_Tx, OUTPUT);
  pinMode(D50_Radiola2_Tx, OUTPUT);

  pinMode(D44_something_Tx, OUTPUT);
  pinMode(D46_photos2_Tx, OUTPUT);

  digitalWrite(A0_Polka1_Tx, HIGH);
  digitalWrite(A1_Polka2_Tx, HIGH);
  digitalWrite(A2_window2_Tx, HIGH);
  digitalWrite(A3_window2_Tx, HIGH);
  
  digitalWrite(A6_mirror_Tx, HIGH);
  digitalWrite(A7_mirror_Tx, HIGH);
  digitalWrite(A8_photos2_Tx, HIGH);
  digitalWrite(D46_photos2_Tx, HIGH);
  digitalWrite(A9_radiola1_Tx, HIGH);
  digitalWrite(A10_radiola1_Tx, HIGH);

  digitalWrite(A12_Lampa_Tx, HIGH);
  digitalWrite(A13_Lampa_Tx, HIGH);
  digitalWrite(A14_Lampa_Tx, HIGH); 

  digitalWrite(D48_Radiola2_Tx, HIGH);
  digitalWrite(D50_Radiola2_Tx, HIGH);

  digitalWrite(D44_something_Tx, HIGH);

  digitalWrite(M1_polka, HIGH);
  digitalWrite(M2_kal_maya, HIGH);
  digitalWrite(M3_hands, HIGH);
  digitalWrite(M4_radiola1, HIGH);
  digitalWrite(M5_photos1, HIGH);
  digitalWrite(M6_photos2, HIGH);
  digitalWrite(M7_K13_XO, HIGH);
  digitalWrite(M8_mirror, HIGH);

  digitalWrite(K17_stenka4_k2ex, HIGH);
  digitalWrite(K16_stenka_k0of, HIGH);
  digitalWrite(K15_stenka_k2of, HIGH);
  digitalWrite(K1_stenka_k0k1, HIGH);
  digitalWrite(K11_doors2_led, LOW);
  digitalWrite(K10_doors2, HIGH);
  digitalWrite(K3_doors1_led, LOW);
  digitalWrite(K2_doors1, HIGH);
  digitalWrite(K7_balka3, HIGH);
  digitalWrite(K6_balka2, HIGH);
  digitalWrite(K5_balka1, HIGH);
  digitalWrite(K16_cal_maya_lock, LOW);
  digitalWrite(K9_balls_sol, LOW);
  digitalWrite(K8_balls_lock, LOW);
  digitalWrite(K4_tel_sol, LOW);
  digitalWrite(K12_stolik_lock, LOW);

  Serial.println("OSU_loaded");

}

void(* resetFunc) (void) = 0;//объявляем функцию reset с адресом 0 - софтовая перезагрузка

void loop() 
{
  functionStart();
  //functionAnalogCommunication();

  if (Serial1.available()) 
  {
    string_reply = "";
    delay(100);
    tx();
  }

 /*if(flag_previous != flag)
 {
  Serial.print("flag_previous = ");
  Serial.print(flag_previous);
  Serial.print("  flag = ");
  Serial.println(flag);
  flag_previous = flag;
 }*/

}

void tx() {                          // розпізнання Kоманди по RS485
  digitalWrite(SSerialTxControl, LOW);
  while (Serial1.available())
  {
    char inChar = Serial1.read();
    string_reply += inChar;
    if (inChar == '#') 
    {
      delay(200);
      Serial.print(string_reply);
      Serial.println(" - copy that!");

      if (string_reply.equals(Console_start) && flag == 0)                                           //пришла команда start с пульта первый раз
      {
        flag = 1;
        dio_p=!dio;
        string_reply = "";

      }

      if ((string_reply.equals(Console_start) || string_reply.equals(Console_radioA)) && flag == 1)      //пришла команда start с пульта второй раз или команда А с радио пульта
      {        
        flag = 2 ;
        dio_p=!dio;
      }
      if (string_reply.equals(Console_reset))
      {
        flag_reset = 1;
        delay(100);
        resetFunc();
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
        flag_photo_good == 1;
      }
      if (string_reply.equals(Console_3))
      {

      }
      if (string_reply.equals(Console_4))
      {

      }
      if (string_reply.equals(Console_5))
      {
        
      }
      if (string_reply.equals(Console_6))
      {
        flag_mirror = 1;
      }
      if (string_reply.equals(Console_7))
      {

        flag_XO_good = 1;
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
        digitalWrite(K2_doors1, LOW);
        delay(1000);
        digitalWrite(K2_doors1, HIGH);
      }
      if (string_reply.equals(Console_F))
      {
        digitalWrite(K10_doors2, LOW);
        delay(1000);
        digitalWrite(K10_doors2, HIGH);
      }
      if (string_reply.equals(Console_G))
      {
        digitalWrite(K16_stenka_k0of, LOW);
        delay(1000);
        digitalWrite(K16_stenka_k0of, HIGH);
      }
      if (string_reply.equals(Console_H))
      {
        digitalWrite(K1_stenka_k0k1, LOW);
        delay(1000);
        digitalWrite(K1_stenka_k0k1, HIGH);
      }
      if (string_reply.equals(Console_I))
      {
        digitalWrite(K1_stenka_k0k1, LOW);
        delay(1000);
        digitalWrite(K1_stenka_k0k1, HIGH);        
      }
      if (string_reply.equals(Console_J))
      {
        digitalWrite(K17_stenka4_k2ex, LOW);
        delay(1000);
        digitalWrite(K17_stenka4_k2ex, HIGH);
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
        digitalWrite(K2_doors1, LOW);      
        digitalWrite(K17_stenka4_k2ex, LOW);
        delay(1000);
        digitalWrite(K17_stenka4_k2ex, HIGH);
        digitalWrite(K2_doors1, HIGH);
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
      if (string_reply.equals(Slave_Burzh_good))
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




      //////////////////////////////// Разрывы питания для девайсов в коридорах
      if (string_reply.equals(M1_polka_on))
      {
        digitalWrite(M1_polka, LOW);
      }
      if (string_reply.equals(M1_polka_off))
      {
        digitalWrite(M1_polka, HIGH);
      }

      if (string_reply.equals(M2_kal_maya_on))
      {
        digitalWrite(M2_kal_maya, LOW);
        delay(1000);
        digitalWrite(M2_kal_maya, HIGH);
      }

      if (string_reply.equals(M3_hands_on))
      {
        digitalWrite(M3_hands, LOW);
      }
      if (string_reply.equals(M3_hands_off))
      {
        digitalWrite(M3_hands, HIGH);
      }

      if (string_reply.equals(M4_radiola1_on))
      {
        digitalWrite(M4_radiola1, LOW);
      }
      if (string_reply.equals(M4_radiola1_off))
      {
        digitalWrite(M4_radiola1, HIGH);
      }

      if (string_reply.equals(M5_photos1_on))
      {
        digitalWrite(M5_photos1, LOW);
      }
      if (string_reply.equals(M5_photos1_off))
      {
        digitalWrite(M5_photos1, HIGH);
      }

      if (string_reply.equals(M6_photos2_on))
      {
        digitalWrite(M6_photos2, LOW);
      }
      if (string_reply.equals(M6_photos2_off))
      {
        digitalWrite(M6_photos2, HIGH);
      }

      if (string_reply.equals(M7_K13_XO_on))
      {
        digitalWrite(M7_K13_XO, LOW);
      }
      if (string_reply.equals(M7_K13_XO_off))
      {
        digitalWrite(M7_K13_XO, HIGH);
      }

       if (string_reply.equals(M8_mirror_on))
      {
        digitalWrite(M8_mirror, LOW);
      }
      if (string_reply.equals(M8_mirror_off))
      {
        digitalWrite(M8_mirror, HIGH);
      }

      ///////////////////////////////////////////////////////polka1,2/////////
      if (string_reply.equals(Analog_polka1))
      {
        digitalWrite(M1_polka, LOW);
        delay(2000);
        digitalWrite(A0_Polka1_Tx, LOW);
        delay(200);
        digitalWrite(A0_Polka1_Tx, HIGH);
      }

      if (string_reply.equals(Analog_polka2))
      {
        digitalWrite(M1_polka, LOW);
        delay(2000);
        digitalWrite(A1_Polka2_Tx, LOW);
        delay(200);
        digitalWrite(A1_Polka2_Tx, HIGH);
      }

      ////////////////////////////////////////////////////////window2//////////
      if (string_reply.equals(Analog_window2_on))
      {
        digitalWrite(A2_window2_Tx, HIGH);
        digitalWrite(A3_window2_Tx, LOW);
        delay(200);
        digitalWrite(A2_window2_Tx, HIGH);
        digitalWrite(A3_window2_Tx, HIGH);
      }

      if (string_reply.equals(Analog_window2_next))
      {
        digitalWrite(A2_window2_Tx, LOW);
        digitalWrite(A3_window2_Tx, LOW);
        delay(200);
        digitalWrite(A2_window2_Tx, HIGH);
        digitalWrite(A3_window2_Tx, HIGH);
      }

      if (string_reply.equals(Analog_window2_off))
      {
        digitalWrite(A2_window2_Tx, LOW);
        digitalWrite(A3_window2_Tx, HIGH);
        delay(200);
        digitalWrite(A2_window2_Tx, HIGH);
        digitalWrite(A3_window2_Tx, HIGH);
      }

      ////////////////////////////////////////////////////////mirror//////////
      if (string_reply.equals(Analog_mirror_ru))
      {
        digitalWrite(M8_mirror, LOW);
        delay(3500);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, LOW);
        delay(200);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, HIGH);
      }

      if (string_reply.equals(Analog_mirror_en))
      {
        digitalWrite(M8_mirror, LOW);
        delay(3500);
        digitalWrite(A6_mirror_Tx, LOW);
        digitalWrite(A7_mirror_Tx, HIGH);
        delay(200);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, HIGH);
      }

      if (string_reply.equals(Analog_mirror_heb))
      {
        digitalWrite(M8_mirror, LOW);
        delay(3500);
        digitalWrite(A6_mirror_Tx, LOW);
        digitalWrite(A7_mirror_Tx, LOW);
        delay(200);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, HIGH);
      }

////////////////////////////////////////////////////////Photos2//////////
      if (string_reply.equals(Analog_photos2_change))
      {
        digitalWrite(M6_photos2, LOW);
        delay(1000);

        digitalWrite(D46_photos2_Tx, HIGH);
        digitalWrite(A8_photos2_Tx, LOW);
        delay(300);
        digitalWrite(A8_photos2_Tx, HIGH);
        digitalWrite(D46_photos2_Tx, HIGH);
      }

      if (string_reply.equals(Analog_photos2_back))
      {
        digitalWrite(D46_photos2_Tx, LOW);
        digitalWrite(A8_photos2_Tx, HIGH);
        delay(300);
        digitalWrite(A8_photos2_Tx, HIGH);
        digitalWrite(D46_photos2_Tx, HIGH);
      }

 ////////////////////////////////////////////////////////radiola1//////////
      if (string_reply.equals(Analog_radiola1_ru))
      {
        digitalWrite(M4_radiola1, LOW);
        delay(2000);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, LOW);
        delay(200);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, HIGH);
      }

      if (string_reply.equals(Analog_radiola1_en))
      {
        digitalWrite(A9_radiola1_Tx, LOW);
        digitalWrite(A10_radiola1_Tx, HIGH);
        delay(200);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, HIGH);
      }      

      if (string_reply.equals(Analog_radiola1_heb))
      {
        digitalWrite(A9_radiola1_Tx, LOW);
        digitalWrite(A10_radiola1_Tx, LOW);
        delay(200);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, HIGH);
      }

////////////////////////////////////////////////////////Lampa//////////
      if (string_reply.equals(Analog_Lampa_on))
      {
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, LOW);
        digitalWrite(A14_Lampa_Tx, LOW);
        delay(200);
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, HIGH);
      }

      if (string_reply.equals(Analog_Lampa_start))
      {
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, LOW);
        delay(200);
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, HIGH);
      }

      if (string_reply.equals(Analog_Lampa_off))
      {
        digitalWrite(A12_Lampa_Tx, LOW);
        digitalWrite(A13_Lampa_Tx, LOW);
        digitalWrite(A14_Lampa_Tx, LOW);
        delay(200);
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, HIGH);
      }

      if (string_reply.equals(Analog_Lampa_open1))
      {
        digitalWrite(A12_Lampa_Tx, LOW);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, HIGH);
        delay(200);
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, HIGH);
      }

      if (string_reply.equals(Analog_Lampa_open2))
      {
        digitalWrite(A12_Lampa_Tx, LOW);
        digitalWrite(A13_Lampa_Tx, LOW);
        digitalWrite(A14_Lampa_Tx, HIGH);
        delay(200);
        digitalWrite(A12_Lampa_Tx, HIGH);
        digitalWrite(A13_Lampa_Tx, HIGH);
        digitalWrite(A14_Lampa_Tx, HIGH);
      }
      
////////////////////////////////////////////////////////radiola2//////////
      if (string_reply.equals(Analog_radiola2_en))
      {
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, LOW);
        delay(400);
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, HIGH);
      }

      if (string_reply.equals(Analog_radiola2_ru))
      {
        digitalWrite(D48_Radiola2_Tx, LOW);
        digitalWrite(D50_Radiola2_Tx, HIGH);
        delay(400);
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, HIGH);
      }

      if (string_reply.equals(Analog_radiola2_heb))
      {
        digitalWrite(D48_Radiola2_Tx, LOW);
        digitalWrite(D50_Radiola2_Tx, LOW);
        delay(400);
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, HIGH);
      }


      ///////////////////////////////////////////////////testing//////////////////////////////////////////
      if (string_reply.equals(mp3_play_mus1))
      {
        mp3_set_serial(pl_musicSerial);                //   софтовый серийный порт для мп3
        delay (50);                              //  обязательная задержка между командами
        mp3_set_volume (10);
        digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
        digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
        digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
        mp3_play(1);
      }

      if (string_reply.equals(mp3_play_mus2))
      {
        mp3_set_serial(pl_musicSerial);                //   софтовый серийный порт для мп3
        delay (50);                              //  обязательная задержка между командами
        mp3_set_volume (10);
        digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
        digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
        digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
        mp3_play(2);
      }

      if (string_reply.equals(mp3_play_eff1))
      {
        mp3_set_serial(pl_effectsSerial);                //   софтовый серийный порт для мп3
        delay (50);                              //  обязательная задержка между командами
        mp3_set_volume (15);
        digitalWrite(K18_kor1_mute, LOW);                     //вкл эфекты в кор1
        digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
        digitalWrite(K20_off_mute, HIGH);                      //выкл эфекты в офисе
        mp3_play(1);
      }

      if (string_reply.equals(test_K17_stenka4_k2ex))
      {
        digitalWrite(K17_stenka4_k2ex, LOW);
        delay(1000);
        digitalWrite(K17_stenka4_k2ex, HIGH);
      }
      if (string_reply.equals(test_K16_stenka_k0of))
      {
        digitalWrite(K16_stenka_k0of, LOW);
        delay(1000);
        digitalWrite(K16_stenka_k0of, HIGH);
      }
      if (string_reply.equals(test_K15_stenka_k2of))
      {
        digitalWrite(K15_stenka_k2of, LOW);
        delay(1000);
        digitalWrite(K15_stenka_k2of, HIGH);
      }
      if (string_reply.equals(test_K1_stenka_k0k1))
      {
        digitalWrite(K1_stenka_k0k1, LOW);
        delay(1000);
        digitalWrite(K1_stenka_k0k1, HIGH);
      }
      if (string_reply.equals(test_K11_doors2_led))
      {
        digitalWrite(K11_doors2_led, HIGH);
        delay(5000);
        digitalWrite(K11_doors2_led, LOW);
      }
      if (string_reply.equals(test_K10_doors2))
      {
        digitalWrite(K10_doors2, LOW);
        delay(1000);
        digitalWrite(K10_doors2, HIGH);
      }
      if (string_reply.equals(test_K3_doors1_led))
      {
        digitalWrite(K3_doors1_led, HIGH);
        delay(5000);
        digitalWrite(K3_doors1_led, LOW);
      }
      if (string_reply.equals(test_K2_doors1))
      {
        digitalWrite(K2_doors1, LOW);
        delay(1000);
        digitalWrite(K2_doors1, HIGH);
      }

      if (string_reply.equals(test_balka))
      {
        digitalWrite(K7_balka3, LOW);
        delay(1000);
        digitalWrite(K6_balka2, LOW);
        delay(1000);
        digitalWrite(K5_balka1, LOW);
        delay(1000);
        digitalWrite(K7_balka3, HIGH);
        digitalWrite(K6_balka2, HIGH);
        digitalWrite(K5_balka1, HIGH);
      }
      if (string_reply.equals(test_K16_cal_maya_lock))
      {
        digitalWrite(K16_cal_maya_lock, HIGH);
        delay(1000);
        digitalWrite(K16_cal_maya_lock, LOW);
      }
      if (string_reply.equals(test_K9_balls_sol))
      {
        digitalWrite(K9_balls_sol, HIGH);
        delay(2000);
        digitalWrite(K9_balls_sol, LOW);
      }
      if (string_reply.equals(test_K8_balls_lock))
      {
        digitalWrite(K8_balls_lock, HIGH);
        delay(1000);
        digitalWrite(K8_balls_lock, LOW);
      }
      if (string_reply.equals(test_K4_tel_sol))
      {
        time_phone = millis();
        functionPhoneRing();
      }
      if (string_reply.equals(test_K12_stolik_lock))
      {
        digitalWrite(K12_stolik_lock, HIGH);
        delay(1000);
        digitalWrite(K12_stolik_lock, LOW);
      }

      /*if (string_reply.equals(Slave_Heart_itemInside) || 
          string_reply.equals(Slave_Photos1_goodParole) || 
          string_reply.equals(Slave_Window2_good) || 
          string_reply.equals(Slave_Phone2_good) || 
          string_reply.equals(Slave_Burzh_good) || 
          string_reply.equals(Slave_Maski_good)
          )
      {
        mp3_set_serial(pl_effectsSerial);                //   софтовый серийный порт для мп3
        delay (50);                              //  обязательная задержка между командами
        mp3_set_volume (15);
        digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
        digitalWrite(K19_kor2_mute, HIGH);                     //выкл эфекты в кор2
        digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
        mp3_play(51);
      }

      if (string_reply.equals(Slave_Photos1_badParole) || 
          string_reply.equals(Slave_Window2_bad) ||
          string_reply.equals(Slave_Maski_bad)
          )
      {
        mp3_set_serial(pl_effectsSerial);                //   софтовый серийный порт для мп3
        delay (50);                              //  обязательная задержка между командами
        mp3_set_volume (15);
        digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
        digitalWrite(K19_kor2_mute, HIGH);                     //выкл эфекты в кор2
        digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
        mp3_play(1);
      }*/

    string_reply = "";
    }
  }
}

void functionStart(){   

  digitalWrite(SSerialTxControl, LOW);

  if(flag==0)
  {

  }
  
  if(flag == 1 && (dio_p != dio))
  { 
    delay(100);                                       //настройки перед запуском
    digitalWrite(SSerialTxControl, HIGH);  //передача данных
    Serial1.println(Master_Projector_on);
    delay(500);
    Serial1.println(Master_Window1_on_vid1); //включение телевизора в коридоре 1
    delay(500);
    Serial1.println(Master_Light_off); //включение режим свет
    delay(500);
    digitalWrite(SSerialTxControl, LOW); 

    digitalWrite(A2_window2_Tx, HIGH); //включение телевизора в коридоре 2
    digitalWrite(A3_window2_Tx, LOW);
    delay(200);
    digitalWrite(A2_window2_Tx, HIGH);
    digitalWrite(A3_window2_Tx, HIGH);
    delay(100);                //передача данных

    digitalWrite(M5_photos1, LOW);                       //врубаем питание на задание с фотками
    digitalWrite(M1_polka, LOW);
    delay(2000);
    digitalWrite(A0_Polka1_Tx, LOW);
    delay(200);
    digitalWrite(A0_Polka1_Tx, HIGH);
    Serial.println("game_is_loading, wait a few secs, then press start");
    delay(100);
    dio_p = dio;
  } 

  //================================КУХНЯ===========================================
  if(flag == 2 && (dio_p != dio)){                                          //начало игры
    Serial.println("Started - let's go, flag = 2");
    delay(100);
    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    delay(50);                                            //нужно проверить нужна ли здесь задержка
    Serial1.println(Master_Projector_start1);             //включение проектора
    delay(50);
    digitalWrite(SSerialTxControl, LOW);                 //передача данных
    delay(10000);                                         //задержка для просмотра видео
    
    digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    mp3_set_volume(15);
    delay (50);
    mp3_play (31);                                         //вкл плеєр з эффектами Слышен гул, шум, скрипы (НОМЕР УТОЧНИТЬ)
    delay(1000);
    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Projector_stop);              //проектор на паузу
    delay(200);
    digitalWrite(SSerialTxControl, LOW);                 //прийом данных

    digitalWrite(K1_stenka_k0k1, LOW);                   //открывается дверь кух-к1 откр на 2сек (админ выходит)
    digitalWrite(K17_stenka4_k2ex, LOW);
    digitalWrite(K2_doors1, LOW);
    delay(2000);
    digitalWrite(K1_stenka_k0k1, HIGH);
    digitalWrite(K17_stenka4_k2ex, HIGH);
    digitalWrite(K2_doors1, HIGH);
    delay(15000);
    flag=3;
    dio_p = dio;
  }
  if(flag == 3){
    Serial.println("flag=3 admin have got out");
    delay(100);

    digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (pl_musicSerial);                             //переключить на мп3 музыки
    mp3_set_volume(18);
    delay (50);
    mp3_play (1);       

    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Projector_start2);             //включение проектора
    delay(300);
    digitalWrite(SSerialTxControl, LOW);                 //прийом данных
    delay(10000);                                         //настроить задержку
    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Projector_off);                //выключение проектора
    delay(300);
    digitalWrite(SSerialTxControl, LOW);                 //прийом данных
    flag=4;
    dio_p=!dio;
  }
  //=================================КОРИДОР 1==========================================
  if(flag == 4){
    if(dio_p!=dio){
      Serial.println("flag=4 light is flickering, tick on the switch");
    delay(100);
      dio_p=dio;

      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      Serial1.println(Master_Light_kor1_shimering);         //мигание света
      delay(300);
      digitalWrite(SSerialTxControl, LOW);                 //прийом данных

    }

    if(digitalRead(S1_vikl)==HIGH){                         //включили выключатель
      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      Serial1.println(Master_Light_kor1);
      delay(100);
      Serial1.println(Master_Photos1_on);                 //активировать фоторамки
      delay(100);
      digitalWrite(SSerialTxControl, LOW);                 //прийом данных
      flag=5;
      dio_p=!dio;
    }
  }
  if(flag==5){
    if(dio_p!=dio){
      Serial.println("flag=5 do the photos");
    delay(100);
      dio_p=dio;
    }
    if(flag_photo_bad == 1){                              //от фоторамок пришел сигнал bad
    digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    delay (100);  
      if(language==1){                                    //в зависимости от языка прохождения вкл вкл плеер и эффектами аудио "нет не правильно" (НОМЕР УТОЧНИТЬ)
        mp3_play(1);

        digitalWrite(SSerialTxControl, HIGH);
        delay(50);
        Serial1.println(Master_Light_kor1_bad);
        delay(100);
        digitalWrite(SSerialTxControl, LOW);   
      }
      if(language==2){
        mp3_play(2);

        digitalWrite(SSerialTxControl, HIGH);
        delay(50);
        Serial1.println(Master_Light_kor1_bad);
        delay(100);
        digitalWrite(SSerialTxControl, LOW);   
      }
      if(language==3){
        mp3_play(3);

        digitalWrite(SSerialTxControl, HIGH);
        delay(50);
        Serial1.println(Master_Light_kor1_bad);
        delay(100);
        digitalWrite(SSerialTxControl, LOW);   
      }

      //Додати світловий ефект - мигання світла при неправильному рішенні

      flag_photo_bad =0;
    }
    if(flag_photo_good == 1){                             //от фоторамок пришел сигнал good
 ////////////////////////////////////////////////////////radiola1//////////

      mp3_set_serial (pl_effectsSerial);                       //переключить на мп3 музыка
      delay (100);                                            
      mp3_play (35);                                         //выполнено

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor1_good);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   

      mp3_set_serial (pl_musicSerial);
      mp3_set_volume (10);
      digitalWrite(M4_radiola1, LOW);
      delay(2000);
      if(language==1){                                    //в зависимости от языка прохождения вкл радиола1
        
        digitalWrite(A9_radiola1_Tx, HIGH); //ru
        digitalWrite(A10_radiola1_Tx, LOW);
        delay(200);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, HIGH);

        flag=6;
      }
      if(language==2){
        
        digitalWrite(A9_radiola1_Tx, LOW); //en
        digitalWrite(A10_radiola1_Tx, HIGH);
        delay(200);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, HIGH);

        flag=6;
      }
      if(language==3){
        
        digitalWrite(A9_radiola1_Tx, LOW); //heb
        digitalWrite(A10_radiola1_Tx, LOW);
        delay(200);
        digitalWrite(A9_radiola1_Tx, HIGH);
        digitalWrite(A10_radiola1_Tx, HIGH);

        flag=6;
      }
    }
  }
  if(flag==6 && digitalRead(A11_radiola1_Rx) == LOW){                   //если постучали в дверь
    delay(50);

    Serial.println("flag=6 door is knocked good");
    delay(100);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor1_good);
      delay(100);
      digitalWrite(SSerialTxControl, LOW); 

      mp3_set_serial (pl_effectsSerial);                       //переключить на мп3 музыка
      delay (100);                                            
      mp3_play (35);                                         //выполнено

    //Скрип двери

    digitalWrite(K3_doors1_led, HIGH);               //вкл подсветка над дверью2
    digitalWrite(K2_doors1, LOW);                   //открывается дверь 2
    delay(2000);
    digitalWrite(K2_doors1, HIGH);

    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println(Master_Light_kor1_fading);
    delay(100);
    digitalWrite(SSerialTxControl, LOW);   

    flag = 7;
    dio_p=!dio;
  }

  if(flag == 7){
    Serial.println("f7 uhodite v k2");
    delay(100);
    while(digitalRead(S5sens1_doors1)==HIGH){           //пока дверь2 открыта
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);
      if(language==1 && dio_p!=dio){                                    //в зависимости от языка прохождения вкл плеер и эффектами аудио "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (4);
      }
      if(language==2&& dio_p!=dio){
        mp3_play (5);
      }
      if(language==3&& dio_p!=dio){
        mp3_play (6);
      }                                         
      dio_p=dio;                                      

    }
    if(digitalRead(S5sens1_doors1)==LOW){                 //если дверь закрылась
      delay(500);
      mp3_stop();
      mp3_set_serial(pl_musicSerial);
      delay(50);
      mp3_stop();
      digitalWrite(K3_doors1_led, LOW);               //выкл подсветка над дверью2
      flag = 8;
    }
  }
  //======================================КОРИДОР 2===========================================
  if(flag==8){
    Serial.println("flag=8 door is closed run on the potolok");
    delay(100);
    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Light_kor2);                 //вкл свет в коридоре 2
    delay(100);
    digitalWrite(SSerialTxControl, LOW);                 //передача данных
    delay(5000);
    
    digitalWrite(K18_kor1_mute, LOW);                     //выкл эфекты в кор1
    digitalWrite(K19_kor2_mute, HIGH);                     //вкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    delay (100);                                 
    mp3_play (32);    //пробежка по потолку

    delay(1000);
    digitalWrite(K7_balka3, LOW);                         //выпадает 1 балка
    delay(2000);
    digitalWrite(K6_balka2, LOW);                         //выпадает 2 балка
    delay(2000);
    digitalWrite(K5_balka1, LOW);                         //выпадает 3 балка
    delay(1000);
    digitalWrite(K5_balka1, HIGH);
    digitalWrite(K6_balka2, HIGH);
    digitalWrite(K7_balka3, HIGH);

    mp3_set_serial (pl_musicSerial);                             //переключить на мп3 эфектов
    mp3_set_volume(18);
    delay (100);                                 
    mp3_play(2);   

    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Photos1_change);               //фоторамки в коридоре 1 вниз
    delay(100); //добавить вращение полки
    Serial1.println(Master_Window1_vid2);                 //в окне коридора 1 сменить видео
    delay(100);                                      // вкл плеєр с эффектами аудио " "кто-то бежит по втором этаже"" (НОМЕР УТОЧНИТЬ)
    digitalWrite(SSerialTxControl, LOW);
    flag = 9;
    dio_p=!dio;
  }
  if(flag == 9){
    if(dio_p!=dio){
    Serial.println("flag=9 balki and viselitsa is down. pull for 1sec");
    delay(100);
    dio_p=dio;
  }
    time_viselitsa=millis();
    while(digitalRead(S2_viselitsa)==LOW){                //пока кнопка нажата
      if((millis()-time_viselitsa)>300){                 //если держать больше 1с
        flag = 10;
        break;
      }
    }
  }
  if(flag==10){
    mp3_set_serial (pl_effectsSerial);                       //переключить на мп3 музыка
    delay (100);                                            
    mp3_play (35);                                         //задание выполнено
    delay(1000);

    Serial.println("flag=10 balls is rolling");
    digitalWrite(K9_balls_sol, HIGH);                   // вкл соленоид на 5с
    delay(2000);
    digitalWrite(K9_balls_sol, LOW);
    delay(15000);                                       //задержку настроить
    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Phone2_ring);                  //звонит телефон 2
    delay(100);
    digitalWrite(SSerialTxControl, LOW);
    delay(12500); //ждем, пока позвонит телефон
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      mp3_set_volume(25);
      delay (100);
      if(language==1){                                    //в зависимости от языка прохождения вкл плеер с эффектами аудио "он сошел с ума, спасите его" (НОМЕР УТОЧНИТЬ)
        mp3_play (7); //звонок в 9111
      }
      if(language==2){
        mp3_play (8);
      }
      if(language==3){
        mp3_play (9);
      }

      flag = 11;
      dio_p=!dio;
  }
  if(flag == 11){
    if(dio_p!=dio){
    Serial.println("flag=11 do the window2");
    delay(100);
    dio_p=dio;
    }
    if(flag_window_bad == 1 || digitalRead(A5_window2_Rx) == LOW){
      delay(50);
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    delay (100);  
      if(language==1){                                    //в зависимости от языка прохождения вкл вкл плеер и эффектами аудио "нет не правильно" (НОМЕР УТОЧНИТЬ)
        mp3_play(1);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_bad);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);         
      }
      if(language==2){
        mp3_play(2);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_bad);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   
      }
      if(language==3){
        mp3_play(3);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_bad);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   
      }

      flag_window_bad = 0;
    }
    if(flag_window_good == 1 || digitalRead(A4_window2_Rx) == LOW){

      mp3_set_serial (pl_effectsSerial);                       //переключить на мп3 музыка
      delay (100);                                            
      mp3_play (35);                                         //задание выполнено

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_good);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   


      delay(50);
      digitalWrite(K11_doors2_led, HIGH);               //вкл подсветка над дверью1
      digitalWrite(K10_doors2, LOW);                   //открывается дверь 1
      delay(2000);
      digitalWrite(K10_doors2, HIGH);
      flag = 12;
      Serial.println("flag=12 close the door");
    delay(100);
      dio_p=!dio;
    }
  }
  if(flag == 12){

    while(digitalRead(S4sens2_doors2)==HIGH){           //пока дверь1 открыта
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);

      if(language==1 && dio_p!=dio){                                    //в зависимости от языка прохождения вкл плеер и эффектами аудио "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (4);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_fading);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   
      }
      if(language==2&& dio_p!=dio){
        mp3_play (5);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_fading);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   
      }
      if(language==3&& dio_p!=dio){
      mp3_play (6);

      digitalWrite(SSerialTxControl, HIGH);
      Serial1.println(Master_Light_kor2_fading);
      delay(100);
      digitalWrite(SSerialTxControl, LOW);   
      }                                           
    }
    if(digitalRead(S4sens2_doors2)==LOW){                 //если дверь закрылась(Додати ДАТЧИК ДВИЖЕНИЯ)
      mp3_stop();
      flag = 13;  
      digitalWrite(K11_doors2_led, LOW);
      dio_p=!dio;
    }
  }
  //===========================КОРИДОР 1===========================================
  if(flag == 13 && flag_stroboscope == 1)
  {
    if(dio_p!=dio){
      Serial.println("flag=13 door is closed)");
    delay(100);
      dio_p=dio;
    }
    digitalWrite(K18_kor1_mute, HIGH);                     //вкл эфекты в кор1
    digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    mp3_set_volume(15);
    delay (100);                                   
    mp3_play (33);                                     // вкл плеєр з эффектами аудbо "крик"

    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Light_strob);               //фоторамки в коридоре 1 вниз
    delay(100);
    //Serial1.println(Master_Photos1_change);               //фоторамки в коридоре 1 вниз
    delay(100); //добавить вращение полки
    Serial1.println(Analog_window2_next);                 //в окне коридора 1 сменить видео
    delay(100);
    digitalWrite(SSerialTxControl, LOW);
    delay(14000);
    mp3_stop();

    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    Serial1.println(Master_Light_kor3);                 //вкл свет в коридоре 2
    delay(100);
    digitalWrite(SSerialTxControl, LOW);                 //передача данных

    mp3_set_serial (pl_musicSerial);                             //переключить на мп3 эфектов
    mp3_set_volume(18);
    delay (100);                                   
    mp3_play(3);                                     // вкл плеєр з эффектами аудио К3

    flag = 14;
    dio_p=!dio;
  }
  if(flag==14 && flag_mirror == 1){
    if(dio_p!=dio){
      Serial.println("flag=14 run mirror");
    delay(100);
      dio_p=dio;
    }

    time_phone = millis();
    functionPhoneRing();
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    delay (100);                                       // вкл плеєр з эффектами аудио "исповедь женщины" (НОМЕР УТОЧНИТЬ)
    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    delay(100);
    if(language==1){                                    //в зависимости от языка прохождения вкл плеєр c эффектами аудіо "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (10);
        
        digitalWrite(M8_mirror, LOW);
        delay(3500);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, LOW);
        delay(200);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, HIGH);
        flag=15;
      }
      if(language==2){
        mp3_play (11);

        digitalWrite(M8_mirror, LOW);
        delay(3500);
        digitalWrite(A6_mirror_Tx, LOW);
        digitalWrite(A7_mirror_Tx, HIGH);
        delay(200);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, HIGH);
        flag=15;
      }
      if(language==3){
        mp3_play (12);

        digitalWrite(M8_mirror, LOW);
        delay(3500);
        digitalWrite(A6_mirror_Tx, LOW);
        digitalWrite(A7_mirror_Tx, LOW);
        delay(200);
        digitalWrite(A6_mirror_Tx, HIGH);
        digitalWrite(A7_mirror_Tx, HIGH);
        flag=15;
      }
      delay(100);
      digitalWrite(SSerialTxControl, LOW);
      dio_p=!dio;
  }
  if(flag==15){
    if(dio_p!=dio){
      Serial.println("flag=15 lets play XO");
    delay(100);
      dio_p=dio;
    }
    
    if(flag_XO_bad == 1){
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (34);                                     // вкл плеєр з эффектами аудио "детский плач" (НОМЕР УТОЧНИТЬ)
      //- Запускається світловий ефект - мигання світла
      flag_XO_bad = 0;
    }
    if(flag_XO_good == 1){
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (36);                                     // вкл плеєр з эффектами аудио "детский смех" (НОМЕР УТОЧНИТЬ)
      delay(10000);
      flag = 16;
    }          
  }
  if(flag==16){
    Serial.println("flag=16 room3");
    delay(30000);

    digitalWrite(K3_doors1_led, HIGH);               //вкл подсветка над дверью2
    digitalWrite(K2_doors1, LOW);                   //открывается дверь 2
    delay(2000);
    digitalWrite(K2_doors1, HIGH);

    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println(Master_Light_kor1_fading);
    delay(100);
    digitalWrite(SSerialTxControl, LOW);   
    flag =17;
    dio_p=!dio;
  }
  if(flag==17){
      Serial.println("flag=17 uhodite v k4");
      delay(1000);
     digitalWrite(SSerialTxControl, HIGH);                 //передача данных
     Serial1.println(Master_Light_kor2);               //тусклый свет кор2
     while(digitalRead(S5sens1_doors1)==HIGH){           //пока дверь2 открыта
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);

      if(language==1 && dio_p!=dio){                                    //в зависимости от языка прохождения вкл плеєр c эффектами аудио "уходите" (НОМЕР УТОЧНИТЬ)
        mp3_play (4);
      }
      if(language==2 && dio_p!=dio){
        mp3_play (5);
      }
      if(language==3 && dio_p!=dio){
        mp3_play (6);
      }        
      dio_p=dio;
      digitalWrite(SSerialTxControl, LOW);   

    }
    if(digitalRead(S5sens1_doors1)==LOW){                 //если дверь закрылась(Додати ДАТЧИК ДВИЖЕНИЯ)
      delay(500);
      mp3_set_serial(pl_musicSerial);
      delay(50);
      mp3_stop();
      digitalWrite(K3_doors1_led, LOW);               //выкл подсветка над дверью1
      flag = 19; //where is 18?))
    }
  }

  //================================КОРИДОР 4==========================================
  if(flag==19){
    Serial.println("flag=19 run phone 2");
    delay(1000);

    digitalWrite(K18_kor1_mute, LOW);                     //выкл эфекты в кор1
    digitalWrite(K19_kor2_mute, HIGH);                     //вкл эфекты в кор2
    digitalWrite(K20_off_mute, LOW);                      //выкл эфекты в офисе
    mp3_set_serial(pl_musicSerial);
    mp3_set_volume(18);
    delay(50);
    mp3_play(4);

    digitalWrite(SSerialTxControl, HIGH);                 //передача данных
    delay(100);
    Serial1.println(Master_Light_kor4);             //вкл свет кор2
    //свет мигает
    delay(200);
    Serial1.println(Master_Phone2_start);             //звонок телефона
    delay(200);
    digitalWrite(SSerialTxControl, LOW);
    flag=20;
  }
  if(flag==20){
    if(flag_phone_good == 1){                         //если от телефона пришел сигнал good
    
      Serial.println("flag=20 phone good run radiola2");
      delay(100);

      digitalWrite(K15_stenka_k2of,LOW);                 //открывается фальш-стенка кор-офис
      delay(1000);
      
       if(language==1){                                    //в зависимости от языка прохождения вкл радиола 2
        digitalWrite(D48_Radiola2_Tx, LOW); //Radiola ru
        digitalWrite(D50_Radiola2_Tx, HIGH);
        delay(400);
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, HIGH); 

        flag=21;
      }
      if(language==2){
        digitalWrite(D48_Radiola2_Tx, HIGH); //en
        digitalWrite(D50_Radiola2_Tx, LOW);
        delay(400);
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, HIGH);

        flag=21;
      }
      if(language==3){
        digitalWrite(D48_Radiola2_Tx, LOW); //heb
        digitalWrite(D50_Radiola2_Tx, LOW);
        delay(400);
        digitalWrite(D48_Radiola2_Tx, HIGH);
        digitalWrite(D50_Radiola2_Tx, HIGH);

        flag=21;
      }
    }
  }
  if(flag==21){
    Serial.println("Radiola is playing, wait and open Lampa");
    delay(100);

    delay(20000);
    digitalWrite(A12_Lampa_Tx, HIGH); //lampa on
    digitalWrite(A13_Lampa_Tx, LOW);
    digitalWrite(A14_Lampa_Tx, LOW);
    delay(200);
    digitalWrite(A12_Lampa_Tx, HIGH);
    digitalWrite(A13_Lampa_Tx, HIGH);
    digitalWrite(A14_Lampa_Tx, HIGH);

    flag=22;
  }
  if(flag==22){
    if(flag_lampa_start==1){
      
      digitalWrite(A12_Lampa_Tx, HIGH); //lampa start
      digitalWrite(A13_Lampa_Tx, HIGH);
      digitalWrite(A14_Lampa_Tx, LOW);
      delay(200);
      digitalWrite(A12_Lampa_Tx, HIGH);
      digitalWrite(A13_Lampa_Tx, HIGH);
      digitalWrite(A14_Lampa_Tx, HIGH);

      flag=23;  
    }
  }
  if(flag==23){
    if(flag_lampa_bad == 1){

      mp3_set_serial(pl_musicSerial);
      mp3_set_volume(18);
      delay(50);
      //mp3_play();

      flag_lampa_bad = 0;
    }
    if(flag_lampa_good == 1){
      flag=24;
    }
  }
  if(flag==24){
    digitalWrite(K3_doors1_led, HIGH);               //вкл подсветка над дверью1
    digitalWrite(K2_doors1, LOW);                   //открывается дверь 1
    digitalWrite(K15_stenka_k2of,LOW);                 //открывается фальш-стенка кор1-офис

    flag=25;             
  }

 //===============================КОРИДОР 1======================================
  if(flag==25){
     if(digitalRead(S4sens2_doors2)==LOW){                 //если дверь закрылась (Додати ДАТЧИК ДВИЖЕНИЯ)
      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      delay(100);
      Serial1.println(Master_Light_office_on);               //вкл свет в офисе
      delay(100);
      Serial1.println(Master_Heart_1);                    //вкл серце скорость 1
      delay(100);
      Serial1.println(Master_Maski_on);                   //вкл маски майя
      delay(100);
      digitalWrite(SSerialTxControl, LOW);
      digitalWrite(K18_kor1_mute, LOW);                     //выкл эфекты в кор1
      digitalWrite(K19_kor2_mute, LOW);                     //выкл эфекты в кор2
      digitalWrite(K20_off_mute, HIGH);                      //вкл эфекты в офисе
      mp3_set_serial (pl_musicSerial);                       //переключить на мп3 музыка
      delay (100);                                            
      mp3_play (5);                                         //фоновая музыка                                         
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
      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      Serial1.println(Master_Heart_3);                    //вкл серце режиме 3
      flag=27;
    }
  }
  if(flag==27){
    if(flag_heart==1){
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (15);                                     // вкл плеєр c эффектами аудио "смерть" (НОМЕР УТОЧНИТЬ)
      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      Serial1.println(Master_Burzh_on);                  //вкл буржуйка
      flag=28;
    }
  }
  if(flag==28){
    delay(30000);                       //подобрать задержку 
    mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
    delay (100);                                   
    mp3_play (15);                                     // вкл плеєр c эффектами аудио "брось в огонь, сожги" (НОМЕР УТОЧНИТЬ)
    flag=29;
  }
  if(flag==29){
    if(flag_burzh_good = 1){
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
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
      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      Serial1.println(Analog_window2_next);                        //переключить видео в кор2
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
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);                                   
      mp3_play (17);                                     // вкл плеєр c  аудио "к выходу"  (НОМЕР УТОЧНИТЬ)
      flag=31;
    }
  }
   
  if(flag==31){
    if(digitalRead(S7_sens_moveK2)==HIGH){                             //если сработал датчик движения в кор2
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
      mp3_set_serial (pl_effectsSerial);                             //переключить на мп3 эфектов
      delay (100);
      mp3_stop();                                           //остановить аудио
      delay(100);
      mp3_set_serial (pl_musicSerial);                      //переключить на мп3 музыка
      delay (100);                                            
      mp3_stop ();                                         //остановить аудио
      digitalWrite(SSerialTxControl, HIGH);                 //передача данных
      Serial1.println(Master_Light_on);                     //вкл света
      Serial1.println(Master_Heart_off);                    //выкл серце
      Serial1.println(Master_Photos1_back);                 //фоторамки вверх
      Serial1.println("Master_Photos2_back");
      Serial1.println(Master_Window1_off);                  //выкл TV
      Serial1.println("Master_Window2_off");                   
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
  }
  while(millis()-time_stroboscope>10000 && millis()-time_stroboscope<15000){
  //stroboscope effect  	
  }
  
}

void functionAnalogCommunication()
{
  if(digitalRead(A4_window2_Rx) == LOW)
  {
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println("Window2 good");
    delay (50);                       
    digitalWrite(SSerialTxControl, LOW);
  }

  if(digitalRead(A5_window2_Rx) == LOW)
  {
    
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println("Window2 bad");
    delay (50);                              //  обязательная задержка между командами
    digitalWrite(SSerialTxControl, LOW);
  }

  if(digitalRead(A11_radiola1_Rx) == LOW)
  {
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println("Radiola good");
    delay(50);
    digitalWrite(SSerialTxControl, LOW);
  }

  if(digitalRead(A15_Lampa_Rx) == LOW && digitalRead(D52_Lampa_Rx) == HIGH)
  {
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println("Lampa good");
    delay(50);
    digitalWrite(SSerialTxControl, LOW);
  }

  if(digitalRead(A15_Lampa_Rx) == HIGH && digitalRead(D52_Lampa_Rx) == LOW)
  {
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial1.println("Lampa bad");
    delay(50);  
    digitalWrite(SSerialTxControl, LOW);
  }

  //Serial.print(digitalRead(S5sens1_doors1));
  //Serial.println(digitalRead(S4sens2_doors2));

}

