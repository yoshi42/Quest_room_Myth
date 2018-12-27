// LED Fire Effect

int ledPin1 = 9; //red
int ledPin2 = 10; //gree
int ledPin3 = 11; //blue

void setup()
{
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
analogWrite(ledPin3, 0);
}

void loop() {
analogWrite(ledPin1, random(120)+135);
analogWrite(ledPin2, random(120)+0);
delay(random(100));
}
