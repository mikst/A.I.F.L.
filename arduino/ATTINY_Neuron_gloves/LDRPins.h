class LDRPins
{
    int val;
    int avg;
    int sampleSize;

    
  public:
    int pin;
    float receivedData;
    int id;
    int sensorVal;
 


    LDRPins(int p, int i) {
      pin = p;
      id = i;
      receivedData = 0.0;
      sensorVal = 0;
      val = 0;
      sampleSize = 10;
      avg = analogRead(pin);
      

      pinMode(pin, INPUT);
    }

    void readPin() {
      sensorVal = analogRead(pin);
      avg = (avg * (sampleSize - 1) + sensorVal) / sampleSize;
      sensorVal = avg;
    }

    void convert(int t){
      receivedData= (t-55)/200.0;
    }


};

