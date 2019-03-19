//
// wifiUDP_Tx_solution
//
// Jiffer Hariman
// Connected Things 2019
//
// UDP transmit and receive example.
//
// constructs comma delimited string message
// using both a digital and analog input
//
// The static IP address of this device needs to be unique (relative to others on the network)
// The remoteIP address list includes other devices that the UDP messages will be sent to.

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// WiFi variables
const char* ssid = "things"; // ssid
const char* password = "connected";// password
boolean wifiConnected = false;

// my IP
IPAddress ip(10, 0, 0, 100);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

#define nListeners 2
#define ledPin 16
#define buttonPin 5

int buttonState;
int lastButtonState;

int beat = 0;

// send to:
IPAddress remoteList[nListeners] =
{
  IPAddress(10, 0, 0, 101),
  IPAddress(10, 0, 0, 102),

};

// UDP variables
unsigned int localPort = 8000;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

char  ReplyBuffer[] = "howdy";       // a string to send back

// strings 

String str_analogIn = "0000";
String str_digitalIn = "0";
String str_out;

void setup() {
  // Initialise Serial connection
  Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  // only proceed if wifi connection successful
  if (wifiConnected) {
    udpConnected = connectUDP();
    if (udpConnected) {
      // initialise pins
      pinMode(ledPin, OUTPUT);
      pinMode(buttonPin, INPUT_PULLUP);
    }
  }
}

void loop() {

  // check if the WiFi and UDP connections were successful
  if (wifiConnected) {
    if (udpConnected) {

      Serial.print("send number:");
      Serial.println(beat);

      // each message can be up to 8192 bytes!
      byte message[2];
      message[0] = 0;
      message[1] = beat++;
      beat %= 16;



      for (int i = 0; i < nListeners; i++) {
//        UDP.beginPacket(remoteList[i], localPort);
//        UDP.write(message, sizeof(message));
//        int success = UDP.endPacket();
      }
      buttonState = digitalRead(buttonPin);

      if (buttonState == LOW && buttonState != lastButtonState) {
        // when button is pressed, send a message to the first IP address onlye:
        Serial.println("ow");
//        UDP.beginPacket(remoteList[0], localPort);
//        UDP.write(ReplyBuffer);
//        int success = UDP.endPacket();
      }

      int analogIn = analogRead(A0);  // Get analog value
      int digitalIn = digitalRead(buttonPin);  // Get digital value
      str_analogIn;

      // Convert analog read integer to 4 character string:
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
      str_out = str_analogIn + "," + str_digitalIn;

      // Compose output character
      const char *msg = str_out.c_str();

      UDP.beginPacket(remoteList[0], localPort);
      UDP.write(msg);
      int success = UDP.endPacket();



      // save it to compare next time
      lastButtonState = buttonState;
      delay(500); // pause a moment
    }
  }
}

// connect to UDP – returns true if successful or false if not
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
// connect to wifi – returns true if successful or false if not
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
