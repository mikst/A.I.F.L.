/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
/*
  print out inputs when button is pressed
*/

int avg1;
int avg2;
int avg3;
int avg4;
int sampleSize = 6;

int buttonPinA = 2;
int buttonPinB = 3;
int buttonPinC = 4;

boolean buttonStatusA;
boolean last_buttonStatusA;
boolean buttonStatusB;
boolean last_buttonStatusB;
boolean buttonStatusC;
boolean last_buttonStatusC;

int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  avg1 = analogRead(A0);
  avg2 = analogRead(A1);
  avg3 = analogRead(A2);
  avg4 = analogRead(A3);

  // pins for buttons to trigger print outs
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(buttonPinC, INPUT_PULLUP);

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);
  sensorValue3 = analogRead(A2);
  sensorValue4 = analogRead(A3);
  avg1 = (avg1 * (sampleSize - 1) + sensorValue1) / sampleSize;
  avg2 = (avg2 * (sampleSize - 1) + sensorValue2) / sampleSize;
  avg3 = (avg3 * (sampleSize - 1) + sensorValue3) / sampleSize;
  avg4 = (avg4 * (sampleSize - 1) + sensorValue4) / sampleSize;

buttonStatusA=digitalRead(buttonPinA);
buttonStatusB=digitalRead(buttonPinB);
buttonStatusC=digitalRead(buttonPinC);

if (buttonStatusA==0 && last_buttonStatusA!=buttonStatusA){ 
  record(0);
}
if (buttonStatusB==0 && last_buttonStatusB!=buttonStatusB){
  record(2);
}
if (buttonStatusC==0 && last_buttonStatusC!=buttonStatusC){
  record(3);
}

last_buttonStatusA=buttonStatusA;
last_buttonStatusB=buttonStatusB;
last_buttonStatusC=buttonStatusC;
  

  delay(10);        // delay in between reads for stability
}

void record(int guesture){
  Serial.print("[");
  Serial.print(avg1);
  Serial.print(",");
  Serial.print(avg2);
  Serial.print(",");
  Serial.print(avg3);
  Serial.print(",");
  Serial.print(avg4);
  Serial.print(",");
  Serial.print(guesture);
  Serial.print("],");
  Serial.println();
}

