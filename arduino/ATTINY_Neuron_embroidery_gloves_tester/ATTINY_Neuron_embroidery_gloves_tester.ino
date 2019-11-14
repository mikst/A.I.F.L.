#include <avr/pgmspace.h>
#include "LDRPins.h"

#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

float w0;
float w1;
float w2;
float b;

float prediction;
int nodeNumber = 10;

LDRPins input0(A1);
LDRPins input1(A3);
LDRPins input2(A2);

int inputRangeMin[] = {135, 60, 60, 162, 95, 60, 0, 55, 60, 85, 84, 71, 74, 99, 50, 134, 70, 52, 120, 82, 83, 48, 92, 142, 77, 56, 64, 70, 91, 140};
int inputRangeMax[] = {370, 232, 205, 430, 290, 225, 40, 232, 230, 270, 272, 214, 246, 310, 190, 360, 230, 193, 338, 250, 284, 173, 283, 397, 269, 203, 222, 214, 267, 343};


void setup() {

  pinMode(0, OUTPUT); // nuron out
  pinMode(1, OUTPUT); // nuron out
  pinMode(2, INPUT); // A1
  pinMode(3, INPUT); // A3
  pinMode(4, INPUT); // A2

   // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");


  // hardcode the weights and bias
  switch (nodeNumber) {
    case 2:
      b =  -1.8792414060072198 ;
      w0 = -2.0754978069879293 ;
      w1 = 1.3096939325382086 ;
      w2 = 4.347601933322612 ;
      input0.setRange(inputRangeMin[2], inputRangeMax[2]);
      input1.setRange(inputRangeMin[4], inputRangeMax[4]);
      input2.setRange(inputRangeMin[8], inputRangeMax[8]);
      break;

    case 3:
      b =  2.727312584655556 ;
      w0 = 0.1860380853131188 ;
      w1 = -0.0862311025241102 ;
      w2 = 0.5551945715579224 ;
      input0.setRange(inputRangeMin[0], inputRangeMax[0]);
      input1.setRange(inputRangeMin[6], inputRangeMax[6]);
      input2.setRange(inputRangeMin[10], inputRangeMax[10]);
      break;

    case 4:
      b =  -2.873967586277664 ;
      w0 = 3.2020657803588 ;
      w1 = -6.217961326862947 ;
      w2 = 8.564185989916634 ;
      input0.setRange(inputRangeMin[1], inputRangeMax[1]);
      input1.setRange(inputRangeMin[3], inputRangeMax[3]);
      input2.setRange(inputRangeMin[9], inputRangeMax[9]);
      break;

    case 5:
      b =  1.8780955194310627 ;
      w0 = 0.25019401731437985 ;
      w1 = 0.7610181405432069 ;
      w2 = 2.9936354478846905 ;
      input0.setRange(inputRangeMin[5], inputRangeMax[5]);
      input1.setRange(inputRangeMin[7], inputRangeMax[7]);
      input2.setRange(inputRangeMin[11], inputRangeMax[11]);
      break;

    case 6:
      b =  -1.6870088327928725 ;
      w0 = 0.11078556500647131 ;
      w1 = 1.0584515102614314 ;
      w2 = -0.9150115243339328 ;
      input0.setRange(inputRangeMin[12], inputRangeMax[12]);
      input1.setRange(inputRangeMin[19], inputRangeMax[19]);
      input2.setRange(inputRangeMin[18], inputRangeMax[18]);
      break;

    case 7:
      b =  -2.0633540223352624 ;
      w0 = -6.652679809023252 ;
      w1 = -1.7862614251038065 ;
      w2 = 8.11682851100347 ;
      input0.setRange(inputRangeMin[13], inputRangeMax[13]);
      input1.setRange(inputRangeMin[15], inputRangeMax[15]);
      input2.setRange(inputRangeMin[16], inputRangeMax[16]);
      break;

    case 8:
      b =  -1.1799591986783033 ;
      w0 = 8.067118408312504 ;
      w1 = -1.2484503077401763 ;
      w2 = -1.8936983193028156 ;
      input0.setRange(inputRangeMin[17], inputRangeMax[17]);
      input1.setRange(inputRangeMin[14], inputRangeMax[14]);
      input2.setRange(inputRangeMin[20], inputRangeMax[20]);
      break;

    case 9:
      b =  -2.9333683358626086 ;
      w0 = -6.507915676515794 ;
      w1 = -0.19388663066549297 ;
      w2 = 6.2546201666964985 ;
      input0.setRange(inputRangeMin[25], inputRangeMax[25]);
      input1.setRange(inputRangeMin[21], inputRangeMax[21]);
      input2.setRange(inputRangeMin[29], inputRangeMax[29]);
      break;

    case 10:
      b =  2.7321369683945673 ;
      w0 = 1.88054070748761 ;
      w1 = -6.026032297710191 ;
      w2 = -6.80558487617812 ;
      input0.setRange(inputRangeMin[22], inputRangeMax[22]);
      input1.setRange(inputRangeMin[28], inputRangeMax[28]);
      input2.setRange(inputRangeMin[24], inputRangeMax[24]);
      break;

    case 11:
      b =  -4.871700863890995 ;
      w0 = -1.5773842769912723 ;
      w1 = 7.983596589693863 ;
      w2 = 1.461803655300419 ;
      input0.setRange(inputRangeMin[23], inputRangeMax[23]);
      input1.setRange(inputRangeMin[26], inputRangeMax[26]);
      input2.setRange(inputRangeMin[27], inputRangeMax[27]);
      break;
  }
}

void loop() {

  // read pins
  input0.readPin();
  input1.readPin();
  input2.readPin();

  // calculate the prediction starting with the weight and bias
  float z = input0.receivedData * w0 + input1.receivedData * w1 + input2.receivedData * w2 + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);
  

  int output;

if (nodeNumber<9){
  output = int (200 * prediction);
  output = constrain(output, 0, 200);
  //analogWrite(0, output + 55); 
}
else{
  output = int (255 * prediction);
  output = constrain(output, 0, 255);
  //analogWrite(0, output);
}


mySerial.print("sensor0: ");
mySerial.print(input0.receivedData);
mySerial.print(" sensor1: ");
mySerial.print(input1.receivedData);
mySerial.print(" sensor2: ");
mySerial.print(input2.receivedData);
mySerial.print(" w0: ");
mySerial.print(w0);
mySerial.print(" w1: ");
mySerial.print(w1);
mySerial.print(" w2: ");
mySerial.print(w2);
mySerial.print(" prediction: ");
mySerial.print(prediction);
mySerial.print(" light: ");
mySerial.print(output);
mySerial.println();
  
  delay(10);

}


float Sigmoid(float x) {
  float sig = 1.0 / (1.0 + exp(-1.0 * x));
  return sig;
}

