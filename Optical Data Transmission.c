/*
Titel: Optische Datenübertragung mit Arduino  
  Beschreibung: Dieses Programm misst die Temperatur mit einem TMP36-Sensor,  
  wandelt die Spannung in Celsius um und konvertiert die Temperatur in eine  
  Binärzahl. Diese Binärdaten werden dann über eine Laserdiode gesendet.  
  Ein zweiter Arduino empfängt die Daten mit einem Fotodetektor und rekonstruiert  
  die Temperatur.  

  Ablauf:  
  1. Temperatur mit TMP36-Sensor messen  
  2. Analogwert in Spannung (mV) umrechnen  
  3. Spannung in Temperatur (°C) umwandeln  
  4. Temperaturwert in Binärformat konvertieren  
  5. Binärdaten über Laserdiode senden  
  6. Empfänger-Arduino empfängt und dekodiert die Datesn  

  Verwendete Hardware:  
  - Arduino Mega 2560 (Sender & Empfänger)  
  - TMP36 Temperatursensor  
  - Laserdiode  
  - Lichtwellenleiter (LWL)  
  - Fotodetektor  
  - USB-Kabel 
  Lizenz: MIT-Lizenz
*/

#include <math.h>

//avoiding magical numbers
#define PAUSE_BETWEEN_BITS 500
#define HIGH_SIGNAL 255
#define LOW_SIGNAL 128

int sensorPin = A0;
int laserPin = 9;

void setup() {
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //read temperature sensor
  int rawValue = analogRead(sensorPin);

  // float tempInVolt = rawValue * 5.0; //or * 3.3, for 3.3 V
  // tempInVolt /= 1024.0;

  //integer math is faster than floating-point operations
  //int voltage_mV = (rawValue * 5000L) / 1024;

  //2^10 = 1024, so using a right shift by 10 (>> 10) is equivalent to dividing by 1024
  //L makes 5000L a long integer (32-bit) to prevent integer overflow
  int voltage_mV = (rawValue * 5000L) >> 10;


  //print voltage in millivolts
  Serial.print("Voltage = ");
  Serial.print(voltage_mV);
  Serial.print(" mV;\t");

  //count temperature
  //if only you knew that AVR can't divide...
  int temperatureC = (voltage_mV - 500) / 10; 
  //round up to the nearest int
  int temperatureRounded = (int)round(temperatureC);
  
  //print temperature
  Serial.print("temperatureRounded = ");
  Serial.print(temperatureRounded);
  Serial.println(" °C");

  //convert to binary
  String binaryString = translateToBinary(temperatureRounded);
  Serial.print("Temperature in binary = ");
  Serial.print(binaryString);
  Serial.println();

  //send binary via laser
  sendBinary(binaryString);
  //turn off the laser for an extended period after transmission to create a clear separation between bit sequences
  delay(PAUSE_BETWEEN_BITS * 2);
}

String translateToBinary(int num) {
  if (num == 0) {
    Serial.println("0");
    return "0";
  }

  String binaryString = "";
  while (num > 0) {
    binaryString = String(num % 2) + binaryString;
    //if only you knew that AVR can't divide...
    //same as num /= 2, but faster on AVR microcontrollers
    num >>= 1;
  }
  return binaryString;
}

void sendBinary(String binaryString) {
  int signal_strength;
  //binaryString = "10101";
  for (int i = 0; i < binaryString.length(); i++) {
    //ternary conditional operator (my favourite shortcut UwU)
    signal_strength = binaryString[i] == '1' ? HIGH_SIGNAL : LOW_SIGNAL;
    //turn on the laser
    analogWrite(laserPin, signal_strength);
    delay(PAUSE_BETWEEN_BITS);

    //turn off the laser
    analogWrite(laserPin, 0);
    delay(PAUSE_BETWEEN_BITS);
  }
  analogWrite(laserPin, 0);
}
