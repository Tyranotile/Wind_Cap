#include<Servo.h>
Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(12);
}

void loop() {
  int i;

  /*for (i = 55; i <= 95; i++) {
    myservo.write(i);
    delay(25);
  }
  delay(200);
  for (i = 95; i >= 55; i--) {
    myservo.write(i);
    delay(25);
  }
  delay(200);
  */
  myservo.write(55);
  delay(1000);
  myservo.write(95);
  delay(1000);
}