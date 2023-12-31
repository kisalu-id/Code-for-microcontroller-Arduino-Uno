int led9 = 9;
int brightness = 0;
int fade = 1;

void setup() {
  pinMode(led9, OUTPUT);
}

void loop() {
  //this pin is this bright:
  analogWrite(led9, brightness);
  
  //increase the brighness, I'm in a loop already
  brightness = brightness + fade;

  //when the brightness is at max, reverse
  if (brightness<=0 || brightness >= (256-fade)) {
    fade = -fade;
  }
  
  delay(16); //60 FPS
}
