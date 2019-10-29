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

      // long conversion from LDR input to possible LED intensity
      if (sensorVal <= 100) {
        val = constrain(sensorVal, 32, 100);
        val = map(val, 32, 100, 55, 80);
      }
      else if (sensorVal > 100 && sensorVal <= 181) {
        val = sensorVal;
        val = map(val, 101, 181, 81, 118);
      }
      else if (sensorVal > 181 && sensorVal <= 222) {
        val = sensorVal;
        val = map(val, 182, 222, 119, 145);
      }
      else if (sensorVal > 222 && sensorVal <= 260) {
        val = sensorVal;
        val = map(val, 223, 260, 145, 172);
      }
      else if (sensorVal > 260 && sensorVal <= 300) {
        val = sensorVal;
        val = map(val, 261, 300, 173, 204);
      }
      else if (sensorVal > 300 && sensorVal <= 340) {
        val = sensorVal;
        val = map(val, 301, 340, 205, 228);
      }
      else if (sensorVal > 340) {
        val = constrain(sensorVal, 341, 359);
        val = map(val, 341, 359, 229, 255);
      }

      val = constrain(val, 55, 255);
      receivedData = (val - 55) / 200.0;
    }




};

