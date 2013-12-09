
#define TOTAL_PLAYERS 4

int digitalPins[] = { 2, 4, 12, 13 };
int analogPins[] = { A0, A5, A2, A3 };

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
    Serial.print(digitalRead(digitalPins[i]));
    Serial.print(" ");
  }
  
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    Serial.print( analogRead(analogPins[i]) );
    Serial.print(" ");
  }
  
  Serial.println();
  
  delay(2);
}
