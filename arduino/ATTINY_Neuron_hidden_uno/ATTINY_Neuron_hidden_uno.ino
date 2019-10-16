

float n_input1;
float n_input2;

float w1;
float w2;
float b;

float prediction;

int nodeNumber = 1;

int val;
int avg1;
int avg2;
int avg3;
int sampleSize = 4;

boolean backPropProcess;

boolean printable=true;



void setup() {
  
  pinMode(5, OUTPUT); // neuron out UNO
  pinMode(2, INPUT); // this is A1
  pinMode(3, INPUT);
  pinMode(4, INPUT);


  // initialize avarage value

  avg1 = analogRead(A2);
  avg2 = analogRead(A3);
  avg3 = analogRead(A1);

// if uno for debug
Serial.begin(9600);
Serial.println("Hello, world?");


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

  
//w1 = random(-10,10)/10.0;
//w2 = random(-10,10)/10.0;
//b = random(-10,10)/10.0;


}

void loop() {

  // forward calculation
  // here are input from the knob
  val = analogRead(A2);
  avg1 = (avg1 * (sampleSize - 1) + val) / sampleSize;
  val = map(avg1, 0, 1023, 0, 100);
  n_input1 = val / 100.0;
  val = analogRead(A3);
  avg2 = (avg2 * (sampleSize - 1) + val) / sampleSize;
  val = map(avg2, 0, 1023, 0, 100);
  n_input2 = val / 100.0;

  // calculate the prediction starting with the weight and bias
  float z = (n_input1 * w1) + (n_input2 * w2) + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  int output = int (200 * prediction);
  output = constrain(output, 0, 200);
  analogWrite(5, output + 55);

  val = analogRead(A1);
  avg3 = (avg3 * (sampleSize - 1) + val) / sampleSize;
  

  if (avg3 > 500 ) {
    if (!backPropProcess) {
      // run the back propagation
      backPropProcess = true;
      backpropagation(val);
    }
  }
  else {
    backPropProcess = false;

// print it only once
    if (printable){
     Serial.print(n_input1);
      Serial.print(" : ");
      Serial.print(n_input2);
      Serial.print(" : ");
      Serial.print(prediction);
      Serial.println();
      printable=false;
    }
  }

  delay(10);

}

void backpropagation(int back) {
  //back propagation for hidden layer1
  float learningRate = 0.2;

  //here is the difference for hidde layer, the derivative of cost is calculated from previous layer
  // back is output neuron's dcost_dpred*dpred_dz*w1 converted into the range -100 to 100
  back = map(avg3, 520, 720, -100, 100);
  back=constrain(back,-100,100);
  float dcost_dpred = back * 0.01;

  //bring derivative through sigmoid (prediction is sigmoid)
  //dpred_dz = sigmoid(z) * (1-sigmoid(z))
  float dpred_dz = prediction * (1 - prediction);


  w1 -= learningRate * dcost_dpred * dpred_dz * n_input1;
  w2 -= learningRate * dcost_dpred * dpred_dz * n_input2;
  b -= learningRate * dcost_dpred * dpred_dz;
  
  Serial.print("back: ");
  Serial.print(back);
  Serial.print(" dcost_dpred: ");
  Serial.print(dcost_dpred);
  Serial.print(" dpred_dz: ");
  Serial.print(dpred_dz);
  Serial.print(" w1: ");
  Serial.print(w1);
  Serial.print(" w2: ");
  Serial.print(w2);
  Serial.print(" b: ");
  Serial.print(b);
  Serial.println();
  printable=true;

  delay(100);
}

float Sigmoid(float x) {
  float sig = 1.0 / (1.0 + exp(-1.0 * x));
  return sig;
}

