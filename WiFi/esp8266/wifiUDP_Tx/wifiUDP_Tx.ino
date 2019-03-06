//
// wifiUDP_Tx
//
// Jiffer Hariman
// Connected Things 2019
//
// UDP transmit and receive example.
//
// Sends a counter that increments from 0-16 and starts over
// When digital input GPIO5 (nodeMCU pin labelled D1) it sends a one time string message
//
// The static IP address of this device needs to be unique (relative to others on the network)
// The remoteIP address list includes other devices that the UDP messages will be sent to.

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// WiFi variables
const char* ssid = "things";        // ssid
const char* password = "connected"; // password
boolean wifiConnected = false;

// My IP address:
IPAddress ip(10, 0, 0, 100);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

#define nListeners 2
#define ledPin 16     // built in LED pin on nodeMCU
#define buttonPin 5   // GPIO 5 = nodeMCU D1

// keep track of button state to check if it has changed
int buttonState;
int lastButtonState;

// this number will increment and be sent to the remote IP address list
int beat = 0;

// list of IP addresses to send to:
IPAddress remoteList[nListeners] =
{
  IPAddress(10, 0, 0, 101),
  IPAddress(10, 0, 0, 102),
};

// UDP variables
WiFiUDP UDP;
unsigned int localPort = 8000;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

// char array (string) to send
char  msgBuffer[] = "howdy";   // this could be up to 8192 bytes

// *************************
// Initialization
// *************************
void setup() {
  // Initialise Serial connection
  Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  // only proceed if wifi connection successful
  if (wifiConnected) {
    udpConnected = connectUDP();
    if (udpConnected) {
      // initialize pins
      pinMode(ledPin, OUTPUT);
      pinMode(buttonPin, INPUT_PULLUP);
    }
  }
}

// *************************
// main loop
// *************************
void loop() {

  // check if the WiFi and UDP connections were successful
  if (wifiConnected) {
    if (udpConnected) {

      Serial.print("send number:");
      Serial.println(beat);

      // UDP message 1:

      // Only sending a 2 byte message here
      // to represent up to a 16 bit integer
      byte message[2];
      message[0] = 0;
      message[1] = beat++;
      beat %= 16;           // 2 bytes can hold integer value up to  2^16 = 65,535

      // broadcast this value to all the IP Addresses in the list:
      for (int i = 0; i < nListeners; i++) {
        UDP.beginPacket(remoteList[i], localPort);
        UDP.write(message, sizeof(message));
        int success = UDP.endPacket();
      }
      buttonState = digitalRead(buttonPin);

      // UDP message 2:

      // if the button has changed from HIGH to LOW
      if (buttonState == LOW && buttonState != lastButtonState) {
        // when button is pressed, send a message to the first IP address onlye:
        Serial.println("ow");
        UDP.beginPacket(remoteList[0], localPort);
        UDP.write(msgBuffer);
        int success = UDP.endPacket();
      }

      // save button state to compare next time
      lastButtonState = buttonState;
      delay(500); // pause a moment
    }
  }
}


// *************************
// connect to UDP – returns true if successful or false if not
// *************************
boolean connectUDP() {
  boolean state = false;

  Serial.println("");
  Serial.println("Connecting to UDP");

  if (UDP.begin(localPort) == 1) {
    Serial.println("Connection successful");
    state = true;
  }
  else {
    Serial.println("Connection failed");
  }

  return state;
}


// *************************
// connect to wifi – returns true if successful or false if not
// *************************
boolean connectWifi() {
  boolean state = true;
  int i = 0;
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
    Serial.print("Try ");
    Serial.println(i);
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}

void udpReset() {
  // asm volatile ("  jmp 0");
  if (wifiConnected) {
    udpConnected = connectUDP();
    if (udpConnected) {
      Serial.print(" ...success");
    }
    else {
      Serial.print(" on nose!");

    }
  }
}

//////////////////////////////////////////
