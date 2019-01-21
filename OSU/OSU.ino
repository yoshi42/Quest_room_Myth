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
String Master_Radio3_on_heb = "Master_Radio2_on_heb#";

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
//==============================================================================

SoftwareSerial pl_musicSerial(SSRxD24_pl_music, SSTxD22_pl_music); // RX, TX плеер музыKа
void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);                      //RS485
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    pl_musicSerial.begin(9600);               //плеер музыKа
    Serial2.begin(9600);                      // плеер эффеKты+теKст
    pinMode(S2_viselitsa, INPUT); 
    pinMode(S1_vikl, INPUT);  
    pinMode(S3_led, INPUT);   
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
  digitalWrite(SSerialTxControl, HIGH);
  Serial1.println(Master_Heart_1);
  delay(1000);
  if (Serial1.available()) {
    string_reply = "";
    delay(100);
    tx();
 }
 
 if (Serial.available()) {
    string = "";
    delay(100);
    txSerial();
 }

}

void tx() {                          // розпізнання Kоманди
  digitalWrite(SSerialTxControl, LOW);
  while (Serial1.available())
  {
    char inChar = Serial1.read();
    string_reply += inChar;
    if (inChar == '#') 
    {
      Serial.println(string_reply);
      
    string_reply = "";
    }

  }

}


void txSerial() {                          // розпізнання Kоманди
  digitalWrite(SSerialTxControl, LOW);
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(Master_Heart_on))
      {
        digitalWrite(13, HIGH);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_on);
        delay(100);
      }
      if (string.equals(Master_Heart_1))
      {
        digitalWrite(13, HIGH);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_1);
        delay(100);
      }
      if (string.equals(Master_Heart_2) )
      {
        digitalWrite(13, LOW);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_2);
        delay(100);
      }
      if (string.equals(Master_Heart_3) )
      {
        digitalWrite(13, HIGH);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_3);
        delay(100);
      }
      if (string.equals(Master_Heart_dead) )
      {
        digitalWrite(13, LOW);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_dead);
        delay(100);
      }
      if (string.equals(Master_Heart_off) )
      {
        digitalWrite(13, HIGH);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_off);
        delay(100);
      }
      if (string.equals(Master_Heart_open) )
      {
        digitalWrite(13, HIGH);
        digitalWrite(SSerialTxControl, HIGH);
        Serial1.println(Master_Heart_open);
        delay(100);
      }      
    string = "";
    }

  }

}
