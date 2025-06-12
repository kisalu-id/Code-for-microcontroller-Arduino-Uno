const int LED_PIN = 3             //LED, pwm
const int DIMMER_SENSOR = A0;

int currentBrightness = 0;
int lastPotValue = 0;
int dimmerValue = 0;
const int POT_CHANGE_THRESHOLD = 5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(DIMMER_SENSOR, INPUT);
}



void loop() {
  if (dimmerIsBeingMessedWith()) {
    adjustLight(dimmerValue);
  }
  else {
    adjustLight(255);
    delay(1000);
    adjustLight(0);
    delay(1000);
  }
}



bool dimmerIsBeingMessedWith() {
  int rawPotValue = analogRead(DIMMER_SENSOR);
  dimmerValue = rawPotValue >> 2; //same as "/4"; rawPotValue is in a range 0-1023 and we need to make it 0-255
  if (abs(currentPotValue - lastPotValue) > POT_CHANGE_THRESHOLD) {  //AI, absolute value
    lastPotValue = currentPotValue;
    return true;
  }
  return false;
}



void adjustLight(int lightValue) {
  //measure light
  int existingLightRaw = 30;
  Serial.print("existingLight: ");
  Serial.println(existingLight);
  int existingLight = existingLightRaw >> 2;
  Serial.print("existingLight: ");
  Serial.println(existingLight);

  if (lightValue > existingLight) {
    for (int i = existingLight; i <= lightValue; i++) {
      analogWrite(LED_PIN, i);
      delay(5);
    }
  }
  else if (lightValue < existingLight) {
    for (int i = existingLight; i >= lightValue; i--) {
      analogWrite(LED_PIN, i);
      delay(5);
    }
  }
  existingLight = lightValue;
}
