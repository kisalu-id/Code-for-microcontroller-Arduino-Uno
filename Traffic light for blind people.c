/*
  Titel: Blindenampel für Fußgänger mit Taste
  Verwendete Hardware: Funrduino 2560, LEDs, Taste, Wiederstände 200 und 10k Ohm, USB-Kabel, Buzzer
  Autor: kisalu-id
  Datum: 19. Februar 2025
  Lizenz: MIT-Lizenz
*/

//declare LEDs
int led_red = 9;
int led_yellow = 10;
int led_green = 11;
int led_peasant_green = 8;
int led_peasant_red = 7;

//declare button und buzzer
int btn = 6;
int buzzer = 12;

//declare timing
int delayTime = 4000; // = 4 sec

void setup() {
  //set LED pins as output
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_peasant_green, OUTPUT);
  pinMode(led_peasant_red, OUTPUT);
  
  //turn them off
  digitalWrite(led_red, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_peasant_green, LOW);
  digitalWrite(led_peasant_red, LOW);
  
  //button is as input
  pinMode(btn, INPUT);
  //buzzer as output
  pinMode(buzzer, OUTPUT);
  
  //test
  Serial.begin(9600);
}

/*a function that turns on red light each 40 seconds automatically, so other cars can cross the road in fromt of you;
and if a pedestrian will press the button, the red light also turns on
*/
void btnPressed() {
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, HIGH);
  digitalWrite(led_peasant_red, HIGH);
  Serial.println("Yellow for cars!");
  delay(delayTime/2);
  digitalWrite(led_yellow, LOW);
  
  digitalWrite(led_red, HIGH);
  digitalWrite(led_peasant_red, LOW);
  digitalWrite(led_peasant_green, HIGH);
  
  for (int i=0; 10>=i; i++)b{
    tone(12,200); //Erzeuge Ton an Pin 12 mit der Frequenz 1000Hz
    delay(100); //100ms warten
    noTone(12); //Schalte Ton aus
    delay(100); //100ms warten
  }

  Serial.println("Red for cars!");
  delay(delayTime);
  digitalWrite(led_red, LOW);

  digitalWrite(led_yellow, HIGH);
  digitalWrite(led_peasant_red, HIGH);
  digitalWrite(led_peasant_green, LOW);
  Serial.println("Yellow for cars!");
  delay(delayTime/2);
  digitalWrite(led_yellow, LOW);
}

void loop() {
  //start with green light being on for cars
  digitalWrite(led_green, HIGH);
  digitalWrite(led_peasant_red, HIGH);
  Serial.println("Green for cars!"); //endless loop, hehe

  //declare a variable state just for convenience
  int state = digitalRead(btn);

  //if the button is pressed, start the function
  if (state == 1) {
    Serial.println("The button was pressed!");
    delay(delayTime);
    btnPressed();
  }
}
