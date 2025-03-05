#include<Servo.h> //library used to control actuators
#include<Wire.h>  //if needed included i2c library, research I2C, gonna need
//Add Timer1 Library for easy timer funcs

Servo Brake; // make object for break actuator (Changing system, leave for now)
Servo Pitch; // make object for pitch actuator

//Check the calculations for ALL

int movementTimer = 500; //timer to allow for actuator movement
int interruptTimer = 1000; // timer used for interrupt function
int Timer = 100; // general timer
int cutinTimer = 1000; // allow time for cut in voltage to be reached
int cutinVoltage = 1; // cut in voltage needs to be adjusted as needed
float vol1 = analogRead(A3); // 8 bit value from voltage sensor
float vol2 = (vol1/40.97); //converted to actual voltag being read
float cur1 = analogRead(A4); //this is going to be our check for load connection
float cur2 = (cur1/50); //  need to figure out what the correct factor is for this but this will be our actual current going to the load, 
                        //  if this drops to zero the load is open and we need to stop the system. 
int startTime = 0; // initiate start time
int endTime = 0; // initiate end time
int Rev = 0; // initiate Revolutions
int RPM = 0; // initiate RPM
int rev = 0; // rev = Rev/3
const int signal = 2; // attach hall effect to pin 2
const int eBrake = 3; // attach eBreak to pin 3
int IntBrakepos = 0; // initiate brake pos
int IntPitchpos = 60; // initiate pitch pos
int FullyBraked = 50; // the remaining vales are different variables used during the code
int FullyPitched = 85;
int SpeedupPitch = 60;
int SlowdownPitch = 85;
int slowRPM = 500;
int fastRPM = 1800;

void setup() {
  Serial.begin(9600); //begin serial
  Wire.begin(); // begin i2c
  Brake.attach(8); // attach brake to pin 8
  Pitch.attach(9); // attach pitch to pin 9
  pinMode(signal, INPUT_PULLUP); //set signal as input
  pinMode(eBrake, INPUT); // set eBreak as input
}

void loop() {
  Brake.write(IntBrakepos); //move to initial brake pos
  Pitch.write(IntPitchpos); // move to initial pitch pos
  delay(movementTimer); 

  if(vol2 >= cutinVoltage){ //check that cut-in voltage is reached
    delay(cutinTimer);
    digitalRead(eBrake);
    if(eBrake != HIGH){ // check that eBrake is not pressed
      if(cur2 >= 1){ // check to make sure that the load is connected
        Rev = 0;
        RPM = 0;
        startTime = millis();
        attachInterrupt(digitalPinToInterrupt(signal), interrupt1, FALLING); //attach signal to interrupt1 function on falling edge
        delay(interruptTimer);
        detachInterrupt(signal);
          if(Rev > 0){ 
            rev = (Rev / 3);
            RPM = (rev * 60000) / (endTime); //calculate RPM based on number of revolutions
            Serial.println(RPM);
          }

          if(RPM < slowRPM){ //check RPM
            Break.write(IntBrakepos);
            Pitch.write(SpeedupPitch);
            Serial.println(RPM);
            delay(movementTimer);
          }
      
          if(RPM > fastRPM){ //check RPM
            Break.write(IntBrakepos);
            Pitch.write(SlowdownPitch);
            Serial.println(RPM);
            delay(movementTimer);
          }
      }

      else{
        Break.write(FullyBraked);
        Pitch.write(FullyPitched);
        Serial.println("LOAD Disconnected");
        delay(movementTimer);
      }
    }

    else{ //if eBrake is pressed
      Break.write(FullyBraked);
      Pitch.write(FullyPitched);
      Serial.println("E-Brake Engaged");
      delay(movementTimer);
    }
  }

  else{ //if cut-in voltage is not reached
    Break.write(FullyBraked);
    Pitch.write(FullyPitched);
    Serial.println("Cut In Voltage not Reached");
    delay(movementTimer);
  }
  delay(Timer);
}

void interrupt1(){ //interrupt function
  Rev++;
}