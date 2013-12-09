
#define TOTAL_PLAYERS 4


int const MIN_ANALOG_VALUE = 0;
int const MAX_ANALOG_VALUE = 1024;

int digitalPins[] = { 2, 4, 12, 13 };
int analogPins[] = { A0, A5, A2, A3 };

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
  
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    Serial.print( map(analogRead(analogPins[i]), MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, -100, 100)/100.f );
    Serial.print(" ");
  }
  
  Serial.println();
  
  delay(2);
}
