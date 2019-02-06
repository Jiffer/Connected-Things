/*
   IRremote: modified from IRrecvDemo - demonstrates receiving IR codes with IRrecv
   uses the decoded button presses to raise and lower the brightness of an LED
   An IR detector/demodulator must be connected to the input RECV_PIN.
  
*/

#include <IRremote.h>

// IR receiver connected to this pin
int RECV_PIN = 11;
// global to keep track of brightness
int brightness = 0;
// IRrecv object
IRrecv irrecv(RECV_PIN);
// decode_results object
decode_results results;

// PWM output pin
int ledPin = 9;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == 0x1FE58A7) //if the button press equals the hex value 0x.......
    {
      //do something useful here
      Serial.println("got on");
      Serial.println(brightness);
      analogWrite(ledPin, brightness+=5); // TODO: constrain the output to valid range 0:255
    } 
    else if (results.value == 0x1FEA05F) {
      Serial.println("got off");
      analogWrite(ledPin, brightness-=5);
    }


    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
