/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

int avg;
int avg2;
int sampleSize=20;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  avg=analogRead(A0);
  avg2=analogRead(A5);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
 // int sensorValue2 = analogRead(A5);
 avg = (avg*(sampleSize-1)+sensorValue)/sampleSize;
 //avg2 = (avg2*(sampleSize-1)+sensorValue2)/sampleSize;

  if (sensorValue>275){
    avg2=500;
  }
  else{
    avg2=100;
  }
  
  
  // print out the value you read:
  Serial.print(1023);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(avg);
   Serial.print(",");
  Serial.print(avg2);
  Serial.println();
  
  delay(10);        // delay in between reads for stability
}
