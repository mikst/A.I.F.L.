

int avg1;
int avg2;
int sampleSize=10;

int LDRval;
int POTval;
int LEDval;

int cnt=50;
long previousMillis;

long writingMillis = 500;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  avg1=analogRead(A0);
  avg2=analogRead(A5);

  pinMode(9,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  // read the LDR
  LDRval = analogRead(A0);
  avg1 = (avg1*(sampleSize-1)+LDRval)/sampleSize;
  LDRval = avg1;
  //LDRval = map(LDRval,74,355,70,240);
 

  long current = millis();

  if (current - previousMillis >50){
previousMillis = current;
 cnt++;
 cnt=cnt%256;
  // read the POT and control the LED intensity
  POTval = analogRead(A5);
  //avg2 = (avg2*(sampleSize-1)+POTval)/sampleSize;
  //POTval= avg2;
  LEDval = map (POTval,0,1023,55,255);
  analogWrite(9,LEDval);
  //analogWrite(9,cnt);
  }

if (current - writingMillis > 50){
  writingMillis = current;
    // print out the value you read:
//  Serial.print(1023);
//  Serial.print(",");
//  Serial.print(0);
//  Serial.print(",");
  Serial.print(LDRval);
   Serial.print(",");
  Serial.print(cnt);
  Serial.println();
  }



 
  

  
  delay(10);        // delay in between reads for stability
}
