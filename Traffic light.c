int led_red = 9;
int led_yellow = 10;
int led_green = 11;

void setup() {
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
}

void loop() {
  digitalWrite(led_red, LOW);
  digitalWrite(led_yellow, HIGH);
  digitalWrite(led_green, LOW);
  delay(2000);
  
  digitalWrite(led_red, HIGH); 
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, LOW);
  delay(4500);
  
  digitalWrite(led_red, LOW);
  digitalWrite(led_yellow, HIGH);
  digitalWrite(led_green, LOW);
  delay(2000);
  
  digitalWrite(led_red, LOW); 
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, HIGH);
  delay(4500);
}
