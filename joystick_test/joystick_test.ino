  #define PAD 50
  
  int x = 0;
  int y = 0;
  String xpos = "NEUTRAL";
  String ypos = "NEUTRAL";
  int x_init;
  int y_init;

void setup() {
  x_init = analogRead(A0);
  y_init = analogRead(A1);
  Serial.begin(9600);
  Serial.println("Initialized with x: " + String(x_init) + " y: " +String(y_init));
}

void loop() {
  x = analogRead(A0);
  y = analogRead(A1);

  xpos = get_xpos(x);
  ypos = get_ypos(y);

  Serial.println("x: " + xpos + " " + String(x) + 
                 " y: " + ypos + " " + String(y));
  delay(500);

}

String get_xpos(int reading){
  String result = "";
  if(reading < (x_init+PAD) && reading > (x_init-PAD)){
    result = "NEUTRAL";
  }
  if(reading < (x_init-PAD)){
    result = "LEFT";
  }
  else if(reading > (x_init+PAD)){
    result = "RIGHT";
  }
  return result;
}

String get_ypos(int reading){
  String result = "";
  if(reading < (y_init+PAD) && reading > (y_init-PAD)){
    result = "NEUTRAL";
  }
  if(reading < (y_init-PAD)){
    result = "DOWN";
  }
  else if(reading > (y_init+PAD)){
    result = "UP";
  }
  return result;
}

