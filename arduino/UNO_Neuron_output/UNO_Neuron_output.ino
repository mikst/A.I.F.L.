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


int buttonFPin=2;
int buttonTPin=3;
boolean lastbuttonStateT;
boolean lastbuttonStateF;

int predOutPin=9;
int backProp1Pin=5;
int backProp2Pin=6;

float backprop1;
float backprop2;

boolean printable=true;

void setup() {

  // predicted outcome
  pinMode(predOutPin, OUTPUT); // nuron out
  // backpropagation pin
  pinMode(backProp1Pin,OUTPUT);
  pinMode(backProp2Pin,OUTPUT);

  // set the learning trigger/teach button to be input
  pinMode(buttonFPin,INPUT_PULLUP);
  pinMode(buttonTPin,INPUT_PULLUP);

  // initialize avarage value
  avg1=analogRead(A0);
  avg2=analogRead(A1);

  // set the data rate for the SoftwareSerial port
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
  int val1 = analogRead(A0); // output from neuron1
  avg1 = (avg1*(sampleSize-1)+val1)/sampleSize;
  val1=avg1;
  val= map(val1, 485, 800, 0, 100);
  val=constrain(val,0,100);
  n_input1=val/100.0;   // converting to number between 0-1.0
  
  int val2 = analogRead(A1); // output from neuron2
  avg2 = (avg2*(sampleSize-1)+val2)/sampleSize;
  val2=avg2;
  val= map(val2, 510, 800, 0, 100);
  val=constrain(val,0,100);
  n_input2=val/100.0; // converting to number between 0-1.0

  // calculate the prediction starting with the weight and bias
  float z = n_input1 * w1 + n_input2 * w2 + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  int output = int (255 * prediction);
  output = constrain(output, 0, 255);
  analogWrite(predOutPin, output);


// check if the training button is pressed
boolean buttonStateT=digitalRead(buttonTPin);
boolean buttonStateF=digitalRead(buttonFPin);

// training button that indicates the correct answer should be true/1 is pressed
if (buttonStateT == 0 && lastbuttonStateT!=buttonStateT){
  backpropagation(1.0);
}

// training button that indicates the correct answer should be false/0 is pressed
else if (buttonStateF == 0 && lastbuttonStateF!=buttonStateF){
  backpropagation(0.0);
}

else{

  analogWrite(backProp1Pin, 0);
  analogWrite(backProp2Pin, 0);  

  if (printable){
    
  Serial.print(val1);
  Serial.print(" : ");
  Serial.print(val2);
  Serial.print(" : ");
  Serial.print(n_input1);
  Serial.print(" : ");
  Serial.print(n_input2);
  Serial.print(" : ");
  Serial.print(w1);
  Serial.print(" : ");
  Serial.print(w2);
  Serial.print(" : ");
  Serial.print(b);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.print(" prediction: ");
  Serial.print(prediction);
  Serial.print(" : ");
  Serial.print(output);
  Serial.println();
  printable=false;
  }
}


lastbuttonStateT=buttonStateT;
lastbuttonStateF=buttonStateF;

 
  delay(10);

}

void backpropagation(float target){
  // back propagation output layer
  float learningRate=0.2;

    //find the slope of the cost w, r, t each parameter (w1 w2 b)
    //bring derivative through square function
    float dcost_dpred= 2* (prediction - target);

    //bring derivative through sigmoid (prediction is sigmoid)
    //dpred_dz = sigmoid(z) * (1-sigmoid(z))
    float dpred_dz = prediction * (1-prediction);

  // here are the caluclation for the hidden layer neurons
    backprop1=dcost_dpred*dpred_dz*w1;
    backprop2=dcost_dpred*dpred_dz*w2;

    //pertial derivatives using the chain rule and adjust
    w1-= learningRate* (dcost_dpred*dpred_dz*n_input1);
    w2-= learningRate* (dcost_dpred*dpred_dz*n_input2);
    b-= learningRate* (dcost_dpred*dpred_dz*1);

    int propLight1 = int(backprop1 * 100.0);
    propLight1 = constrain(propLight1,-100,100);
    propLight1 = map(propLight1, -100,100,55,255);
    analogWrite(backProp1Pin, propLight1);

    int propLight2 = int (backprop2 * 100.0);
    propLight2 = constrain(propLight2,-100,100);
    propLight2 = map(propLight2, -100,100,55,255);
    analogWrite(backProp2Pin, propLight2);

Serial.print("target: ");
    Serial.print(target);

    Serial.print(" dcost_dpred: ");
    Serial.print(dcost_dpred);
    Serial.print(" dpred_dz: ");
    Serial.print(dpred_dz);
   
    Serial.print(" backprop1: ");
    Serial.print(backprop1);
    Serial.print(" light1: ");
    Serial.print(propLight1);
    Serial.print(" backprop2: ");
    Serial.print(backprop2);
    Serial.print(" light2: ");
    Serial.print(propLight2);
    Serial.println();

    printable=true;
  delay(500);

}



float Sigmoid(float x) {
  float sig = 1.0 / (1.0 + exp(-1.0 * x));
  return sig;
}

