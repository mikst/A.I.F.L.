#include <SoftwareSerial.h>
#include "Packetizer.h"

#define PACKETIZER_SIZE 32

SoftwareSerial mySerial(1, 1); // RX, TX

// the packetizer
Packetizer slicer;


int num;
int incomingByte = 0;

boolean readMode = true;
boolean said = false;


byte mySensor = 97;
byte nextSensor = 98;


void setup() {

  pinMode(1, INPUT); // first set it as RX reading pin
  pinMode(0, OUTPUT); // indicator LED
  pinMode(2, OUTPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(2400);

  slicer.setStartCondition("start");

  // setup packetizer
  slicer.init(PACKETIZER_SIZE);
  // set end condition with byte-array, return CR/NL
  uint8_t b[] = {13, 10};
  slicer.setEndCondition(b, sizeof(b));
  // set callbacks
  slicer.onPacket(myOnPacket);

  digitalWrite(0, HIGH);
  delay(1000);
  digitalWrite(0, LOW);
  delay(1000);

}

void loop() {
  if (readMode) {
    serialEvent();
  }
  delay(1);
}

void checkSerial() {
  if (mySerial.available()) {
    incomingByte = mySerial.read();
    if (incomingByte > -1) {
      slicer.appendData((uint8_t)incomingByte);
    }
  }
}

void serialEvent() {
  while (mySerial.available()) {
    // get the new byte:
    int inVal = mySerial.read();

    if (inVal > -1) {
      // append data to slicer
      slicer.appendData((uint8_t)inVal);
    }
  }

}


//----------------------------------------
// callback for messages
//----------------------------------------


void myOnPacket(byte* _buffer, unsigned int _bufferSize)
{
 // saySomething('A', (uint16_t)_buffer);  
 // saySomething('B', _bufferSize);
  for (int i = 0; i < _bufferSize; i++) {
 //   saySomething('y', _buffer[i]);    
  }
  
  // the first byte is the sensor number index
  byte sensorNum = _buffer[0];
  said = false;

  char* str = (char*)malloc(_bufferSize);
  if (str == 0) {
 //   saySomething(99, 999);
    return;
  }


  // fill the str array which is 1 longer than buffer size with 0
  memset(str, 0, _bufferSize);
  // copy the buffer to str array. this way the last of the array remains 0, which is a marker for the end of the string
  memcpy(str, _buffer + 1, _bufferSize - 1);

  for (int i = 0; i < _bufferSize; i++) {
//    saySomething('y', str[i]);    
  }

  //check if is a number
  boolean isNumber = true;

  for (int i = 0; i < _bufferSize - 1; i++) {
    if (str[i] > 57 || str[i] < 44) {
      isNumber = false;
      break;
    }
  }

  if (isNumber) {
    if (sensorNum == mySensor) {
      // convert to integer
      num = atoi(str);
      //mySerial.print("val: ");
      //mySerial.println(num);
      if (!said) {
        said = true;
        saySomething(nextSensor, num + 10);
      }
    }
  } else {
    //saySomething(100, 1000);
  }
  free(str);

  slicer.reset();
}

void saySomething(char who, int val) {
  mySerial.stopListening();
  digitalWrite(0, HIGH);
  readMode = false;
  pinMode(1, OUTPUT);
  delay(10);
  mySerial.print((int)44);
  mySerial.print((int)55);
  mySerial.print((int)66);
  mySerial.print("start");
  mySerial.write(who);
  mySerial.print(val);
  mySerial.println();
  pinMode(1, INPUT);
  delay(10);
  digitalWrite(0, LOW);
  readMode = true;

  mySerial.listen();
}


