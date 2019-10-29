
class LED_node
{
    long startTime;
    int send_step;


  public:
    int pin;
    int sensorVal;
    int mode;
    long signalLength;
    int id;
    int threshold;
    int brightness;


    LED_node(int p, int i)
    {
      pin = p;
      id = i;
      sensorVal = 0;
      mode = 0;
      send_step = 0;
      signalLength = 0;
      startTime = 0;
      threshold = 100;
      brightness = 0;
    }

    void readLight() {
      for (int i = 0; i < 6; i++) {
        pinMode(i + 14, OUTPUT);
      }
      pinMode(pin, INPUT);
      delay(10);

      sensorVal = analogRead(pin);

      if (sensorVal > threshold) {
        if (mode == 0) {
          startTime = millis();
          mode = 1;
        }
      }
      if (mode == 1 && sensorVal < threshold - 30) {
        signalLength = millis() - startTime;
        if (signalLength > 50) {
          signalLength = map(signalLength, 50, 1200, 1, 100);
          signalLength = constrain(signalLength, 1, 100);
          signalLength = signalLength * 12;
          mode = 2;
        }
        else mode = 0;
      }

    }

    void sendLight() {
      long currentTime = millis();

      if (send_step == 0) {
        delay(10);
        pinMode(pin, OUTPUT);
        send_step = 1;
        startTime = currentTime;
      }
      if (send_step == 1 && currentTime - startTime  > 1000 ) {
        // turn on both the light
        digitalWrite(pin, HIGH);
        brightness = 255;
        startTime = currentTime;
        send_step = 2;
      }
      if (send_step == 2 && currentTime - startTime > signalLength ) {
        digitalWrite(pin, LOW);
        brightness = 0;
        startTime = currentTime;
        send_step = 3;
      }

      if (send_step == 3 && currentTime - startTime > 1000 ) {
        digitalWrite(pin, LOW);
        signalLength = 0;
        send_step = 0;
        mode = 0;
      }
    }

};



// create LED nodes. arguments are pin number and id (not in use at the moment)
LED_node node1(15, 0);
LED_node node2(16, 1);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {

// mode indicates if it should be in reading or sending
  if (node1.mode < 2) {
    node1.readLight();
  }
  if (node2.mode < 2) {
    node2.readLight();
  }

  if (node1.mode == 2) {
    node1.sendLight();
  }
  if (node2.mode == 2) {
    node2.sendLight();
  }

  //prints out for debuging. works with plotter
  debug();



  delay(10);        // delay in between reads for stability
}

void debug() {
  Serial.print(600);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(node1.threshold);
  Serial.print(",");
  Serial.print(node1.sensorVal);
  Serial.print(",");
  Serial.print(node2.sensorVal);
  Serial.print(",");
  Serial.print(node1.brightness);
  Serial.print(",");
  Serial.print(node2.brightness);
  Serial.println();
}

