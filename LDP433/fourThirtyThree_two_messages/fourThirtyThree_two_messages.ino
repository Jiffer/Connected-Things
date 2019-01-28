/*
  433 MHz RF Module Transmitter Demonstration
  Demonstrates 433 MHz RF Transmitter Module
  Use with fourThirtythree_Basic_Rx

adapted from:
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
}

void loop()
{
  // a string is just a bunch of characters
    char *msg = "Hello World";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);

    char *msg1 = "msg1";
    rf_driver.send((uint8_t *)msg2, strlen(msg1));
    rf_driver.waitPacketSent();
    delay(500);

}
