int stp = 13; //подключите 13 пин к step
int dir = 12; //подключите 12 пин к dir

int key1 = 9;
int but1 = 10;
int but2 = 11;
int sens1 = 8;

int speed = 3000;

void setup()

{
  Serial.begin(9600);

  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
}

void loop()
{  
  Serial.print("but1 = ");
  Serial.print(digitalRead(but1));
  Serial.print("  ");
  Serial.print("but2 = ");
  Serial.print(digitalRead(but2));
  Serial.println("  sens1 = ");
  //Serial.println(digitalRead(sens1));
  
  if(digitalRead(but1)==0){
        digitalWrite(dir, LOW);
        
        for(int a=0; a<10; a++){
          digitalWrite(stp, HIGH);
          delayMicroseconds(speed);
          digitalWrite(stp, LOW);
          delayMicroseconds(speed);
        }
  }

  if(digitalRead(but2)==0){
        digitalWrite(dir, HIGH);
        
        for(int a=0; a<10; a++){
          digitalWrite(stp, HIGH);
          delayMicroseconds(speed);
          digitalWrite(stp, LOW);
          delayMicroseconds(speed);
        }
  }

  /*if(digitalRead(but2)==0)  {
        digitalWrite(key1, HIGH);
        delay(200);
        digitalWrite(key1, LOW);
  }*/
}
