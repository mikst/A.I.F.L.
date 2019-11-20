#include <SoftwareSerial.h>
#include "Packetizer.h"

SoftwareSerial mySerial(2, 1); // RX, TX

// the packetizer
Packetizer slicer;

// bufferlength of packetizer
unsigned int bufferLength;

// result, use for error handling
byte result;

int num;



int incomingByte = 0;


void setup() {
pinMode(1, OUTPUT);
    pinMode(2, INPUT); 

  // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
  
  mySerial.println("Hello, world?");

    // setup packetizer  
  slicer.init(128);
  // set end condition with byte-array
  uint8_t b[] = {13, 10};
  result = slicer.setEndCondition(b, sizeof(b)); 
  // set callbacks  
  slicer.onPacket(myOnPacket); 

}

void loop() {

  
if (mySerial.available()){
  incomingByte = mySerial.read();
  if (incomingByte>-1){
  slicer.appendData((uint8_t)incomingByte);
  }
}
    
  delay(10);

}


//----------------------------------------
// callback for messages
//----------------------------------------
void myOnPacket(byte* _buffer, unsigned int _bufferSize)
{
  
  if (_bufferSize < 1) {
    return;
  }


  char* str = (char*)malloc(_bufferSize);
  if (str == 0) {
    return;
  }

  
  //[9, 77, 22, 34]
  memset(str, 0, _bufferSize);
  //[0, 0, 0, 0]
  memcpy(str, _buffer, _bufferSize-1);
  //[49, 51, 51, 0]

  //check if is a number
  boolean isNumber = true;

  for (int i=0; i<_bufferSize-1; i++) {
    if (str[i] > 57) {
      isNumber = false;
      break;
    } 
    
  }

  if (isNumber) {
    // convert to integer
    num = atoi(str);
    saySomething(num);
    
  } else {
    // string
  }
    
  
  free(str);
}

void saySomething(int say){   
    //pinMode(2, OUTPUT);
    delay(100);
    mySerial.println("---");
    mySerial.println(say);
    
   // pinMode(2, INPUT);
    delay(100);
  
}


