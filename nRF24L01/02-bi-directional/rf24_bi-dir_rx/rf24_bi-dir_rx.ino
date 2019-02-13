/*
 * Modified from code at: https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int button = 4;
int led = 5;

RF24 radio(8, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
    // power levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(2);  // number between 0-124

  Serial.begin(9600);
  Serial.println("starting main loop...");
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int dataIn = 0;
      radio.read(&dataIn, sizeof(dataIn));
//      Serial.println(dataIn);
      analogWrite(led, dataIn);
    }
    
    delay(5);
    // going into Transmit mode
    radio.stopListening();
    // send the digital input pin value 
    buttonState = digitalRead(button);
    radio.write(&buttonState, sizeof(buttonState));
  }
}
