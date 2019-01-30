/*
  433 MHz RF Module Transmitter Demonstration 2
  RF-Xmit-Demo-2.ino
  Demonstrates 433 MHz RF Transmitter Module with DHT-22 Sensor
  Use with Receiver Demonstration 2

   adapted from
  https://dronebotworkshop.com/433mhz-rf-modules-arduino/
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>

// Define Constants


// Define Variables

int analogIn;    // stores input values
int digitalIn;

int aPin = A0;
int dPin = 2;

// Define output strings

String str_analogIn = "0000";
String str_digitalIn = "0";
String str_out;

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup() {

  // Initialize ASK Object
  rf_driver.init();

  // initialize digital pin to use an internal pullup
  pinMode(dPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.print("started serial at 9600...");

}

void loop()
{

  delay(500);

  analogIn = analogRead(aPin);  // Get analog value
  digitalIn = digitalRead(dPin);  // Get digital value

  // Convert analog read integer to string
  if (analogIn < 1000 && analogIn > 99) {
    str_analogIn = "0" + String(analogIn);
  }
  else if (analogIn < 100 && analogIn > 9) {
    str_analogIn = "00" + String(analogIn);
  }
  else if (analogIn < 10) {
    str_analogIn = "000" + String(analogIn);
  }
  else { //uses 4 digits
    str_analogIn = String(analogIn);
  }

  str_digitalIn = String(digitalIn);
  
  // Combine analog and digital sensors into one string (payload)
  str_out = "msg" + str_analogIn + "," + str_digitalIn;

  // Compose output character
  static char *msg = str_out.c_str();
  Serial.print("sending message: ");
  Serial.println(msg);
  Serial.print("message length: ");
  Serial.println(strlen(msg));

  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();

}
