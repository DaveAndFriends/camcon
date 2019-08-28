/**************************************
 * Camera Control Receiver Node
 * 
 * Author: Davis Johnson
 **************************************/

#include <SPI.h>
#include <LoRa.h>
#include <AccelStepper.h>

const char NODE_ID = '1';      //ID of this reciever node (1-8)

const long TILT_LIMIT = 100.0; //Limit for the tilt motor
const long PAN_LIMIT = 512.0;  //Limit for the pan motor
const float MTR_SPEED = 100.0; //Speed for both motors (recommend 25-300)

//Lora pins - do not modify
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DI0     7
#define BAND    868E6
#define PABOOST true 

//Motor pins
#define pin1Pan  2 
#define pin2Pan  3
#define pin3Pan  5
#define pin4Pan  6
#define pin1Tilt 10
#define pin2Tilt 11
#define pin3Tilt 12
#define pin4Tilt 13

#define STEPS_PER_REV 2048

#define DEBUG true

char newFunc;
char curFunc;

AccelStepper panMtr(AccelStepper::FULL4WIRE, pin1Pan, pin2Pan, pin3Pan, pin4Pan);
AccelStepper tiltMtr(AccelStepper::FULL4WIRE, pin1Tilt, pin2Tilt, pin3Tilt, pin4Tilt);

void setup() {
  //Lora Setup
  Serial.begin(9600);
  Serial.println("LoRa Receiver");
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND,PABOOST )) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

   //Motor setup
   panMtr.setMaxSpeed(300.0);
   panMtr.setSpeed(0);
   tiltMtr.setMaxSpeed(300.0);
   tiltMtr.setSpeed(0);
}

void loop() {
  //Check for packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //Packet received
    int count = 0;
    char packet[packetSize];
    if(DEBUG) Serial.print("Received packet '");
    //Parse packet
    while (LoRa.available()) {
      char curChar = (char)LoRa.read();
      packet[count] = curChar;
      count++;
      if(DEBUG) Serial.print(curChar);
    }
    if(DEBUG){
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());
    }
    //Is this packet for me?
    if(packet[0] == NODE_ID){
      //Packet is for me, read function
      if(DEBUG) Serial.println("It's for me!");
      newFunc = packet[2];
    }
  }

  //Should we do something new?
  if(newFunc!=curFunc){
    curFunc=newFunc;
    //Stop
    if(curFunc=='S'){
      stop_all();
    }//Tilt
    else if(curFunc=='U' || curFunc=='D'){
      tilt(curFunc);
    }//Pan
    else if(curFunc=='L' || curFunc=='R'){
      pan(curFunc);
    }
  }

  //Update motors
  panMtr.runSpeedToPosition();
  tiltMtr.runSpeedToPosition();
}

//Stop all motors
void stop_all(){
  if(DEBUG) Serial.println("STOP");
  tiltMtr.stop();
  tiltMtr.setSpeed(0);
  panMtr.stop();
  panMtr.setSpeed(0);
}

void tilt(char dir){
  if(DEBUG){
    Serial.print("Tilt ");
    Serial.print(dir);
    Serial.print(" curPos: ");
    Serial.println(tiltMtr.currentPosition());
  }
  if(dir=='U'){
    if(tiltMtr.currentPosition()<=TILT_LIMIT){
      tiltMtr.moveTo(TILT_LIMIT);
      tiltMtr.setSpeed(MTR_SPEED);
    }  
  }else if(dir=='D'){
    if(tiltMtr.currentPosition()>=-TILT_LIMIT){
      tiltMtr.moveTo(-TILT_LIMIT);
      tiltMtr.setSpeed(-MTR_SPEED);
    }
  }
}

void pan(char dir){
  if(DEBUG){
    Serial.print("Pan ");
    Serial.print(dir);
    Serial.print(" curPos: ");
    Serial.println(panMtr.currentPosition());
  }
  if(dir=='R'){
    if(panMtr.currentPosition()<=PAN_LIMIT){
      panMtr.moveTo(PAN_LIMIT);
      panMtr.setSpeed(MTR_SPEED);
    }  
  }else if(dir=='L'){
    if(panMtr.currentPosition()>-PAN_LIMIT){
      panMtr.moveTo(-PAN_LIMIT);
      panMtr.setSpeed(-MTR_SPEED);
    }
  }
}

