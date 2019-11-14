class sensorPins
{
    int avg;
    int sampleSize;


  public:
    int pin;
    int sensorVal;
    int brightness;
    

    sensorPins(int p) {
      pin = p;
      sensorVal = 0;
      sampleSize = 10;
      avg = analogRead(pin);      
    }



    void readPin() {
      sensorVal = analogRead(pin);
      avg = (avg * (sampleSize - 1) + sensorVal) / sampleSize;
      sensorVal = avg;
      brightness = map(sensorVal,0,1023,55,255);

    }




};

