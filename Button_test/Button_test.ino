#define POT_PIN A0
#define LEFT_SW_PIN 2


void setup() {
  pinMode(LEFT_SW_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(LEFT_SW_PIN) == HIGH){
    Serial.println("HIGH");
  }
  delay(500);
}
