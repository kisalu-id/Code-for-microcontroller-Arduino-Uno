/*
 Titel: Automatische Lüftersteuerung für Serverräume
 Beschreibung: Dieses Projekt misst die Temperatur eines Serverraums mit einem TMP36-Sensor
 und steuert einen Lüfter über PWM. Ein Ultraschallsensor erkennt Personen in der Nähe
 und schaltet den Lüfter ab, um Energie zu sparen und Lärm zu reduzieren.
 Verwendete Hardware: Arduino Mega 2560, TMP36 Temperatursensor, 5V PWM-gesteuerter Lüfter, 
 HC-SR04 Ultraschall-Abstandssensor, 16x2 LCD mit I2C, Widerstände, Breadboard
 */


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2);

//pin declarations
int TEMP_SENSOR = A0;  //temperature sensor
int FAN_PWM_PIN = 9;   //PWM output for the fan
int SEND_PIN = 3;      //send an ultrasonic pulse from the sensor to measure distance
int ECHO_PIN = 4;      //receives the reflected ultrasonic pulse

//storing measurement values
double temperature = 0;
int duration;
long distance;
int fanSpeed = 0;

void setup() {
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(SEND_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  LCD.init();   //initialize the lcd, turn on the light
  LCD.backlight();
  //initialize serial communication at 9600 baud
  //Baud rate - the speed at which data is transmitted or received over a communication channel, such as serial communication.
  //It represents the number of signal changes (or symbols) per second.
  //In the context of Arduino, 9600 baud means that the data is transmitted at a rate of 9600 bits per second (bps)
  Serial.begin(9600);
}

void loop() {
  temperature = getTemperature();
  distance = getDistance();
  
  //fan speed settings
  if (distance < 1) {    //1 meter
    fanSpeed = 0;   //turns off the fan if a someone is nearby
  } else if (temperature < 20) {
    fanSpeed = 0; //turns off the fan at very low T
  } else if (temperature >= 20 && temperature < 25) {
    fanSpeed = 80; //low speed for medium T
  } else if (temperature >= 25 && temperature < 30) {
    fanSpeed = 160; //medium speed for warmer T
  } else {
    fanSpeed = 255; //maximum speed at high T
  }
  analogWrite(FAN_PWM_PIN, fanSpeed);

  LCD.clear();
  LCD.setCursor(0, 0); //start to print at the first row & first line
  LCD.print(temperature);
  LCD.print(" C;");
  LCD.setCursor(0, 1); //print at the first row & second line
  LCD.print(distance);
  LCD.print(" cm");

  delay(1000);
}

//function to measure temperature with the TMP36 sensor
//reads the analog input and calculates the temperature in C
float getTemperature() {
  int sensorValue = analogRead(TEMP_SENSOR);
  float voltage = sensorValue * (5.0 / 1023.0); //to V
  return (voltage - 0.5) * 100.0; //to T, Celsius
}

//measure distance with the HC-SR04 ultrasonic sensor, returns he distance
int getDistance() {
    digitalWrite(SEND_PIN, LOW);   //initializing the sensor
    delayMicroseconds(2);          //wait to make sure initialization was correct

    digitalWrite(SEND_PIN, HIGH);  //send the signal
    delayMicroseconds(10);         //

    digitalWrite(SEND_PIN, LOW);   //turn off
    duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.017 / 2;   //to cm
}
