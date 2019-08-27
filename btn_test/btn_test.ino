// Define our three input button pins
#define  LEFT_PIN  8
#define  LEFT_JOG_PIN 9
#define  STOP_PIN  10
#define  RIGHT_PIN 11
#define  RIGHT_JOG_PIN 12
#define  TEST_BTN 13

//Define Limit Switchs
#define LIMIT_LEFT 6  // Pin 6 connected to Limit switch out
#define LIMIT_RIGHT 7  // Pin 7 connected to Limit switch out

// Define our analog pot input pin
#define  SPEED_PIN A0

void setup() {

  pinMode(TEST_BTN, INPUT_PULLD);
  Serial.begin(9600);
  Serial.println("Initialized...");
}


void loop() {
  if(digitalRead(TEST_BTN)==HIGH){
    Serial.println("Pin " + String(TEST_BTN) + " is HIGH");
  }
  else if(digitalRead(TEST_BTN)==LOW){
    Serial.println("Pin " + String(TEST_BTN) + " is LOW");
  }
  delay(500);
}
