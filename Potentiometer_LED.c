const int LED_PIN = 3;             //LED, pwm
const int DIMMER_SENSOR = A0;
const int TEMP_SENSOR = A1;

int currentBrightness = 0;
int lastPotValue = 0;
int dimmerValue = 0;
const int POT_CHANGE_THRESHOLD = 15;
const unsigned long INACTIVITY_TIME = 3000;

unsigned long lastChangeTime = 0;
bool dimmerActive = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(DIMMER_SENSOR, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (dimmerIsBeingMessedWith()) {
    adjustLightToDimmer(dimmerValue);
    lastChangeTime = millis();
    dimmerActive = true;
  }


  else if (dimmerActive && (millis() - lastChangeTime > INACTIVITY_TIME)) {
    dimmerActive = false;
  }

  if (!dimmerActive && (millis() - lastChangeTime > INACTIVITY_TIME)) {
    adjustLight(255);
    delay(500);
    adjustLight(0);
    delay(500);
  }
}


bool dimmerIsBeingMessedWith() {
  int rawPotValue = analogRead(DIMMER_SENSOR);
  dimmerValue = rawPotValue >> 2; //same as "/4"; rawPotValue is in a range 0-1023 and we need to make it 0-255
  if (abs(dimmerValue - lastPotValue) > POT_CHANGE_THRESHOLD) {  //absolute value

    Serial.print("Dimmer changed: ");
    Serial.println(dimmerValue);
    Serial.println("+++dimmerIsBeingMessedWith()"); 
    return true;
  }

  Serial.println("---NOT dimmerIsBeingMessedWith()"); 
  return false;
}

void adjustLightToDimmer(int dimmerValue) { 
  Serial.println("adjustLightToDimmer()"); 
  Serial.print("dimmerValue :"); 
  Serial.println(dimmerValue); 
  if (dimmerValue <= 15) {
    analogWrite(LED_PIN, 0);
  }

  else if (dimmerValue != lastPotValue) { 
    int step = (dimmerValue > lastPotValue) ? 1 : -1;
    for (int i = lastPotValue; i != dimmerValue; i += step) {
      analogWrite(LED_PIN, i);
      delay(3);
    }
    analogWrite(LED_PIN, dimmerValue); 
  }
  lastPotValue = dimmerValue;
}

void adjustLight(int lightValue) { //1 LED
  //Serial.print("adjustLight()\n"); 
  Serial.print("lightValue :"); 
  Serial.println(lightValue); 
  //measure light
  int existingLightRaw = 200;
  //Serial.print("existingLightRaw: ");
  //Serial.println(existingLightRaw);
  int existingLight = existingLightRaw >> 2;
  //Serial.print("existingLight: ");
  //Serial.println(existingLight);


  if (lightValue > existingLight) {

    for (int i = existingLight; i <= lightValue; i++) {
      analogWrite(LED_PIN, i);
      delay(5);
    }
    //gradually turn the light on 
  }
  else if (lightValue < existingLight) {
    //gradually turn the light off
    for (int i = existingLight; i >= lightValue; i--) {
      analogWrite(LED_PIN, i);
      delay(5);
    }
  }
  existingLight = lightValue;
}
