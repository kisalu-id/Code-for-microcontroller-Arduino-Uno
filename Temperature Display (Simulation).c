/*
  Titel: 4. Temperaturanzeige (Simulation)
  Beschreibung: Alle 5 Sekunden wird eine zufällige Temperatur zwischen 20°C und 30°C generiert und ausgegeben.
  Verwendete Hardware: Funrduino 2560, USB-Kabel.
  Lizenz: MIT-Lizenz
*/
void setup() {
  //start the program
  Serial.begin(9600);
}

void loop() {
  int temp = random(20, 31);  //randon number between 20 und 30
  //print the result
  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.println(" °C");
  //wait 5 seconds
  delay(5000);
}
