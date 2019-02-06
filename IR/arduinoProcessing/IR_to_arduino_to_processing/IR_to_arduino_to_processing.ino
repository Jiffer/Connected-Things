//////////////////////////////////////////////////
// Jiffer Harriman
// ATLAS Institute
// University of Colorado
//
// Processing to Arduino
//-----------------------------------
// Processing sends an integer to serial port when mouse button is down
// In Arduino, this sets the PWM rate for pin 9 (fade amount for an LED)
//
// Arduino to Processing
//-----------------------------------
// Arduino sends integer value of analog input A0 to serial port.
// Processing expects an integer from serial port which maps to the size of
// a circle being drawn where the mouse is in Processing window
//////////////////////////////////////////////////

#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

int ledPin = 9;

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  // LED output 
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);

    if (results.value == 0x1FE58A7) //if the button press equals the hex value 0xC284
    {
      Serial.println(1);
      digitalWrite(ledPin, HIGH);
    } else if (results.value == 0x1FEA05F) {
      Serial.println(0);
      digitalWrite(ledPin, LOW);
    }


    irrecv.resume(); // Receive the next value
  }
  delay(100);

 
  // check for serial data
  if (Serial.available() > 0) {
    int serialIn = Serial.read();

    analogWrite(ledPin, serialIn);
  }
}
