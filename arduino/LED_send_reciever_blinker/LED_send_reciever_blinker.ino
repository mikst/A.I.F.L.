/*
  to test if the LED send-reciever works.
  sends sequences of light wiht counter
*/

int led = 13;
int led2 = 8;

int cnt;
int cnt2 = 5;

long startTiming;
int steps;
long startTiming2;
int steps2;

int timing;
int timing2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {


  if (steps == 0) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    startTiming = millis();
    steps = 1;
  }

  if (millis() - startTiming > timing && steps == 1) {
    digitalWrite(led, LOW);
    steps = 2;
  }

  if (millis() - startTiming > 5000  && steps == 2) {
    steps = 0;
    cnt++;
    cnt = cnt % 15;
    timing = cnt * 100 + 50;
  }


  if (steps2 == 0) {
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    startTiming2 = millis();
    steps2 = 1;
  }

  if (millis() - startTiming2 > timing2 && steps2 == 1) {
    digitalWrite(led2, LOW);
    steps2 = 2;
  }

  if (millis() - startTiming2 > 5000   && steps2 == 2) {
    steps2 = 0;
    cnt2++;
    cnt2 = cnt2 % 15;
    timing2 = cnt2 * 100 + 50;
  }

}
