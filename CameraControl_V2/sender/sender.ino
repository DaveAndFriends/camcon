/**************************************
 * Camera Control Sender Node
 * 
 * Author: Davis Johnson
 **************************************/

#include <Keypad.h>
#include <SPI.h>
#include <LoRa.h>

//Max number of nodes
#define MAX_NODES 8

//Lora pins - do not modify
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

#define DEBUG   false

//Keypad config
const byte ROWS = 4;
const byte COLS = 4;
//Define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'S','S','S','U'},
  {'L','R','S','D'}
};
byte rowPins[ROWS] = { Y1, Y2, Y3, Y4};
byte colPins[COLS] = { X1, X2, X3, X4};

//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//Holds the current node 
int curNode = 0;

void setup()
{
  //Serial init
  if(DEBUG){
    Serial.begin(9600);
    Serial.println("Serial initialzed");
  }

  //Keypad init
  myKeypad.setHoldTime(100);
  myKeypad.setDebounceTime(10);

  //Lora Init
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND,PABOOST)) {
    if(DEBUG) Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop()
{
  readKey();
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
    if(DEBUG){
      Serial.print("Current key: ");
      Serial.println(curKey);
    }
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


