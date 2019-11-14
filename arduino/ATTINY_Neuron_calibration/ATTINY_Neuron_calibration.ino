
#include "sensorPins.h"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(1, 2); // RX, TX

sensorPins sensor1(A3);


// the setup routine runs once when you press reset:
void setup() {
  pinMode(0, OUTPUT); // sensor reading out1
  pinMode(1, OUTPUT); // serial
  pinMode(2, OUTPUT); // serial


  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  
}

// the loop routine runs over and over again forever:
void loop() {
 sensor1.readPin();

  mySerial.print(sensor1.sensorVal);
  mySerial.println();

  delay(10);        // delay in between reads for stability
}
