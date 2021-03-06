/**
 * oscP5parsing by andreas schlegel - modified by Jiffer Harriman
 * example shows how to parse incoming osc messages "by hand".
 * it is recommended to take a look at oscP5plug for an
 * alternative and more convenient way to parse messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

int remoteX, remoteY = 0;

void setup() {
  size(400,400);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,9999);
  
  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1" ,8888);
}

void draw() {
  fill(255);
  ellipse(mouseX, mouseY, 10, 10);
  fill(100, 20, 250);
  ellipse(remoteX, remoteY, 10, 10);
}


void mousePressed() {
  /* create a new osc message object */
  OscMessage myMessage = new OscMessage("/mouse");
  
  myMessage.add(mouseX); /* add an int to the osc message */
  myMessage.add(mouseY); /* add a float to the osc message */
  

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation); 
}

void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */
  
  if(theOscMessage.checkAddrPattern("/mouse")==true) {
    /* check if the typetag is the right one. */
    if(theOscMessage.checkTypetag("ii")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
       remoteX = theOscMessage.get(0).intValue();  
       remoteY = theOscMessage.get(1).intValue();
      
      print("### received an osc message /test with typetag ii.");
      println(" values: " + remoteX + ", " + remoteY);
      return;
    }  
  } 
  println("### received an osc message. with address pattern "+theOscMessage.addrPattern());
}
