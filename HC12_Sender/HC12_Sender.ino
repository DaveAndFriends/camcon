/*  HC12 Send/Receive Example Program 1
    By Mark J. Hughes 
    for AllAboutCircuits.com
    
    Connect HC12 "RXD" pin to Arduino Digital Pin 4
    Connect HC12 "TXD" pin to Arduino Digital Pin 5
    Connect HC12 "Set" pin to Arduino Digital Pin 6
   
    Do not power over USB.  Per datasheet, 
    power HC12 with a supply of at least 100 mA with 
    a 22 uF - 1000 uF reservoir capacitor.
    Upload code to two Arduinos connected to two computers.
    
    Transceivers must be at least several meters apart to work.
   
 */

#include <PacketSerial.h>
#include <SoftwareSerial.h>

uint8_t packet[] = {255,10};
int count = 0;
const byte HC12RxdPin = 2;                  // Recieve Pin on HC12
const byte HC12TxdPin = 3;                  // Transmit Pin on HC12

SoftwareSerial HC12(HC12TxdPin,HC12RxdPin); // Create Software Serial Port
PacketSerial myPacketSerial;

void setup() {
  Serial.begin(9600);                       // Open serial port to computer
  HC12.begin(9600);
  myPacketSerial.setStream(&HC12);
}

void loop() {
  myPacketSerial.send(packet, sizeof(packet));
  Serial.println("Sent " + String(count++));
  delay(1000);
}
