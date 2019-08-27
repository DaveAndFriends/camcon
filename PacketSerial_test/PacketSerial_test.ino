//
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:  MIT
//

#include <SoftwareSerial.h>
#include <PacketSerial.h>


// By default, PacketSerial automatically wraps the built-in `Serial` object.
// While it is still possible to use the Serial object directly, it is
// recommended that the user let the PacketSerial object manage all serial
// communication. Thus the user should not call Serial.write(), Serial.print(),
// etc. Additionally the user should not use the serialEvent() framework.
//
// By default, PacketSerial uses COBS encoding and has a 256 byte receive
// buffer. This can be adjusted by the user by replacing `PacketSerial` with
// a variation of the `PacketSerial_<COBS, 0, BufferSize>` template found in
// PacketSerial.h.
PacketSerial HC12;
SoftwareSerial hc12ss(9, 3);
// p/t,dir,data
uint8_t packet[] = {'n','a','n','o'};
//uint8_t packet[] = {'u','n','o'};

void setup()
{
  hc12ss.begin(9600);
  HC12.setStream(&hc12ss);
  HC12.setPacketHandler(&onPacketReceived);
  // We begin communication with our PacketSerial object by setting the
  // communication speed in bits / second (baud).
  
  Serial.begin(9600);
  Serial.write("Nano intialized");
  //Serial.write("Uno intialized");
  // If we want to receive packets, we must specify a packet handler function.
  // The packet handler is a custom function with a signature like the
  // onPacketReceived function below.
  HC12.setPacketHandler(&onPacketReceived);
}


void loop()
{
  // Do your program-specific loop() work here as usual.

  // The PacketSerial::update() method attempts to read in any incoming serial
  // data and emits received and decoded packets via the packet handler
  // function specified by the user in the void setup() function.
  //
  // The PacketSerial::update() method should be called once per loop(). Failure
  // to call the PacketSerial::update() frequently enough may result in buffer
  // serial overflows.
  
  HC12.update();
  //HC12.send(packet,sizeof(packet));
  delay(1000);
}

// This is our handler callback function.
// When an encoded packet is received and decoded, it will be delivered here.
// The `buffer` is a pointer to the decoded byte array. `size` is the number of
// bytes in the `buffer`.
void onPacketReceived(const uint8_t* buffer, size_t size)
{
  // Send the reversed buffer back to the sender. The send() method will encode
  // the whole buffer as as single packet, set packet markers, etc.
  // The `tempBuffer` is a pointer to the `tempBuffer` array and `size` is the
  // number of bytes to send in the `tempBuffer`.
    printPacket(buffer, size);
}

void printPacket(const uint8_t* packet, size_t size){
 for(int i=0;i<size;i++){
  Serial.print(packet[i]);
  if(i==size-1){
    Serial.println();
  }
  else{Serial.print(",");}
 }
 
}


