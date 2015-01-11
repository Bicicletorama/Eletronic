#include "Arduino.h"


int encoderStates[4][4] = {
  {  0,  1, -1,  0 }, // 00
  { -1,  0,  0,  1 }, // 01
  {  1,  0,  0, -1 }, // 10
  {  0, -1,  1,  0 }  // 11
};


class Bike 
{
  public:
  
    int wheelPin;
    int encoderPinA; // DT
    int encoderPinB; // CLK
    int encoderPinSwitch; // SW (Switch)
    int statusPin;

    boolean wheelValue;
    boolean lastWheel;

    int encoderPos;
    int lastEncoderState;
  
    Bike() 
    {
      wheelValue = false;
      lastWheel = false;
      encoderPos = 0;
      lastEncoderState = 0;
    };
    
    
    void setup(int pin3, int pin4, int pin5, int pin6, int pin7, int pin8) 
    { 
      wheelPin = pin3;
      encoderPinA = pin4;
      encoderPinB = pin5;
      encoderPinSwitch = pin6;
      statusPin = pin8;

      pinMode(wheelPin, INPUT_PULLUP);
      pinMode(encoderPinA, INPUT_PULLUP);
      pinMode(encoderPinB, INPUT_PULLUP);
      pinMode(encoderPinSwitch, INPUT_PULLUP);
      pinMode(statusPin, INPUT_PULLUP);
      
    };
    
    
    void loop() 
    {
      // wheel
      boolean wheel = digitalRead(wheelPin);
      if (lastWheel == HIGH && wheel == LOW) {
        wheelValue = true;
      } else {
        wheelValue = false;
      }
      lastWheel = wheel;
      
      // encoder
      if (digitalRead(encoderPinSwitch) == LOW) {
        // reset encoder
        encoderPos = 0;
      } else {
        // check and increment changes
        int encoderState = (digitalRead(encoderPinA) << 1) | digitalRead(encoderPinB);
        if (lastEncoderState != encoderState) {
          encoderPos += encoderStates[lastEncoderState][encoderState]; 
        }
        lastEncoderState = encoderState;
      }
      
    };

    String getData() 
    {
      return String(!digitalRead(statusPin)) + " " +String(wheelValue) + " " + String(encoderPos);
    };
    
    
};


 
 
