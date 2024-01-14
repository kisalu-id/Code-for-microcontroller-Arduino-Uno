/*Y up - blink faster, Y down blink slower. Press the pin - turn the LED on/off. */
const int led = 9;
int brightness = 0;
int fade = 1;

const int SW_pin = 8; // digital pin8 connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

int state = 1; //switch
int statePrevious = 0;


void setup() {
  pinMode(led, OUTPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600); //serial connection (speed)
}



void loop() {
  while (state) { //switch on

    analogWrite(led, brightness);
  
    //increase the brighness, I'm in a loop already
    brightness = brightness + fade;

    //when the brightness is at max, reverse
    if (brightness<=0 || brightness >= (256-fade)) {
      fade = -fade;
    }
  
    //delay(17); =60 FPS
    delay((analogRead(Y_pin)/500)+1);
    //flip the switch
    if (digitalRead(SW_pin) == 0 && statePrevious == 0) {
      if (state) {
        statePrevious = state; //=1
        state = 0;
      }
    }
  }
  
  if (state==0) {
    Serial.print("StatePrev is: ");
    Serial.print(statePrevious);
    Serial.print(" | State is: ");
    Serial.print(state);
    Serial.print(" | Pin is:");
    Serial.println(digitalRead(SW_pin));
  
    digitalWrite(led, LOW);

    //flip the switch
    if (digitalRead(SW_pin) == 0 && statePrevious == 1) {
      if (!state){
        statePrevious = state;
        state = 1;
      }
    }
  }
  Serial.print("StatePrev is: ");
  Serial.print(statePrevious);
  Serial.print(" | State is: ");
  Serial.print(state);
  Serial.print(" | Pin is:");
  Serial.println(digitalRead(SW_pin));
  
}
