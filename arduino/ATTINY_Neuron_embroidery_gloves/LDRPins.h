class LDRPins
{
    int val;
    int avg;
    int sampleSize;
    int sensorMax;
    int sensorMin;


  public:
    int pin;
    float receivedData;
    int sensorVal;
    

    LDRPins(int p) {
      pin = p;
      receivedData = 0.0;
      sensorVal = 0;
      val = 0;
      sampleSize = 10;
      avg = analogRead(pin);      
    }

    void setRange(int sMin, int sMax){
      sensorMin=sMin;
      sensorMax=sMax;
    }


    void readPin() {
      sensorVal = analogRead(pin);
      avg = (avg * (sampleSize - 1) + sensorVal) / sampleSize;
      sensorVal = avg;

      val = constrain(sensorVal, sensorMin, sensorMax);
        val = map(val, sensorMin, sensorMax, 55, 255);

      val = constrain(val, 55, 255);
      receivedData = (val - 55) / 200.0;
    }




};

