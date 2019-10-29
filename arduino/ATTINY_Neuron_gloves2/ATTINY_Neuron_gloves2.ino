#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
SoftwareSerial mySerial(1, 2); // RX, TX

#include "LDRPins.h"

float w[3];
float b;

float prediction;
int nodeNumber = 0;

LDRPins input0(A2, 0);
LDRPins input1(A3, 1);

void setup() {

  pinMode(0, OUTPUT); // nuron out
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);

    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
    mySerial.println("Hello, world?");
  


  // hardcode the weights and bias
  switch (nodeNumber) {
    case 0:
      float temp0[] = { -4.40350067942314, -4.383896735373529, -2.927458329253389};
      memcpy(w, temp0, 3);
      b = 6.6878883965306235;
      break;

//    case 1:
//      float temp1[] = {0.9986696201577525, -2.8487908655028096, -3.2368474818654587};
//      memcpy(w, temp1, 3);
//      b = 2.479656344160664;
//      break;
//
//    case 2:
//      float temp2[] = {1.7659984453424213, 0.7013665968417439, 1.627505036710998};
//      memcpy(w, temp2, 3);
//      b = -1.6151380396000723;
//      break;
//
//    case 3:
//      float temp3[] = {0.20014090094175427, -0.7845909085496982, 8.866852602517492};
//      memcpy(w, temp3, 3);
//      b = -3.832975861451879;
//      break;
//
//    case 10:
//      float temp10[] = { -6.351268363583637, -5.019168100865285, 2.6708229405310977};
//      memcpy(w, temp10, 3);
//      b = 2.3833490703670055;
//      break;
//
//    case 11:
//      float temp11[] = {7.137888877036356, -1.60562409210227, -8.94400882382718};
//      memcpy(w, temp11, 3);
//      b = -0.08503653295192201;
//      break;
//
//    case 12:
//      float temp12[] = {1.334438458028954, 1.1920323252378646, 0.031120590720109958};
//      memcpy(w, temp12, 3);
//      b = 1.576218072856936;
//      break;
//
//    case 20:
//      float temp20[] = {7.0452854054523275, -5.067183054085642, -0.6335098755465082};
//      memcpy(w, temp20, 3);
//      b = -2.6735074053744663;
//      break;
//
//    case 21:
//      float temp21[] = { -3.499125859410934, 7.994066208431146, -2.175756979723036};
//      memcpy(w, temp21, 3);
//      b = -1.411818428546999;
//      break;
//
//    case 22:
//      float temp22[] = { -6.749357272074924, -7.017209940072923, 1.7994120236403375};
//      memcpy(w, temp22, 3);
//      b = 1.436308038287372;
//      break;
  }
}

void loop() {

  // read pins
  input0.readPin();
  input1.readPin();

  // calculate the prediction starting with the weight and bias
  float z = input0.receivedData * w[input0.id] +input1.receivedData * w[input1.id]+ b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  int output = int (200 * prediction);
  output = constrain(output, 0, 200);
  analogWrite(0, output + 55);

  // if in the case of debugging with serial

      mySerial.print(" sensor0: ");
      mySerial.print(input0.sensorVal);
      mySerial.print(" data0: ");
      mySerial.print(input0.receivedData);
      mySerial.print(" sensor1: ");
      mySerial.print(input1.sensorVal);
      mySerial.print(" data1: ");
      mySerial.print(input1.receivedData);
      mySerial.print(" pred: ");
      mySerial.print(prediction);

  mySerial.println();

  delay(50);

}


float Sigmoid(float x) {
  float sig = 1.0 / (1.0 + exp(-1.0 * x));
  return sig;
}

