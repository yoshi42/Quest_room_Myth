//#include <SoftwareSerial.h>
//#define SSerialRX        0  //Serial Receive pin
//#define SSerialTX        1  //Serial Transmit pin
#define SSerialTxControl 2   //RS485 Direction control

#define photos1_out3 3
#define photos1_out4 4
#define projector_out5 5
#define projector_out6 6
#define projector_out7 7
#define burzh_out8 8
#define burzh_out9 9
#define out10 10
#define out11 11
#define out12 12
#define out13 13

#define photos1_in0 A0
#define photos1_in1 A1
#define burzh_in2 A2
#define in3 A3
#define in4 A4
#define in5 A5
#define in6 A6
#define in7 A7

String Master_Photos1_on = "Master_Photos1_on#";                  // фоторамKи
String Master_Photos1_change = "Master_Photos1_change#";
String Master_Photos1_back = "Master_Photos1_back#";

String Slave_Photos1_goodParole = "Slave_Photos1_goodParole#";        //фоторамKи-KнопKи
String Slave_Photos1_badParole = "Slave_Photos1_badParole#";

String Master_Projector_on = "Master_Projector_on#";                            //прожектор
String Master_Projector_start1 = "Master_Projector_start1#";
String Master_Projector_stop = "Master_Projector_stop#";
String Master_Projector_start2 = "Master_Projector_start2#";
String Master_Projector_off = "Master_Projector_off#";


String Master_Burzh_on = "Master_Burzh_on#";                      //буржуйка
String Master_Burzh_off = "Master_Burzh_off#";
String Master_Burzh_open = "Master_Burzh_open#";
String Slave_Burzh_good = "Slave_Burzh_good#";

String string0 = "led_on#";
String stringgood = "photos1_in1LOW#";

String string;
//SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup()
{
    Serial.begin(9600);
    pinMode(SSerialTxControl, OUTPUT); 
    digitalWrite(SSerialTxControl, LOW); 
    //RS485Serial.begin(9600);

    pinMode(photos1_out3, OUTPUT);
    pinMode(photos1_out4, OUTPUT);
    pinMode(projector_out5, OUTPUT);
    pinMode(projector_out6, OUTPUT);
    pinMode(projector_out7, OUTPUT);
    pinMode(burzh_out8, OUTPUT);
    pinMode(burzh_out9, OUTPUT);
    pinMode(out10, OUTPUT);
    pinMode(out11, OUTPUT);
    pinMode(out12, OUTPUT);
    pinMode(out13, OUTPUT);
    digitalWrite(photos1_out3, HIGH);
    digitalWrite(photos1_out4, HIGH);
    digitalWrite(projector_out5, HIGH);
    digitalWrite(projector_out6, HIGH);
    digitalWrite(projector_out7, HIGH);
    digitalWrite(burzh_out8, HIGH);
    digitalWrite(burzh_out9, HIGH);
    digitalWrite(out10, HIGH);
    digitalWrite(out11, HIGH);
    digitalWrite(out12, HIGH);
    digitalWrite(out13, HIGH);
    
    pinMode(photos1_in0, INPUT_PULLUP);
    pinMode(photos1_in1, INPUT_PULLUP);
    pinMode(burzh_in2, INPUT_PULLUP);
    pinMode(in3, INPUT_PULLUP);
    pinMode(in4, INPUT_PULLUP);
    pinMode(in5, INPUT_PULLUP);
    pinMode(in6, INPUT_PULLUP);
    pinMode(in7, INPUT_PULLUP);

}

void loop() {
  digitalWrite(SSerialTxControl, LOW);
  if(Serial.available()){
    string = "";
    delay(100);
    tx(); 
  }
  //photos1 good bad//
  if(digitalRead(photos1_in0) == HIGH && digitalRead(photos1_in1) == LOW) //Photos1 good
  {
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial.println(Slave_Photos1_goodParole);
    delay(1000);
    digitalWrite(SSerialTxControl, LOW);  
  }

  if(digitalRead(photos1_in0) == LOW && digitalRead(photos1_in1) == HIGH) //Photos1 bad
  {
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial.println(Slave_Photos1_badParole);
    delay(1000);
    digitalWrite(SSerialTxControl, LOW);  
  } 
  if(digitalRead(burzh_in2) == LOW){             //Burzh_good
    delay(50);
    digitalWrite(SSerialTxControl, HIGH);
    Serial.println(Slave_Burzh_good);
    delay(1000);
    digitalWrite(SSerialTxControl, LOW);
  }
}

void tx() {                          // розпізнання команди
  digitalWrite(SSerialTxControl, LOW);
  while (Serial.available())
  {
    char inChar = Serial.read();
    string += inChar;
    if (inChar == '#') 
    {
      if (string.equals(string0))
      {
          digitalWrite(out13, LOW);
          delay(1500);
          digitalWrite(out13, HIGH);
      }  

      if (string.equals(Master_Photos1_on))
      {
          digitalWrite(photos1_out3, LOW);
          digitalWrite(photos1_out4, LOW);
          delay(500);
          digitalWrite(photos1_out3, HIGH);
          digitalWrite(photos1_out4, HIGH);
      }   

      if (string.equals(Master_Photos1_change))
      {
          digitalWrite(photos1_out3, HIGH);
          digitalWrite(photos1_out4, LOW);
          delay(500);
          digitalWrite(photos1_out3, HIGH);
          digitalWrite(photos1_out4, HIGH);
      }   

      if (string.equals(Master_Photos1_back))
      {
          digitalWrite(photos1_out3, LOW);
          digitalWrite(photos1_out4, HIGH);
          delay(500);
          digitalWrite(photos1_out3, HIGH);
          digitalWrite(photos1_out4, HIGH);
      }  
      if (string.equals(Master_Projector_on))
      {
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, LOW);
          delay(500);
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, HIGH);
      }  
      if (string.equals(Master_Projector_start1))
      {
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, LOW);
          digitalWrite(projector_out7, HIGH);
          delay(500);
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, HIGH);
      }
      if (string.equals(Master_Projector_stop))
      {
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, LOW);
          digitalWrite(projector_out7, LOW);
          delay(500);
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, HIGH);
      }  
      if (string.equals(Master_Projector_start2))
      {
          digitalWrite(projector_out5, LOW);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, HIGH);
          delay(500);
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, HIGH);
      }if (string.equals(Master_Projector_off))
      {
          digitalWrite(projector_out5, LOW);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, LOW);
          delay(500);
          digitalWrite(projector_out5, HIGH);
          digitalWrite(projector_out6, HIGH);
          digitalWrite(projector_out7, HIGH);
      }
      
      if (string.equals(Master_Burzh_on))
      {
          digitalWrite(burzh_out8, HIGH);
          digitalWrite(burzh_out9, LOW);
          delay(500);
          digitalWrite(burzh_out8, HIGH);
          digitalWrite(burzh_out9, HIGH);
      } 
      if (string.equals(Master_Burzh_off))
      {
          digitalWrite(burzh_out8, LOW);
          digitalWrite(burzh_out9, HIGH);
          delay(500);
          digitalWrite(burzh_out8, HIGH);
          digitalWrite(burzh_out9, HIGH);
      } 
      if (string.equals(Master_Burzh_open))
      {
          digitalWrite(burzh_out8, LOW);
          digitalWrite(burzh_out9, LOW);
          delay(500);
          digitalWrite(burzh_out8, HIGH);
          digitalWrite(burzh_out9, HIGH);
      } 
     


    string = "";
    }
  }
loop();
}

