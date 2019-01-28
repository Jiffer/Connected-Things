/*
  433 MHz RF Module Receiver Demonstration 1
  RF-Rcv-Demo-1.ino
  Demonstrates 433 MHz RF Receiver Module
  Use with Transmitter Demonstration 1

  adapted from
  https://dronebotworkshop.com/433mhz-rf-modules-arduino/
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

String str_out;
int ledPin = 3;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("waiting for received data of size 11 chars...");

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Set buffer to size of expected message 
  // or max expected size
  uint8_t buf[11];

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet and if it is expected size
  if (rf_driver.recv(buf, &buflen))
  {
        Serial.print("received message length: " );
        Serial.println(buflen);

// simpler but less robust way is to simply check the length of the message:
//    if (buflen == 11) {
//      digitalWrite(2, LOW);
//      // Message received with valid checksum
//      Serial.print("Message Received: ");
//      Serial.println((char*)buf);
//    }
//    if (buflen == 4) {
//      digitalWrite(2, HIGH);
//      // Message received with valid checksum
//      Serial.print("Message Received: ");
//      Serial.println((char*)buf);
//    }
    // convert char* to a String
    str_out = String((char*)buf);
    // check for specific characters

    if(str_out.substring(0,4) == "msg1") {
      Serial.println("msg1");
      digitalWrite(ledPin, HIGH);
      
    }
    if(str_out.substring(0,4) == "msg2") {
      Serial.println("got msg2");
      digitalWrite(ledPin, LOW);
      
    }
  }

}
