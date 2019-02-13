/*
 * Modified version of code at: https://howtomechatronics.com/tutorials/arduino/how-to-build-an-arduino-wireless-network-with-multiple-nrf24l01-modules/
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
        == Node 01 (Child of Master node 00) ==
*/
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Servo.h>

RF24 radio(8, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format

// led output
const int led = 5;

// initialization:
void setup() {
  SPI.begin();
  radio.begin();
  // set channel and this node's address
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(led, OUTPUT);
}
void loop() {
  // keep things moving
  network.update();
  
  //===== Receiving =====//
  // check for incoming data
  while ( network.available() ) {    
    RF24NetworkHeader header;
    unsigned long incomingData;
    
    // read data and header
    network.read(header, &incomingData, sizeof(incomingData)); 

    // check where the data came from
    if (header.from_node == 02) {    // If data comes from Node 02
      digitalWrite(led, incomingData);
    }
  }
}
