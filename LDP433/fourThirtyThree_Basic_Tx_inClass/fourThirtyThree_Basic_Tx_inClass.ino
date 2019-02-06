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


// sensor pins
int aPin = A0;
int dPin = 2;
 
// data
int analogIn;
int digitalIn;

 String str_analogIn = "0000";
 String str_digitalIn = "0";
 String str_out;


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

    analogIn = analogRead(aPin);
    digitalIn = digitalRead(dPin);

    if(analogIn < 1000 && analogRead > 99){
      str_analogIn = "0" + String(analogIn);
    }
    else if(analogIn < 100 && analogIn > 9){
      str_analogIn = "00" + String(analogIn);
    }
    else if(analogIn < 10){
      str_analogIn = "000" + String(analogIn);
    }
    else{
      str_analogIn = String(analogIn);
    }
    

    
    str_digitalIn = String(digitalIn);

    str_out = str_analogIn + "," + str_digitalIn;

    char *msg = str_out.c_str();
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    
}
