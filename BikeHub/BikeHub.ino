
#define TOTAL_PLAYERS 4

int wheelPins[] = { 3, 5, 7, 9 };
int handlebarPins[] = { A0, A1, A2, A3 };


void setup()
{
  Serial.begin(9600);
 
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    pinMode(wheelPins[i], INPUT);
  }
}

void loop()
{
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    if (i != 0) {
      Serial.print(" ");
    }
    Serial.print( digitalRead(wheelPins[i]) );
    Serial.print(" ");
    Serial.print( analogRead(handlebarPins[i]) );
  }
  Serial.println();
}
