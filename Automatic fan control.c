/*
DE:
 Titel: Automatische Lüftersteuerung für Serverräume
 Beschreibung: Dieses Projekt misst die Temperatur eines Serverraums mit einem TMP36-Sensor
 und steuert einen Lüfter über PWM. Ein Ultraschallsensor erkennt Personen in der Nähe
 und schaltet den Lüfter ab, um Energie zu sparen und Lärm zu reduzieren.
 Verwendete Hardware: Arduino Mega 2560, TMP36 Temperatursensor, 12V PWM-gesteuerter Lüfter, 
 HC-SR04 Ultraschall-Abstandssensor, 16x2 LCD mit I2C, Breadboard, Kabel
*/

/*
ENG:
 Title: Automatic Fan Control for Server Rooms
 Description: This project measures the temperature of a server room using a TMP36 sensor
 and controls a fan via PWM. An ultrasonic sensor detects people nearby
 and turns off the fan to save energy and reduce noise.
 Used Hardware: Arduino Mega 2560, TMP36 Temperature Sensor, 12V PWM-controlled Fan,
 HC-SR04 Ultrasonic Distance Sensor, 16x2 LCD with I2C, Breadboard, Wires
*/

 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2);

//pin declarations
int TEMP_SENSOR = A0;  //temperature sensor
int FAN_PWM_PIN = 9;   //PWM output for the fan
int SEND_PIN = 3;      //send an ultrasonic pulse from the sensor to measure distance
int ECHO_PIN = 4;      //receives the reflected ultrasonic pulse
  
//variables for storing measurement values
float temperature = 0;
float lastValidTemperature;
int duration;
int distance;
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
  //for the first iteration, get the first valid measurment 
  if (temperature == 0) {
    temperature = calibrateTemperature(); //calibrate and store first temperature
    lastValidTemperature = temperature;
  }

  //for following iterations
  else {
    //get the next measurment
    temperature = getTemperature();

    //check if the next measurment is significantly different than the previous one
    //with the help of the abs() function, which gets the absolute value
    if (abs(temperature - lastValidTemperature) > 5.0) {
      //if it's a large change, calibrate again and store the new valid temperature
      temperature = calibrateTemperature();
      lastValidTemperature = temperature;
    }
  }

  distance = getDistance();
  
  //fan speed settings
  if (distance == 404) {   //if these's an error in reading the distance, turn off the fan (just in case)
    fanSpeed = 0; 
  } else if (distance < 50) {  //50 cm
    fanSpeed = 0;   //turns off the fan if a someone is nearby
  } else if (temperature < 20) {
    fanSpeed = 0;   //turns off the fan at very low T
  } else if (temperature >= 20 && temperature < 25) {
    fanSpeed = 80;  //low speed for medium T
  } else if (temperature >= 25 && temperature < 30) {
    fanSpeed = 160; //medium speed for warmer T
  } else {
    fanSpeed = 255; //maximum speed at a very high T
  }

  analogWrite(FAN_PWM_PIN, fanSpeed);

  LCD.clear();  //clear the display - TODO: check, if that's really necessary
  LCD.setCursor(0, 0);  //start to print at the first row & first line
  LCD.print(temperature);
  LCD.print(" C;");

  LCD.setCursor(0, 1); //print at the first row & second line
  if (distance != 404) {
    //if the distance is valid (not 404), display it
    LCD.print(distance);
    LCD.print(" cm");
  } else {
    //if the distance is 404 (invalid), display "Error" on the LCD screen
    LCD.print("Error");
  }

  //serial monitor print
  Serial.print(temperature);
  Serial.print(" C;   ");
  if (distance != 404) {
    //if the distance is valid (not 404), display it
    Serial.print(distance);
    Serial.print(" cm");
  } else {
    //f the distance is 404 (invalid), display "Error" on the serial monitor
    Serial.print("Error");
  }
  Serial.println();

  delay(988); //in function getDistance() we wait 12 ms; the program has to output values each second
}

//there's a problem, that sometimes we get temperature fluctuations, which are not realistic for typical room temperatures: 
//29.18 C; 49.22 C; 41.89 C; 60.95 C; 30.65 C; 8.16 C; 20.38 C;
//the solution to that is sorting several measurments and taking one from the middle of the array
float calibrateTemperature() {
  //get 10 temperature measurments
  Serial.print("Calibrating temperature: ");
  //n = number of mesurments, should be minimum 7
  int n = 10;
  float arrayTemp[n];
  for (int i=0; i<n; i++) {
    arrayTemp[i] = getTemperature();
  }

  //sort an array with bubble sort
  bubbleSort(n, arrayTemp);

  for (int i=0; i<n; i++) {
    Serial.print(arrayTemp[i]);
    Serial.print(";  ");
  }
  Serial.println();

  //take the one in the middle as the correct one
  //both odd and even numbers for n will work
  int nMid = n; //middle on an array
  nMid >>= 1; //same as nMid = n / 2
  Serial.print(++nMid); //same as  nMid + 1
  Serial.print(" is the measurment number from the middle of the array, the value is: ");
  Serial.print(arrayTemp[nMid]);
  Serial.println();

  return arrayTemp[nMid];
}

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
  int sensorValue = analogRead(TEMP_SENSOR);
  float voltage = sensorValue * (5.0 / 1024.0);  //to V, Volt
  return (voltage - 0.5) * 100.0;    //to T, Celsius
}

//measure distance with the HC-SR04 ultrasonic sensor, returns he distance
int getDistance() {
  digitalWrite(SEND_PIN, LOW);   //initializing the sensor
  delayMicroseconds(2);          //wait to make sure initialization was correct

  digitalWrite(SEND_PIN, HIGH);  //send the signal
  delayMicroseconds(10);         //wait 10 ms

  digitalWrite(SEND_PIN, LOW);   //turn off
  duration = pulseIn(ECHO_PIN, HIGH);

  //convert to distance (in cm)
  //if only you knew that AVR can't divide...
  int dist = duration * 0.034 / 2;

  //filter out unrealistic readings (e.g., negative or overly large distances)
  if (dist < 0 || dist > 300) {
    dist = 404;  //error code XD
  }
  return dist;
}

