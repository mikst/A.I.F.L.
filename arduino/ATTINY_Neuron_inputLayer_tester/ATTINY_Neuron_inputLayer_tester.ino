
#include "sensorPins.h"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

sensorPins sensor1(A3);
sensorPins sensor2(A2);

// the setup routine runs once when you press reset:
void setup() {
  pinMode(0, OUTPUT); // sensor reading out1
  pinMode(1, OUTPUT); // sensor reading out2
//  pinMode(5, OUTPUT); // sensor reading out1
//  pinMode(6, OUTPUT); // sensor reading out2
//  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

// the loop routine runs over and over again forever:
void loop() {
 sensor1.readPin();
 sensor2.readPin();

 mySerial.print(sensor1.sensorVal);
 mySerial.print(" : ");
 mySerial.print(sensor2.sensorVal);
 mySerial.println();



//analogWrite(1,sensor1.brightness);
//analogWrite(0,sensor2.brightness);

//analogWrite(5,sensor1.brightness);
//analogWrite(6,sensor2.brightness);

  delay(10);        // delay in between reads for stability
}
