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

int analogIn = A0;
int digitalIn = 2;

void setup()
{
    // Initialize ASK Object
    rf_driver.init();
}

void loop()
{
  // a string is just a bunch of characters
    char *msg1 = "msg1";
    rf_driver.send((uint8_t *)msg1, strlen(msg1));
    rf_driver.waitPacketSent();
    delay(1000);
    
    // message 2
    char *msg2 = "msg2";
    rf_driver.send((uint8_t *)msg2, strlen(msg2));
    rf_driver.waitPacketSent();
    delay(1000);
}
