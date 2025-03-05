// This code will allow us to control boh actuators using serial commands, to use this code, open serial monitor and enter the command. 
//The commands are as follows, for actuator 1 1 and 2 move it +/- 50 and 3 and 4 more it +/- 10 and 5 and 6 move it +/- 1.
//for actuator 2, 7 and 8 move it +/- 50 and 9 and 10 move it +/- 10 and 11 and 12 move it +/- 1
//This code is meant to make testing easier we can do fine movements to ensure that we are acheiving the disered pitching and breaking that is required of us. 

#include <Servo.h> //include servo library
Servo myservo;//create object for servo1
Servo myservo2; 

int pos = 10;//initialize pos for servo 1
int pos2 = 10;





void setup() {
  Serial.begin(9600);
  myservo.attach(12);
  myservo2.attach(9);
  pos = 10;
  pos2 = 10;
  myservo.write(pos);
  myservo2.write(pos2);
 


}

void loop() {
  Serial.println("enter value from 1 to 12 to move servo 1 or 2:");
  while(Serial.available() == 0){}
    char ch = Serial.readString().toInt();
    

    

    if(ch == 1 ){
      pos = pos + 50;
      myservo.write(pos);
      

    }
    if(ch == 2 ){
      pos = pos - 50;
      myservo.write(pos);
      


    }
    if(ch == 3 ){
      pos = pos + 10;
      myservo.write(pos);
      

    }
    if(ch == 4){
      pos = pos - 10;
      myservo.write(pos);
      

    }
    if(ch == 5 ){
      pos = pos + 1;
      myservo.write(pos);
    }
    if(ch == 6 ){
      pos = pos - 1;
      myservo.write(pos);
    }
    if(ch == 7){
      pos2 = pos2 + 50;
      myservo2.write(pos2);

    }
    if(ch ==8){
      pos2 = pos2 - 50;
      myservo2.write(pos2);
    }
    if(ch == 9 ){
      pos2 = pos2 + 10;
      myservo2.write(pos2);

    }
    if(ch == 10 ){
      pos2 = pos2 - 10;
      myservo2.write(pos2);
    }
    if(ch == 11 ){
      pos2 = pos2 + 1;
      myservo2.write(pos2);

    }
    if(ch == 12 ){
      pos2 = pos2 - 1;
      myservo2.write(pos2);
    }
  Serial.println(pos);
  Serial.println(pos2);
  delay(1000);
  
  
} 