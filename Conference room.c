#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2); //16 columns, 2 rows

#include <Servo.h>    
Servo jalousieServo;  
Servo beamerwandServo;
//Servo BeamerwandServo;  //TODO: ?

//pin declarations
const int JAL_SERVO = 5;
const int BEAM_SERVO = 8;

const int LED_PIN = 9             //LED
const int LIGHT_SENSOR = A0;       //LDR or light sensor ???
const int DIMMER_SENSOR = 9;      //TODO: implement

const int BTN_PIN = 2;            //btn to start the meeting 

const int TEMP_SENSOR = A0;       //temperature sensor
const int FAN_PWM_PIN = 9;        //PWM output for the fan

const int SEND_PIN_DOOR = 3;      //send an ultrasonic pulse from the sensor to measure distance
const int ECHO_PIN_DOOR = 4;      //receives the reflected ultrasonic pulse - if shorter than set up, the door was opened or someone is in the room

const int SEND_PIN_HOOMAN = 3;    //send an ultrasonic pulse from the sensor to measure distance to the wall


//variables for storing measurement values
bool turnOn = true; //global toggle for turn on/off the "meeting mode" (with Beamerwand, etc.)
int currentBrightness = 0;
int fanSpeed = 0;
float temperature = 0;
float lastValidTemperature = 0;
int lastPotValue = 0;
int dimmerValue = 0;
int duration;
int distance;

const int POT_CHANGE_THRESHOLD = 15;
const unsigned long INACTIVITY_TIME = 3000;
unsigned long lastChangeTime = 0;
bool dimmerActive = false;

const int distanceNoPersonInRoom = 5;  //lets say, dist for an empty room is 5 cm
const int distanceForOpenedDoor = 3;

//TODO: learn millis()  
//the number of milliseconds that have passed since your Arduino started running the current program
//millis() will overflow after ~50 days.
//But this is handled safely as long as unsigned long for time comparisons is used
//const unsigned long PERSON_CHECK_INTERVAL = 1000;     // check for person every 1s              //AI
//const unsigned long DOOR_RECHECK_DELAY = 100;         // delay if door check fails              //AI
//const unsigned long PERSON_TIMEOUT = 30000;           // timeout if no person detected (30s)    //AI


//learn memory stuff

//Arduino Uno has very limited SRAM (2 KB) for variables during runtime.
//If you put constant data (like strings, lookup tables, big arrays) as normal variables, they use precious SRAM.
//But Arduino has 32 KB flash memory (program memory), which is much bigger and ideal to store constants.
//

//1. Using const
//On Arduino, simple const like const int x = 5; often gets stored in flash automatically.
//But for arrays or strings, const alone does not guarantee storage in flash — they might still be copied into SRAM at runtime.

//2. Using PROGMEM
//PROGMEM is a special macro telling the compiler to put data directly into flash memory.
//You use it for large constant arrays, strings, or lookup tables.


void setup() {
  Serial.begin(9600);
  LCD.init();                      //initialize the lcd, turn on the light
  LCD.backlight();
  jalousieServo.attach(JAL_SERVO); //AI
  beamerwandServo.attach(JAL_SERVO);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(DIMMER_SENSOR, INPUT);

  pinMode(TEMP_SENSOR_PIN, INPUT);
  pinMode(FAN_PWM_PIN, OUTPUT);

  pinMode(BTN_PIN, INPUT_PULLUP);   //AI

  pinMode(SEND_PIN_DOOR, OUTPUT);
  pinMode(ECHO_PIN_DOOR, INPUT);

  pinMode(SEND_PIN_HOOMAN, OUTPUT);
  pinMode(ECHO_PIN_HOOMAN, INPUT);

  //initialize serial communication at 9600 baud
  //Baud rate - the speed at which data is transmitted or received over a communication channel, such as serial communication.
  //It represents the number of signal changes (or symbols) per second.
  //In the context of Arduino, 9600 baud means that the data is transmitted at a rate of 9600 bits per second (bps)
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



int buttonWasPressed() {
  if (digitalRead(BNT_PIN) == HIGH) {
    delay(50);                           //AI, debounce delay 0,5 sek
    if (digitalRead(BNT_PIN) == HIGH) {  //AI
      Serial.println("button pressed");
      return 1;
    }
  }
  return 0;
}
