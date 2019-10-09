//include <SoftwareSerial.h>
//SoftwareSerial mySerial(1, 2); // RX, TX

boolean serialcomm=false;

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
int avg3;
int sampleSize=4;



void setup() {
  pinMode(0, OUTPUT); // neuron out
  pinMode(2,INPUT); // this is A1
  pinMode(3,INPUT);
  pinMode(4,INPUT);

  if (serialcomm){
     pinMode(1, OUTPUT);
     pinMode(2, OUTPUT);
  }

  // initialize avarage value

  avg1=analogRead(A2);
  avg2=analogRead(A3);
  avg3=analogRead(A1);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

// hardcode the weights and bias
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

// here are input from the knob
  val = analogRead(A2);
  avg1 = (avg1*(sampleSize-1)+val)/sampleSize;
  val = map(avg1, 0, 1023, 0, 100);
  n_input1 = val / 100.0;
  val = analogRead(A3);
  avg2 = (avg2*(sampleSize-1)+val)/sampleSize;
  val = map(avg2, 0, 1023, 0, 100);
  n_input2 = val / 100.0;
  
  int back = analogRead(A1);
  avg3 = (avg3*(sampleSize-1)+back)/sampleSize;
  back = map(avg3, 500, 700, 0, 100);
  back = constrain(back,0,100);
  if (back >0){
    backpropagation(back);
  }
  


  // calculate the prediction starting with the weight and bias
  float z = n_input1 * w1 + n_input2 * w2 + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  int output = int (200 * prediction);
  output = constrain(output, 0, 200);
  analogWrite(0, output+55);
  

  mySerial.print(n_input1);
  mySerial.print(" : ");
  mySerial.print(n_input2);
  mySerial.print(" : ");
  mySerial.print(prediction);
  mySerial.println();
  delay(50);



}

void backpropagation(int back){
  //back propagation for hidden layer1
    //here is the difference for hidde layer, the derivative of cost is calculated from previous layer
     float multiplier = 0.01;
   
    float dcost_dpred = back * multiplier;

    //bring derivative through sigmoid (prediction is sigmoid)
    //dpred_dz = sigmoid(z) * (1-sigmoid(z))
    float dpred_dz = prediction * (1-prediction);


    w1 -= learningRate * dcost_dpred * dpred_dz * n_input1;
    w2 -= learningRate * dcost_dpred * dpred_dz * n_input2;
    b -= learningRate * dcost_dpred * dpred_dz;

  delay(10);
}

float Sigmoid(float x) {
  float sig = 1 / (1 + exp(-1 * x));
  return sig;
}

