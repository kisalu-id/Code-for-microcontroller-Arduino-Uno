/*
  Titel: Potentiometer 
  Beschreibung: Das Potentiometer steuert die Helligkeit einer LED über den PWM-Ausgang.
  Verwendete Hardware: Arduino Mega 2560, Potentiometer, Breadboard, Jumper-Kabel, USB-Kabel, LED, Wiederstände 200 Ohm
  Datum: 26. Februar 2025
  Lizenz: MIT-Lizenz
*/

//analog pins like A0 are pre-defined as part of the system, so there's no need to declare them
//but for convenience that will be done
int potentiometer = A0;
int red = 5;
int green = 4;
int blue = 3;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  //initialize serial communication at 9600 baud
  //Baud rate - the speed at which data is transmitted or received over a communication channel, such as serial communication.
  //It represents the number of signal changes (or symbols) per second.
  //In the context of Arduino, 9600 baud means that the data is transmitted at a rate of 9600 bits per second (bps)
  Serial.begin(9600);
}

void loop() {
  //read the analog value from the potentiometer (pin A0)
  int sensorValue = analogRead(potentiometer);
  
  //calculate the corresponding voltage (0 - 5V)
  float voltage = sensorValue * (5.0 / 1023.0);
  
  //print the raw value and the voltage to the serial monitor
  Serial.print("sensor value: ");
  Serial.print(sensorValue);
  Serial.print("  voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  //map the potentiometer value to a range of 0 to 255 for PWM control
  int brightness = map(sensorValue, 0, 1023, 0, 255);

  Serial.print(brightness);
  Serial.println(" brightness ");

  //set the brightness for each color channel
  analogWrite(red, brightness);
  analogWrite(green, brightness);
  analogWrite(blue, brightness);

  //wait for 100 milliseconds or 0,1 second
  delay(500);
}
