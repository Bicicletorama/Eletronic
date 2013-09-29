
#define TOTAL_PLAYERS 4


int const MIN_ANALOG_VALUE = 200;
int const MAX_ANALOG_VALUE = 800;

int digitalPins[] = { 2, 4, 5, 6 };
int analogPins[] = { A2, A4, A1, A3 };


int lastDigitalRead[] = { 0, 0, 0, 0 };


void setup()
{
  Serial.begin(9600);
  
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    pinMode(digitalPins[i], INPUT);
  }
}

void loop()
{
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    int value = digitalRead(digitalPins[i]);
    if (lastDigitalRead[i] == 0 && value == 1) {
      Serial.print(1);
    } else {
      Serial.print(0);
    }
    Serial.print(" ");
    
    lastDigitalRead[i] = value;
  }
  
  float direction = 0;
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    direction = map(analogRead(analogPins[i]), MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, -100, 100)/100.f;
    if (direction > 1.0f) {
      direction = 1.0f;
    } else if (direction < -1.0f) {
      direction = -1.0f;
    }
    Serial.print(direction);
    Serial.print(" ");
  }
  
  Serial.println();
  
  delay(2);
}
