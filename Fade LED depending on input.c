const int led = 9;
int brightness = 0;
int fade = 1;

const int SW_pin = 8;
const int X_pin = 0;
const int Y_pin = 1;

int a = 5; //"switch"


void setup() {
  pinMode(led, OUTPUT);
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
   
  if (digitalRead(SW_pin) == 0) {
    delay(10);
    a = a*(-1); //switch states
  }
    
  if (a<0) { //don't read
    int brightness = 5;
  }

  if (a>0) { //read input from joystick and change the value of brightness
      //this pin is this bright:
  analogWrite(led, brightness);
  
  //increase the brighness, I'm in a loop already
  brightness = brightness + fade;

  //when the brightness is at max, reverse
  if (brightness<=0 || brightness >= (256-fade)) {
    fade = -fade;
  }
  
  //delay(1); //16=60 FPS
    delay((analogRead(Y_pin)/70)+1);
    
  }
}
