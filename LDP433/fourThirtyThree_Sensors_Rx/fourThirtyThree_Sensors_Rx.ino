/*
  433 MHz RF Module Receiver Demonstration 2
  RF-Rcv-Demo-2.ino
  Demonstrates 433 MHz RF Receiver Module with DHT-22 Sensor
  Use with Transmitter Demonstration 2
 
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/
 
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Define output strings
 
String str_analogVal;
String str_digitalVal;
String str_out;
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);

    Serial.println("starting main loop");
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[6]; // may be 5, 4 or 3 
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      Serial.print("length: ");
      Serial.println(buflen);
      // Message received with valid checksum
      // Get values from string
      
      // Convert received data into string
      str_out = String((char*)buf);
      
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
      str_analogVal = str_out.substring(0, i);
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
