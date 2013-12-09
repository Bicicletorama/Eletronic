
#define TOTAL_PLAYERS 4

int digitalPins[] = { 2, 3, 4, 5 };
int analogPins[] = { A0, A1, A2, A3 };


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
    if (i != 0) {
      Serial.print(" ");
    }
    Serial.print( digitalRead(digitalPins[i]) );
    Serial.print(" ");
    Serial.print( analogRead(analogPins[i]) );
  }
  Serial.println();
}
