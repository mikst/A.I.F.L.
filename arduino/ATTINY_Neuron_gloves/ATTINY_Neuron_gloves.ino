#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
SoftwareSerial mySerial(1, 2); // RX, TX

#include "LDRPins.h"


byte lookupTable1[] = {55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 58, 58, 58, 58, 58, 59, 59, 60, 61, 61, 61, 62, 62, 62, 63, 63, 64, 64, 65, 65, 65, 65, 66, 68, 69, 69, 70, 70, 71, 71, 71, 72, 72, 72, 72, 72, 72, 73, 73, 73, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 77, 77, 77, 78, 78, 78, 78, 80, 80, 81, 81, 82, 82, 83, 83, 83, 83, 84, 85, 85, 86, 86, 86, 86, 87, 87, 88, 89, 89, 90, 90, 90, 91, 91, 91, 91, 92, 92, 93};
byte lookupTable2[] = {94, 94, 94, 95, 96, 96, 96, 97, 97, 98, 99, 99, 99, 100, 100, 101, 101, 102, 102, 103, 104, 104, 105, 105, 106, 106, 107, 107, 108, 108, 109, 109, 110, 110, 111, 111, 112, 112, 113, 113, 114, 115, 115, 115, 116, 116, 116, 117, 117, 118, 119, 122, 123, 124, 125, 127, 127, 128, 129, 130, 131, 131, 132, 133, 134, 134, 135, 135, 135, 136, 137, 138, 138, 139, 139, 139, 140, 140, 140, 141, 141, 142, 142, 143, 143, 143, 143, 144, 144, 144, 145, 146, 146, 147, 149, 151, 153, 153, 154, 154};
byte lookupTable3[] = {155, 156, 157, 158, 159, 160, 161, 161, 161, 162, 162, 162, 162, 163, 163, 163, 163, 163, 164, 164, 165, 165, 166, 167, 168, 169, 170, 171, 172, 172, 173, 173, 174, 174, 175, 175, 176, 176, 176, 177, 178, 179, 180, 181, 181, 182, 182, 183, 183, 184, 184, 184, 185, 186, 186, 187, 188, 189, 190, 191, 193, 195, 197, 199, 200, 201, 202, 203, 204, 205, 205, 206, 207, 207, 208, 208, 209, 210, 211, 211, 211, 212, 213, 213, 214, 215, 215, 216, 217, 217, 217, 218, 219, 219, 220, 220, 220, 221, 221, 222};
byte lookupTable4[] = {223, 223, 223, 224, 225, 226, 226, 227, 228, 230, 232, 233, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 246, 248, 250, 252, 255};
float w[3];
float b;

float prediction;
int nodeNumber = 0;

LDRPins input0(A2, 0);
//LDRPins input1(A3, 1);

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
  int v = input0.sensorVal;
  v = v-31;
  v = constrain(v, 0, 199);
  int q = v/100;
  int r = v%100;
  int tv;
  switch(q){
    case 0:
    r = constrain(r,0,99);
    tv =lookupTable1[r];
    break;
    
    case 1:
    r = constrain(r,0,99);
    tv =lookupTable2[r];
    break;
    
//    case 2:
//    r = constrain(r,0,99);
//    tv =lookupTable3[r];
//    break;
//    
//    case 3:
//    r = constrain(r,0,27);
//    tv =lookupTable4[r];
//    break;   
  }
  
  input0.convert(tv);
  
  //input1.readPin();

  // calculate the prediction starting with the weight and bias
  float z = input0.receivedData * w[input0.id] + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  int output = int (200 * prediction);
  output = constrain(output, 0, 200);
  analogWrite(0, output + 55);

  // if in the case of debugging with serial
 mySerial.print(v);
mySerial.print(" table: ");
      mySerial.print(tv);
      mySerial.print(" sensor: ");
      mySerial.print(input0.sensorVal);
      mySerial.print(" data: ");
      mySerial.print(input0.receivedData);
      mySerial.print(" pred: ");
      mySerial.print(prediction);

  mySerial.println();

  delay(50);

}


float Sigmoid(float x) {
  float sig = 1.0 / (1.0 + exp(-1.0 * x));
  return sig;
}

