int Distance = 0; // записываем количество шагов, которое было совершено

void setup() {

pinMode(8, OUTPUT);

pinMode(9, OUTPUT);

digitalWrite(8, LOW);

digitalWrite(9, LOW);

}

void loop() {

digitalWrite(9, HIGH);

delayMicroseconds(1500);

digitalWrite(9, LOW);

delayMicroseconds(1500);

Distance = Distance + 1; // записываем этот шаг

// проверяем, не находимся ли мы в конце перемещения

// два поворота при мосте 1/8 и 1 поворот для моста 1/6 (для этого скетча)

if (Distance == 12800) { // Мы добрались до крайней точки, начинаем вращение в противоположном направлении

if (digitalRead(8) == LOW) {

digitalWrite(8, HIGH); }

else {

digitalWrite(8, LOW);

} // Обнуляем расстояние, так как мы начинаем новое движение

Distance = 0;

// Делаем паузу на пол секунды

delay(2000);

}

}

