/*
   IRremote: modified from IRrecvDemo - demonstrates receiving IR codes with IRrecv
   and decodes specific messages
   An IR detector/demodulator must be connected to the input RECV_PIN.
*/

#include <IRremote.h>

// the receiver should be connected to this pin
int RECV_PIN = 11;

// delcare and initialize IRrecv object
IRrecv irrecv(RECV_PIN);
// decode_results object
decode_results results;

int ledPin = 9;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  //
  // output to toggle on/off with receieved and decoded messages
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    // print the value received and decoded
    Serial.println(results.value, HEX);

    //if the button press equals the hex value 0x....
    if (results.value == 0x1FE58A7)
    {
      //do something useful here
      Serial.println("got button 1");
      Serial.println(brightness);
      digitalWrite(ledPin, HIGH);
    } else if (results.value == 0x1FEA05F) {
      Serial.println("got button 2");
      digitalWrite(ledPin, LOW);
    }


    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
