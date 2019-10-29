
byte lookupTable[] = {55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 58, 58, 58, 58, 58, 59, 59, 60, 61, 61, 61, 62, 62, 62, 63, 63, 64, 64, 65, 65, 65, 65, 66, 68, 69, 69, 70, 70, 71, 71, 71, 72, 72, 72, 72, 72, 72, 73, 73, 73, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 77, 77, 77, 78, 78, 78, 78, 80, 80, 81, 81, 82, 82, 83, 83, 83, 83, 84, 85, 85, 86, 86, 86, 86, 87, 87, 88, 89, 89, 90, 90, 90, 91, 91, 91, 91, 92, 92, 93, 94, 94, 94, 95, 96, 96, 96, 97, 97, 98, 99, 99, 99, 100, 100, 101, 101, 102, 102, 103, 104, 104, 105, 105, 106, 106, 107, 107, 108, 108, 109, 109, 110, 110, 111, 111, 112, 112, 113, 113, 114, 115, 115, 115, 116, 116, 116, 117, 117, 118, 119, 122, 123, 124, 125, 127, 127, 128, 129, 130, 131, 131, 132, 133, 134, 134, 135, 135, 135, 136, 137, 138, 138, 139, 139, 139, 140, 140, 140, 141, 141, 142, 142, 143, 143, 143, 143, 144, 144, 144, 145, 146, 146, 147, 149, 151, 153, 153, 154, 154, 155, 156, 157, 158, 159, 160, 161, 161, 161, 162, 162, 162, 162, 163, 163, 163, 163, 163, 164, 164, 165, 165, 166, 167, 168, 169, 170, 171, 172, 172, 173, 173, 174, 174, 175, 175, 176, 176, 176, 177, 178, 179, 180, 181, 181, 182, 182, 183, 183, 184, 184, 184, 185, 186, 186, 187, 188, 189, 190, 191, 193, 195, 197, 199, 200, 201, 202, 203, 204, 205, 205, 206, 207, 207, 208, 208, 209, 210, 211, 211, 211, 212, 213, 213, 214, 215, 215, 216, 217, 217, 217, 218, 219, 219, 220, 220, 220, 221, 221, 222, 223, 223, 223, 224, 225, 226, 226, 227, 228, 230, 232, 233, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 246, 248, 250, 252, 255};

int avg1;
int avg2;
int sampleSize = 10;

int LDRval;
int POTval;
int LEDval;

int LDRdata;

float sentData;
float receivedData;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  avg1 = analogRead(A0);
  avg2 = analogRead(A5);

  pinMode(9, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  // read the LDR
  LDRval = analogRead(A0);
  avg1 = (avg1 * (sampleSize - 1) + LDRval) / sampleSize;
  LDRval = avg1;
  LDRval = LDRval - 31; // 32 is the lowest value at light intensity 55
  LDRval = constrain(LDRval, 0, 326);
  LDRdata = lookupTable[LDRval];
  receivedData = (LDRdata-55)/200.0;



  // read the POT and control the LED intensity
  POTval = analogRead(A5);
  avg2 = (avg2*(sampleSize-1)+POTval)/sampleSize;
  POTval= avg2;
  LEDval = map (POTval, 0, 1023, 55, 255);
  sentData = (LEDval-55)/200.0;
  analogWrite(9, LEDval);


  // print out the value you read:
  Serial.print(300);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(sentData);
  Serial.print(",");
  Serial.print(receivedData);
  Serial.println();



  delay(10);        // delay in between reads for stability
}
