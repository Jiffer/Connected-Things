/**
 * modified oscP5parsing by andreas schlegel
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

int buttonVal = 1;
int analogVal = 100;

void setup() {
  size(1000, 1000);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 9999);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1", 9999);
}

void draw() {
  background(0);
  if(buttonVal == 0){
    fill(100);
    
  }
  else if(buttonVal ==1){
    fill(255);
    
  }
  ellipse(width/2, height/2, analogVal/4, analogVal/4);
}




void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */

  if (theOscMessage.checkAddrPattern("/test")==true) {
    /* check if the typetag is the right one. */
    if (theOscMessage.checkTypetag("ifs")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      int firstValue = theOscMessage.get(0).intValue();  
      float secondValue = theOscMessage.get(1).floatValue();
      String thirdValue = theOscMessage.get(2).stringValue();
      print("### received an osc message /test with typetag ifs.");
      println(" values: "+firstValue+", "+secondValue+", "+thirdValue);
      return;
    }  
    
    // This one works with the Arduino/OSC default 
    if (theOscMessage.checkTypetag("i")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      int firstValue = theOscMessage.get(0).intValue();  

      print("### received an osc message /test with typetag i.");
      println(" values: " + firstValue);
      return;
    }
  } 

  if (theOscMessage.checkAddrPattern("/inputs/d0")==true) {
    /* check if the typetag is the right one. */
    if (theOscMessage.checkTypetag("i")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      int firstValue = theOscMessage.get(0).intValue();  

      print("### received an osc message /inputs/d0 with typetag i.");
      println(" values: "+firstValue);
      buttonVal = firstValue;
      return;
    }
  } 
  if (theOscMessage.checkAddrPattern("/inputs/a6")==true) {
    /* check if the typetag is the right one. */
    if (theOscMessage.checkTypetag("i")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      int firstValue = theOscMessage.get(0).intValue();  

      print("### received an osc message /inputs/a6 with typetag i.");
      println(" values: "+firstValue);
      analogVal = firstValue;
      return;
    }
  } 
  println("### received an osc message. with address pattern "+theOscMessage.addrPattern());
}
