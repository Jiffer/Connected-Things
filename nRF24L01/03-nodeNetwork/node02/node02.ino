/*
 * Modified version of code at: https://howtomechatronics.com/tutorials/arduino/how-to-build-an-arduino-wireless-network-with-multiple-nrf24l01-modules/
 * 
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
        == Node 02 (Child of Master node 00) ==    
*/
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
RF24 radio(8, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 02;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;
const uint16_t master00 = 00;    // Address of the other node in Octal format

const unsigned long interval = 10;  //ms  // How often to send data to the other unit
unsigned long last_sent;            // When did we last send?

// digital inputs
const int button1 = 3;
const int button2 = 4;
// output
const int led = 5;

void setup() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  network.update();
  //===== Sending =====//
  unsigned long now = millis();
  if (now - last_sent >= interval) {   // If it's time to send a data, send it!
    last_sent = now; // capture the current value of millis()
    unsigned long buttonVal1 = digitalRead(button1);
    unsigned long buttonVal2 = digitalRead(button2);
    RF24NetworkHeader header(master00);   // (Address where the data is going)
    bool ok = network.write(header, &buttonVal1, sizeof(buttonVal1)); // Send the data
    RF24NetworkHeader header2(node01);   // (Address where the data is going)
    bool ok2 = network.write(header2, &buttonVal2, sizeof(buttonVal2)); // Send the data
  }

  // add receiving code here
  // to set brightness (analogWrite value) of led output

}
