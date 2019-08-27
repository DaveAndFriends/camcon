#include <SPI.h>
#include <LoRa.h>

// uncomment the section corresponding to your board
// BSFrance 2017 contact@bsrance.fr 

  //LoR32u4II 868MHz or 915MHz (black board)
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DI0     7
#define BAND    868E6  // 915E6
#define PABOOST true 

#define DEBUG true

const char NODE_ID = '1';

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND,PABOOST )) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } 
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    int count = 0;
    char packet[packetSize];
    if(DEBUG) Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {
      char curChar = (char)LoRa.read();
      packet[count] = curChar;
      if(DEBUG) Serial.print(curChar);
    }
    // print RSSI of packet
    if(DEBUG){
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());
    }
    //Is this packet for me?
    if(packet[0] == NODE_ID){
      //packet is for me, what should I do?
      char func = packet[2];
      //tilt
      if(func=='S'){
        stop_all();
      }
      else if(func=='U' || func=='D'){
        tilt(func);
      }//pan
      else if(func=='L' || func=='R'){
        pan(func);
      }
    }
  }
}
