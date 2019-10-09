float n_input1;
float n_input2;

float w1;
float w2;
float b;

float prediction;

int val;
int avg1;
int avg2;
int sampleSize=4;

boolean lastButtonStateF;
boolean lastButtonStateT;
int buttonFPin=2;
int buttonTPin=3;

int predOutPin=9;
int backProp1Pin=5;
int backProp2Pin=6;

float backprop1;
float backprop2;

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


      // assign the value that is from the simulation
//      w1 = 7.55;
//      w2 = -17.15;
//      b = 3.75;

w1 = random(-10,10)/10.0;
w2 = random(-10,10)/10.0;
b = random(-10,10)/10.0;

     
}

void loop() {

// forward calculation
  int val1 = analogRead(A0); // output from neuron1
  avg1 = (avg1*(sampleSize-1)+val1)/sampleSize;
  val1=avg1;
  val= map(val1, 485, 708, 0, 100);
  val=constrain(val,0,100);
  n_input1=val/100.0;   // converting to number between 0-1.0
  
  int val2 = analogRead(A1); // output from neuron2
  avg2 = (avg2*(sampleSize-1)+val2)/sampleSize;
  val2=avg2;
  val= map(val2, 510, 728, 0, 100);
  val=constrain(val,0,100);
  n_input2=val/100.0; // converting to number between 0-1.0

//  Serial.print(val1);
//  Serial.print(" : ");
//  Serial.print(val2);
//  Serial.print(" : ");

  // calculate the prediction starting with the weight and bias
  float z = n_input1 * w1 + n_input2 * w2 + b;
  // make a prediction using sigmoid
  prediction = Sigmoid(z);

  int output = int (255 * prediction);
  output = constrain(output, 0, 255);
  analogWrite(predOutPin, output);
 
//  Serial.print(n_input1);
//  Serial.print(" : ");
//  Serial.print(n_input2);
//  Serial.print(" : ");
//  Serial.print(w1);
//  Serial.print(" : ");
//  Serial.print(w2);
//  Serial.print(" : ");
//  Serial.print(b);
//  Serial.print(" : ");
//  Serial.print(prediction);
//  Serial.print(" : ");
//  Serial.print(output);
//  Serial.println();

// check if the training button is pressed
boolean buttonStateT=digitalRead(buttonTPin);
boolean buttonStateF=digitalRead(buttonFPin);

// training button that indicates the correct answer should be true/1 is pressed
if (buttonStateT == 0){
  backpropagation(1.0);
}
lastButtonStateT==buttonStateT;

// training button that indicates the correct answer should be false/0 is pressed
if (buttonStateF == 0 ){
  backpropagation(0.0);
}
lastButtonStateF==buttonStateF;

 
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

    Serial.print("dcost_dpred: ");
    Serial.print(dcost_dpred);
    Serial.print("dpred_dz: ");
    Serial.print(dpred_dz);
   
    Serial.print("backprop1: ");
    Serial.print(backprop1);
    Serial.print("backprop2: ");
    Serial.print(backprop2);
    Serial.println();
    
  delay(500);
}



float Sigmoid(float x) {
  float sig = 1 / (1 + exp(-1 * x));
  return sig;
}

