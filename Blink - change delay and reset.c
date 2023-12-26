/*A programm that makes a LED blink with dynamically changed delay in a loop with hardcoded reset at 10th round of adding a value*/

int count = 100;
int count2 = 900;

//the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

  //the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(count);                      // wait for X time
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(count2);                     // wait for X2 time
  count = count + 100;
  count2 = count2 + 300;

  if (count >= 1000) {
    count = 100;
    count2 = 900;
    }
}
