/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

  --------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "things";          // your network SSID (name)
char password[] = "connected";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10, 0, 0, 101);     // remote IP of your computer
// use to request a static IP
IPAddress ip(10, 0, 0, 100); // my IP address (requested)
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)


// global variables
bool ledValue = false;

void setup() {
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

}

void loop() {
  // toggle value to write
  ledValue = !ledValue;

  Serial.print("sending message /led ");
  Serial.println(ledValue);
  OSCMessage msg("/led");
  if(ledValue){
    msg.add(1);  
  }else{
    msg.add(0);
  }
  
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  delay(500);


  // send another
  Serial.print("sending message /test ");
  OSCMessage msg1("/test");
  msg1.add("hello, osc.");
  Udp.beginPacket(outIp, outPort);
  msg1.send(Udp);
  Udp.endPacket();
  msg1.empty();
  delay(500);

  // send another
  Serial.print("sending message /analog ");
  OSCMessage msg2("/analog");
  msg2.add((int)random(255));
  Udp.beginPacket(outIp, outPort);
  msg2.send(Udp);
  Udp.endPacket();
  msg2.empty();
  delay(500);
}
