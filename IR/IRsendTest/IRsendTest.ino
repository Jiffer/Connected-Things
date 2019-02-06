/*
   IRremote: modified version of IRremote example IRsendDemo 
   An IR LED must be connected to Arduino PWM pin 3.
   
*/

// include the library
#include <IRremote.h>

// declare IRsend object
IRsend irsend;

void setup()
{
  // configure a button to send the code
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // sendSony example (apprently it needs to be sent 3 times)
  //	for (int i = 0; i < 3; i++) {
  //		irsend.sendSony(0xa90, 12);
  //		delay(40);
  //	}
  
  // send hex code 0x1FE58A7
  irsend.sendNEC(0x1FE58A7, 32);
  delay(100);

  // send hex code 0x1FEA05F
  irsend.sendNEC(0x1FEA05F, 32);
  delay(900);
}
