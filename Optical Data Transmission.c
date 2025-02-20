//TMP36
int sensorPin = A0;
    
void setup() {
    Serial.begin(9600);
}

void loop() {
	int tempInput = analogRead(sensorPin);
  float tempInVolt = tempInput * 5.0; //or * 3.3
  tempInVolt /= 1024.0;

  Serial.print("Voltage = ");
  Serial.print(tempInVolt); //print temperature
  Serial.print(" mV;\t"); 
	
  float temperatureC = (voltage - 0.5) * 100;
  Serial.print("Temperature = ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  int tempBinary = translateToBinary(temperatureC);
	
  delay(2000);
}

int translateToBinary(num) {
  int binaryNum[32]; //assuming 32 bit integer.
  int i=0;

  if (num == 0) {
    Serial.println("0");
    return 0;
  }

   while (num > 0) {
      binaryNum[i++] = num % 2;
      num /= 2;
   }

  //print in reverse

  //clear from unnecesary 0's


  return answer;
}
