//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(1, 2); // RX, TX

#include "sensorPin.h"

SensorPins sensor0(A2, 0);
SensorPins sensor1(A3, 1);

void setup() {
  pinMode(0, OUTPUT); // nurone out1
  pinMode(1, OUTPUT); // nurone out2



  // set the data rate for the SoftwareSerial port
//  mySerial.begin(9600);
//  mySerial.println("Hello, world?");

}

void loop() {

sensor0.readPins();
sensor1.readPins();

// output the value from sensor0
analogWrite(0, sensor0.LEDval);
// output the value from sensor0
analogWrite(1, sensor1.LEDval);
  
 

  
//  mySerial.print ("sensor0: ");
//  mySerial.print(sensor0.sensorVal);
//  mySerial.print(" LED0: ");
//  mySerial.print(sensor0.LEDval);
//  mySerial.println();
  
  delay(10);



}


