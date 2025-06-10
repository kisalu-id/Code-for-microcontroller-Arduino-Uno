#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2); //16 columns, 2 rows

#include <Servo.h>    
Servo jalousieServo;  
//Servo BeamerwandServo;  //TODO: ?

//pin declarations
const int SERVO_PIN = 6

const int LED_PIN = 9             //LED
const int LIGHT_SENSOR = A0       //LDR or light sensor ???
const int DIMMER_SENSOR = 9;      //TODO: implement

const int BTN_PIN = 5;            //btn to start the meeting 

const int TEMP_SENSOR = A0;       //temperature sensor
const int FAN_PWM_PIN = 9;        //PWM output for the fan

const int SEND_PIN_DOOR = 3;      //send an ultrasonic pulse from the sensor to measure distance
const int ECHO_PIN_DOOR = 4;      //receives the reflected ultrasonic pulse - if shorter than set up, the door was opened or someone is in the room

const int SEND_PIN_HOOMAN = 3;    //send an ultrasonic pulse from the sensor to measure distance to the wall

const int POT_PIN = A10;          //potentiometer

//variables for storing measurement values
bool turnOn = true; //global toggle for turn on/off the "meeting mode" (with Beamerwand, etc.)
int currentBrightness = 0;
int fanSpeed = 0;
float temperature = 0;
float lastValidTemperature = 0;
int lastPotValue = 0;
int dimmerValue = 0
int duration;
int distance;

const int distanceNoPersonInRoom = 5;  //lets say, dist for an empty room is 5 cm
const int distanceForOpenedDoor = 3;






void jalousieMove(bool turnOn) {
  Serial.println("Moving jalousie: ");
  Serial.println(turnOn);
  if (turnOn) {
    //pull down with servomotor
    jalousieServo.write(90);
  }
  else {
    //pull up
    jalousieServo.write(0);
  }
  delay(1000);
}


void BeamerwandMove(bool turnOn) {
  Serial.println("Moving Beamerwand: ");
  Serial.println(turnOn);
  if (turnOn) {
    //pull down with servomotor
    jalousieServo.write(90);
  }
  else {
    //pull up
    jalousieServo.write(0);
  }
  delay(1000);  //time to move
}
