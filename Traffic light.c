//declare LEDs
int led_red = 9;
int led_yellow = 10;
int led_green = 11;

//declare button
int btn = 5;

//declare timing
int delayTime = 4000; // = 4 sec

void setup() {
  //set LED pins as output
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
  
  //turn them off
  digitalWrite(led_red, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, LOW);
  
  //button is as input
  pinMode(btn, INPUT);
  
  //test
  Serial.begin(9600);

}

/*a function that turns on red light each 40 seconds automatically, so other cars can cross the road in fromt of you;
and if a pedestrian will press the button, the red light also turns on
*/
void btnPress() {

  for (int i=0; i<40; i++) {
    //declare a variable state just for convenience
    int state = digitalRead(btn); 
    
    if (state == 0) {
      Serial.println(i);
      delay(1000); //countdown 1 sec * 40 times, for other cars to cross the road
    }
    
    else if (state == 1) {
      Serial.println("The button was pressed!");
      delay(delayTime);
      return;
    }
  }
}

void loop() {
  //start with green light being on for 40 sec
  digitalWrite(led_green, HIGH);
  Serial.println("Green!");
  btnPress();
  digitalWrite(led_green, LOW);

  //if the button is pressed OR if 40 sec passed by:
  digitalWrite(led_yellow, HIGH);
  Serial.println("Yellow!");
  delay(delayTime/2);
  digitalWrite(led_yellow, LOW);
  
  digitalWrite(led_red, HIGH);
  Serial.println("Red!");
  delay(delayTime);
  digitalWrite(led_red, LOW);
  
  digitalWrite(led_yellow, HIGH);
  Serial.println("Yellow!");
  delay(delayTime/2);
  digitalWrite(led_yellow, LOW);
}

