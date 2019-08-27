#include <Keypad.h>
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
#include <PacketSerial.h>

#define NODE_ID 1 //ID of this node

//Lora comm vars
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DI0     7
#define BAND    868E6  // 915E6
#define PABOOST true 

//Keypad pin mappings and vars
#define X1      10
#define X2      11
#define X3      12
#define X4      13
#define Y1      2
#define Y2      3
#define Y3      5
#define Y4      6
#define MAX_NODES 8


//Set to false for production
#define DEBUG   true

//Keypad config
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'U','N','N','N'},
  {'D','L','R','S'}
};
byte rowPins[ROWS] = { Y1, Y2, Y3, Y4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { X1, X2, X3, X4}; //connect to the column pinouts of the keypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

//Holds the current node 
int curNode = 0;

void setup()
{
  //Serial init
  Serial.begin(9600);
  Serial.println("Serial initialzed");

  //Keypad init
  myKeypad.setHoldTime(100);
  myKeypad.setDebounceTime(10);

  //Lora Init
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND,PABOOST)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  readKey();

  //delay(100);
}

void sendPacket(char function){
  LoRa.beginPacket();
  LoRa.print(curNode);
  LoRa.print(',');
  LoRa.print(function);
  if(DEBUG){
      Serial.print("Sending packet: ");
      Serial.print(curNode);
      Serial.print(',');
      Serial.println(function);
  }
  LoRa.endPacket();
}

void readKey(){
  char curKey = myKeypad.getKey();
  
  if(curKey){
    Serial.print("Current key: ");
    Serial.println(curKey);

    if(curKey>'0' && curKey<='8'){
      curNode=(curKey-48);
      if(DEBUG){
        Serial.print("Current node changed to ");
        Serial.println(curNode);
      }
    }else{
      sendPacket(curKey);
    }
  }
}


