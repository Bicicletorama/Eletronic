/*
--- PLAYER 1 ---
Pin 2 - Reed switch
Pin 3 - Encoder 1 (DT)
Pin 4 - Enconder 2 (CLK)
Pin 5 - Encoder switch (SW)
Pin 6 - N/C
pin 7 - Status
--- PLAYER 2 ---
Pin 8 - Reed switch
Pin 9 - Encoder 1 (DT)
Pin 10 - Enconder 2 (CLK)
Pin 11 - Encoder switch (SW)
Pin 12 - N/C
Pin 13 - Status
--- PLAYER 3 ---
Pin 14 - Reed switch
Pin 15 - Encoder 1 (DT)
Pin 16 - Enconder 2 (CLK)
Pin 17 - Encoder switch (SW)
Pin 18 - N/C
Pin 19 - Status
--- PLAYER 4 ---
Pin 20 - Reed switch
Pin 21 - Encoder 1 (DT)
Pin 22 - Enconder 2 (CLK)
Pin 23 - Encoder switch (SW)
Pin 24 - N/C
Pin 25 - Status
*/

#include "Bike.h"


#define NUM_PLAYERS 1

Bike bikes[NUM_PLAYERS];

void setup()
{
  Serial.begin(115200);
  
  int pin = 2;
  for (int i = 0; i < NUM_PLAYERS; i++) {
    bikes[i].setup(pin, pin+1, pin+2, pin+3, pin+4, pin+5);
    pin = pin+6;
  }
}

void loop() 
{
  String message = "";
  for (int i = 0; i < NUM_PLAYERS; i++) {
    bikes[i].loop();
    if (i > 0) {
      message += " ";
    }
    message += bikes[i].getData();
  }
  Serial.println(message);
}
