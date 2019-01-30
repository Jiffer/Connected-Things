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


// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

// vars to hold output strings
String str_analogVal;
String str_digitalVal;
String str_out;

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
  uint8_t buf[9];

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet and if it is expected size
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("len: " );
    Serial.println(buflen);


    // Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

    String str_out = String((char*)buf);

    if(str_out.substring(0,4) == "msg1"){
      Serial.println("got msg1");
    }

    if(str_out.substring(0,4) == "msg2"){
      Serial.println("got msg2");
    }
    
    if(str_out.substring(0,3) == "msg"){
      Serial.print("got a sensor msg: ");
      Serial.println(str_out.substring(4, buflen));

      for(int i = 3; i < str_out.length(); i++){
      if(str_out.substring(i, i+1) == ","){
        str_analogVal = str_out.substring(3, i); // starting 3 characters in, after the message flag
        str_digitalVal = str_out.substring(i+1);
        break;
      }
    }
   // Print values to Serial Monitor
      Serial.print("analog: ");
      Serial.print(str_analogVal.toInt());
      Serial.print("  - digital: ");
      Serial.println(str_digitalVal.toInt());
    }

    
  }

}
