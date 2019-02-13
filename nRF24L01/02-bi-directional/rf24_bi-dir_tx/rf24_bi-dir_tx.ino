
/*
 * Modified from code at: https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
 * 
  Example 2 - Transmitter Code by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



RF24 radio(8, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

const int led = 5;

void setup() {
  pinMode(led, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
    // power levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(2);  // number between 0-124


}

void loop() {
  delay(5);

  radio.stopListening();
  int potValue = analogRead(A0);
  int angleValue = map(potValue, 0, 1023, 0, 255);
  radio.write(&angleValue, sizeof(angleValue));

  delay(5);
  radio.startListening();
  if (radio.available()) {
    while (radio.available()) {
      boolean buttonState = 0;
      radio.read(&buttonState, sizeof(buttonState));
      if (buttonState == HIGH) {
        digitalWrite(led, HIGH);
      }
      else {
        digitalWrite(led, LOW);
      }
    }
  }
}
