void setup()
{
  pinMode(A0, OUTPUT);
}

void loop ()
{
  analogWrite(A0, 0);
  delay(2000);
  analogWrite(A0, 125);
  delay(3000);
}