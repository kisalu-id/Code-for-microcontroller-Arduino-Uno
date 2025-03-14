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
  6. Empfänger-Arduino empfängt und dekodiert die Daten  

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

int sensorPin = A0;
int laserPin = 9;
    
void setup() {
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //read temperature sensor
  int tempInput = analogRead(sensorPin);
  float tempInVolt = tempInput * 5.0; //or * 3.3
  tempInVolt /= 1024.0;

  //print voltage
  Serial.print("Voltage = ");
  Serial.print(tempInVolt);
  Serial.print(" mV;\t"); 

  //print temperature
  float temperatureC = (tempInVolt - 0.5) * 100;
  Serial.print("temperatureRounded = "); 
  Serial.print(temperatureC);
  Serial.println(" °C");

  //round up to int
  int temperatureRounded = ceil(temperatureC);
  int temperatureCtest = 29;

  //convert to binary
  String binaryString = translateToBinary(temperatureRounded);
  Serial.println();
  Serial.print("Temperature in binary = ");
  Serial.print(binaryString);
  Serial.println();

  //send binary via laser
  sendBinary(binaryString);

  //delay(10000);
}

String translateToBinary(int num) {
  if (num == 0) {
    Serial.println("0");
    return "0";
  }

  String binaryString = "";
  while (num > 0) {
    binaryString = String(num % 2) + binaryString;
    num /= 2;
  }
  return binaryString;
}

void sendBinary(String binaryString) {
  for (int i = 0; i < binaryString.length(); i++) {
    //ternary conditional operator (my favourite shortcut UwU)
    analogWrite(laserPin, binaryString[i] == '1' ? 225 : 128);
    delay(500);
    analogWrite(laserPin, 0);
    delay(500);
  }
  //turn it off for 1 second after sending
  analogWrite(laserPin, 0);
  delay(1000);
}
