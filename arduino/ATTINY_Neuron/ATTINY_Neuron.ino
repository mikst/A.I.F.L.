#include <SoftwareSerial.h>

float n_input1;
float n_input2;

float w1;
float w2;
float b;

float prediction;

int nodeNumber = 3;

int val;
int avg1;
int avg2;
int sampleSize=4;

SoftwareSerial mySerial(1, 2); // RX, TX

void setup() {
  pinMode(0, OUTPUT); // nuron out
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
   pinMode(3,INPUT);
  pinMode(4,INPUT);

  // initialize avarage value
  avg1=analogRead(A2);
  avg2=analogRead(A3);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  switch (nodeNumber) {
    case 1:
      w1 = 5.75;
      w2 = 1.03;
      b = -2.21;
      break;

    case 2:
      w1 = -16.24;
      w2 = -1.82;
      b = 6.6;
      break;

    case 3:
      w1 = 7.55;
      w2 = -17.15;
      b = 3.75;
      break;
  }
}

void loop() {

if (nodeNumber ==3){
  int val1 = analogRead(A2); 
  avg1 = (avg1*(sampleSize-1)+val1)/sampleSize;
  val1=avg1;
  val= map(val1, 485, 708, 0, 100);
  val=constrain(val,0,100);
  n_input1=val/100.0;
  int val2 = analogRead(A3); 
  avg2 = (avg2*(sampleSize-1)+val2)/sampleSize;
  val2=avg2;
  val= map(val2, 510, 728, 0, 100);
  val=constrain(val,0,100);
  n_input2=val/100.0;

  mySerial.print(val1);
  mySerial.print(" : ");
  mySerial.print(val2);
  mySerial.print(" : ");
}

else{
  val = analogRead(A2);
  val = map(val, 0, 1023, 0, 100);
  n_input1 = val / 100.0;
  val = analogRead(A3);
  val = map(val, 0, 1023, 0, 100);
  n_input2 = val / 100.0;
}

  // calculate the prediction starting with the weight and bias
  float z = n_input1 * w1 + n_input2 * w2 + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  if (nodeNumber ==3){
  int output = int (255 * prediction);
  output = constrain(output, 0, 255);
  analogWrite(0, output);
  }
  else{
    int output = int (200 * prediction);
  output = constrain(output, 0, 200);
  analogWrite(0, output+55);
  }

  mySerial.print(n_input1);
  mySerial.print(" : ");
  mySerial.print(n_input2);
  mySerial.print(" : ");
  mySerial.print(prediction);
  mySerial.println();
  delay(50);



}



float Sigmoid(float x) {
  float sig = 1 / (1 + exp(-1 * x));
  return sig;
}

