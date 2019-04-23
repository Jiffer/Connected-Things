/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for receiving open sound control (OSC) messages on the ESP8266/ESP32
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.

  This example code is in the public domain.

  --------------------------------------------------------------------------------------------- */
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NEO_PIN            25
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);


char ssid[] = "anotherThing";          // your network SSID (name)
char password[] = "connected";                    // your network password

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(10, 0, 1, 10);     // remote IP (not needed for receive)
IPAddress ip(10, 0, 1, 9); // my IP address (requested)
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 255, 0);
const unsigned int outPort = 8888;          // remote port (not needed for receive)
const unsigned int localPort = 9999;        // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;
unsigned int ledState = LOW;              // LOW means led is *on*

#ifndef BUILTIN_LED
#ifdef LED_BUILTIN
#define BUILTIN_LED LED_BUILTIN
#else
#define BUILTIN_LED 13
#endif
#endif

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, ledState);    // turn *on* led

  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  int i = 0;
  int state = true;
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }


  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif
  // initialize the neopixel library
  pixels.begin();
}

void led(OSCMessage &msg) {
  ledState = msg.getInt(0);
  if (ledState == 1) {
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));

    }
    pixels.show();
  }else{
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  }
  pixels.show();
  }
  
  // also blink the on board LED
  digitalWrite(2, ledState); // GPIO 2 is built in LED on DOIT ESP32 board
  Serial.print("/led: ");
  Serial.println(ledState);
}


void test(OSCMessage &msg) {
  char * blah;
  // here blah can hold up to 100 characters
  blah = new char[100];
  Serial.print("/test: ");
  msg.getString(0, blah);
  Serial.println(blah);
}

void gotAnalog(OSCMessage &msg) {
  int val = msg.getInt(0);
  Serial.print("/analog: ");
  Serial.println(val);
}

void loop() {
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    //    Serial.print("stuff");
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError())
    {
      // all possible OSC messages and handler functions
      msg.dispatch("/led", led);
      msg.dispatch("/test", test);
      msg.dispatch("/analog", gotAnalog);

    }
    else
    {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
