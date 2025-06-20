#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2); //16 columns, 2 rows

#include <Servo.h>    
Servo jalousieServo;  
Servo beamerwandServo;

//pin declarations
const int LED_PIN = 3;            //LED
const int LIGHT_SENSOR = A2;      //LDR or light sensor ???
const int DIMMER_SENSOR = A0;      //TODO: implement

const int BTN_PIN = 2;            //btn to start the meeting 

const int TEMP_SENSOR = A1;       //temperature sensor
const int FAN_PWM_PIN = 11;        //PWM output for the fan to cool down the room if it's too hot

const int SEND_PIN_DOOR = 9;      //send an ultrasonic pulse from the sensor to measure distance
const int ECHO_PIN_DOOR = 10;      //receives the reflected ultrasonic pulse - if shorter than set up, the door was opened or someone is in the room

const int SEND_PIN_HOOMAN = 12;    //send an ultrasonic pulse from the sensor to measure distance to the wall
const int ECHO_PIN_HOOMAN = 13;

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




//easy but effective sorting algorithm
int bubbleSort(int n, float arrayTemp[]) {
  float temp;
  for (int i=0; i<n-1; i++) {
    for (int j=0; j<n-i-1; j++) {
      if (arrayTemp[j] > arrayTemp[j+1]) {
        //swap elements, if they're in wrong order
        temp = arrayTemp[j];
        arrayTemp[j] = arrayTemp[j+1];
        arrayTemp[j+1] = temp;
      }
    }
  }    //the array is being modified in place, so there's no need to return it
}


//function to measure temperature with the TMP36 sensor
//reads the analog input and calculates the temperature in C
float getTemperature() {
  //int sensorValue = analogRead(TEMP_SENSOR);
  //float voltage = sensorValue * (5.0 / 1024.0);  //to V, Volt
  //return (voltage - 0.5) * 100.0;    //to T, Celsius
  return analogRead(TEMP_SENSOR) * 0.48828125 - 50.0; //AI; combining constants to reduce runtime math
}


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
