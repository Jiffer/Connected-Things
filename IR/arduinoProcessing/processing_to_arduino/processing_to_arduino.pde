//////////////////////////////////////////////////
// Jiffer Harriman
// ATLAS Institute
// University of Colorado
//
// Processing to Arduino
//-----------------------------------
// Processing sends an integer to serial port when mouse button is down
// In Arduino, this sets the PWM rate for pin 9 (fade amount for an LED)
//
// Arduino to Processing
//-----------------------------------
// Arduino sends integer value of analog input A0 to serial port.
// Processing expects an integer from serial port which maps to the size of 
// a circle being drawn where the mouse is in Processing window
//////////////////////////////////////////////////

// include serial communications library
import processing.serial.*;

//////// global variables ////////
int gCircleSize = 30;

// create instance of Serial object
Serial usbPort;

float xPos, yPos;
float speed = 0;

void setup() {
  // the window
  size(900, 600);
  xPos = width / 4;
  yPos = height /2;

  // list available serial ports

  println(usbPort.list()[5]);
  // connect to port /dev/tty.usbmodem*
  usbPort = new Serial (this, Serial.list( ) [5], 9600); // changed to 4 

  // collect data until you hit a new line character
  usbPort.bufferUntil ('\n');
}

void draw() {
  background(0);
  // bunch of rectangles with a gradient
  for (int i = 0; i < width/10; i++) {
    strokeWeight(10);
    stroke(200, 200, 0, map(i, 0, width/10, 0, 255));
    line(i*10, 0, i*10, height);
  }
  strokeWeight(1);
  stroke(0);

  // draw a circle unless the mouse is pressed
  // if the mouse is down then send the value to the Arduino
  if (!mousePressed) {
    ellipse(xPos, yPos, gCircleSize, gCircleSize/2);
  } else {
    // when mouse button is down 
    // send a value over serial port
    usbPort.write((int)map(xPos, 0, width, 0, 255));
  }

  xPos = xPos + speed;
  speed *= 0.99;
  
  if (xPos > width){
    xPos = 0;
  }
  else if(xPos < 0){
    xPos = width;
  }
}

// serialEvent handler
// this is called automatically by processing when there is serial data to read
void serialEvent(Serial usbPort) {

  // variable to store the input
  String usbString = usbPort.readStringUntil('\n');
  // save data into usbString variable, removing the whitespace
  usbString = trim(usbString);

  // display data to processing window
  //println(usbString);

  println("input: " + int(usbString));

  fill(int(usbString)*255);

  if (int(usbString) == 1) {
    print("setting speed: ");
    speed = speed + 5;
    println(speed);
  } else if (int(usbString) == 0) {
    print("setting speed: ");
    speed = speed - 5;
    println(speed);
  }
}
