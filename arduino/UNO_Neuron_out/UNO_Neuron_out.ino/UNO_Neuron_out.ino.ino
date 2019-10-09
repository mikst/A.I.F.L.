

float n_input1;
float n_input2;

float w1;
float w2;
float b;

float prediction;

int nodeNumber = 3;

int val;


void setup() {
  pinMode(9, OUTPUT); // nuron out



  // set the data rate for the SoftwareSerial port
 Serial.begin(9600);
Serial.println("Hello, world?");

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
   val= map(val1, 400, 820, 0, 100);
  val=constrain(val,0,100);
  n_input1=val/100.0;
  int val2 = analogRead(A3); 
  val= map(val2, 200, 920, 0, 100);
  val=constrain(val,0,100);
  n_input2=val/100.0;

  Serial.print(val1);
  Serial.print(" : ");
  Serial.print(val2);
  Serial.print(" : ");
}

else{
  int val = analogRead(A2);
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

  int output = int (255 * prediction);
  output = constrain(output, 0, 255);
  analogWrite(9, output);

 Serial.print(n_input1);
  Serial.print(" : ");
  Serial.print(n_input2);
  Serial.print(" : ");
  Serial.print(prediction);
  Serial.print(" : ");
  Serial.print(1023);
  Serial.print(" : ");
  Serial.print(0);
  Serial.println();
  delay(50);



}



float Sigmoid(float x) {
  float sig = 1 / (1 + exp(-1 * x));
  return sig;
}

