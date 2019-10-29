class SensorPins
{
    int avg;
    int sampleSize;

  public:
    int pin;
    int id;
    int sensorVal;
    int LEDval;


    SensorPins(int p, int i) {
      pin = p;
      id = i;
      sensorVal = 0;
      LEDval = 0;
      sampleSize = 10;
      avg = analogRead(pin);
      pinMode(pin, INPUT);
    }

    void readPins() {
      sensorVal = analogRead(pin);
      avg = (avg * (sampleSize - 1) + sensorVal) / sampleSize;
      sensorVal = avg;
      LEDval = map(sensorVal, 0, 1023, 55, 255);
      LEDval = constrain(LEDval, 55, 255);
    }

    void report() {
      //      mySerial.print("id: ");
      //      mySerial.print(id);
      //      mySerial.print(" sensor: ");
      //      mySerial.print(sensorVal);
      //      mySerial.print(" data: ");
      //      mySerial.print(receivedData);
      //      mySerial.print(" ,\t")


    }

};

