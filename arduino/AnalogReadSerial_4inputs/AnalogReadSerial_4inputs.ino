/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

int avg1;
int avg2;
int avg3;
int avg4;
int sampleSize=6;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  avg1=analogRead(A0);
  avg2=analogRead(A1);
  avg3=analogRead(A2);
  avg4=analogRead(A3);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue1= analogRead(A0);
  int sensorValue2= analogRead(A1);
  int sensorValue3= analogRead(A2);
  int sensorValue4= analogRead(A3);
  avg1 = (avg1*(sampleSize-1)+sensorValue1)/sampleSize;
  avg2 = (avg2*(sampleSize-1)+sensorValue2)/sampleSize;
  avg3 = (avg3*(sampleSize-1)+sensorValue3)/sampleSize;
  avg4 = (avg4*(sampleSize-1)+sensorValue4)/sampleSize;
  
  // print out the value you read:
  Serial.print(1023);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(avg1);
  Serial.print(",");
  Serial.print(avg2);
    Serial.print(",");
  Serial.print(avg3);
  Serial.print(",");
  Serial.print(avg4);
  Serial.println();
  
  delay(10);        // delay in between reads for stability
}
