//This is the code that i showed during our meeting. To wire the driver for the acctuator to the arduino, 
//attach one of the - terminals of the driver to a GND pin on the arduino.
//Then attach the RC pin of the driver to pin 9 of the arduino. Then connect the other - terminal and the + terminal of the driver to a 12V supply. 
//There is an ac to 12VDC wall converter in one of our boxes. This works fine. 
//To use the code, first upload it to the baord then go to tools and select serial monitor. 
//from the serial monitor you can type what position you want the acctuator to go to. 



#include<Servo.h>
Servo myservo;

int pos;

void setup(){
  Serial.begin(9600);
  myservo.attach(12);
  




}
void loop(){
  Serial.println("Enter pos:");
  while(Serial.available() == 0){}
  pos = Serial.readString().toInt();
  if(pos>=0 && pos <= 180){
    myservo.write(pos);
    Serial.println("Servo at pos:");
    Serial.println(pos);
  }
else{
  Serial.println("invalid");
}
}
