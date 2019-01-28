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

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("waiting for received data of size 11 chars...");
}

void loop()
{
  // Set buffer to size of expected message
  uint8_t buf[11];

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet and if it is expected size
  if (rf_driver.recv(buf, &buflen))
  {
    //    Serial.print("len: " );
    //    Serial.println(buflen);


    // Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

  }

}
