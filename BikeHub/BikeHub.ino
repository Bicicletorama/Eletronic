
#define TOTAL_PLAYERS 4

int connectionPins[] = { 2, 4, 6, 8 };
int wheelPins[] = { 3, 5, 7, 9 };
int handlebarPins[] = { A0, A1, A2, A3 };


void setup()
{
  Serial.begin(9600);
 
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    pinMode(connectionPins[i], INPUT);
    pinMode(wheelPins[i], INPUT);
  }
}

void loop()
{
  for (int i = 0; i < TOTAL_PLAYERS; i++) {
    if (i != 0) {
      Serial.print(" ");
    }
    Serial.print( digitalRead(connectionPins[i]) );
    Serial.print(" ");
    Serial.print( digitalRead(wheelPins[i]) );
    Serial.print(" ");
    Serial.print( analogRead(handlebarPins[i]) );
  }
  Serial.println();
}
