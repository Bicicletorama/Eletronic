// referencia ::  http://arduinotronics.blogspot.nl/2013/09/using-rotary-encoder-with-arduino.html

#define PINS_PER_BIKE 4
#define TOTAL_BIKES 2

int pinsBikeA[] = {2, 3, 4, 5};
int pinsBikeB[] = {21, 20, 17, 16};

volatile unsigned int encoderPos[] = {200, 200};  // a counter for the dial
unsigned int lastReportedPos[] = {1, 1};   // change management
static boolean rotating[] = {false, false};      // debounce management

unsigned int lastReportedImpulse[] = {1, 1};

// interrupt service routine vars
boolean A_set[] = {false, false};
boolean B_set[] = {false, false};

void setup()
{
  for (int i = 0; i < PINS_PER_BIKE; i++) {
    pinMode(pinsBikeA[i], INPUT_PULLUP);
    pinMode(pinsBikeB[i], INPUT_PULLUP);
  }

// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

// encoder pin on interrupt 2 (pin 21)
  attachInterrupt(2, doEncoderC, CHANGE);
// encoder pin on interrupt 3 (pin 20)
  attachInterrupt(3, doEncoderD, CHANGE);

  Serial.begin(9600);  // output
}

// main loop, work is done by interrupt service routines, this one only prints stuff
void loop()
{
  // PRINTA OS VALORES DO IMPULSO

  //impulso 1  
  if (digitalRead(pinsBikeA[3]) == 1 && lastReportedImpulse[0] == 0) {
    Serial.print("1");
  } else {
    Serial.print("0");
  }

  lastReportedImpulse[0] = digitalRead(pinsBikeA[3]);
  Serial.print(" ");

  //impulso 2
  if (digitalRead(pinsBikeB[3]) == 1 && lastReportedImpulse[1] == 0) {
    Serial.print("1");
  } else {
    Serial.print("0");
  }

  lastReportedImpulse[1] = digitalRead(pinsBikeB[3]);
  Serial.print(" ");

  //impulso 3 e 4
  Serial.print("0");
  Serial.print(" ");
  Serial.print("0");
  Serial.print(" ");


  // PRINTA OS VALORES DA DIREÇÃO

  //direção 1
  rotating[0] = true;  // reset the debouncer

  if (lastReportedPos[0] != encoderPos[0]) {
    if (lastReportedPos[0] > encoderPos[0]) {
      Serial.print("-1");
    } else {
      Serial.print("1");
    }

    lastReportedPos[0] = encoderPos[0];
  } else {
    Serial.print("0");
  }

  Serial.print(" ");

  //direção 2
  rotating[1] = true;  // reset the debouncer

  if (lastReportedPos[1] != encoderPos[1]) {
    if (lastReportedPos[1] > encoderPos[1]) {
      Serial.print("-1");
    } else {
      Serial.print("1");
    }

    lastReportedPos[1] = encoderPos[1];
  } else {
    Serial.print("0");    
  }

  Serial.print(" ");

  //direção 3 e 4
  Serial.print("0");
  Serial.print(" ");
  Serial.print("0");
  Serial.print(" ");

  // PRINTA OS VALORES DO CLICK

  //click 1
  if (digitalRead(pinsBikeA[2]) == LOW )  {
    Serial.print("1");
    encoderPos[0] = 200;
  } else {
    Serial.print("0");
  }

  Serial.print(" ");

  //click 2
  if (digitalRead(pinsBikeB[2]) == LOW )  {
    Serial.print("1");
    encoderPos[1] = 200;
  } else {
    Serial.print("0");
  }

  Serial.print(" ");

  //click 3 e 4
  Serial.print("0");
  Serial.print(" ");
  Serial.print("0");
  Serial.println();
}

// Interrupt on A changing state
void doEncoderA()
{
  // debounce
  if ( rotating[0] ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change? 
  if( digitalRead(pinsBikeA[0]) != A_set[0] ) {  // debounce once more
    A_set[0] = !A_set[0];

    // adjust counter + if A leads B
    if ( A_set[0] && !A_set[1] ) 
      encoderPos[0] += 1;

    rotating[0] = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderB()
{
  if ( rotating[0] ) delay (1);
  if( digitalRead(pinsBikeA[1]) != A_set[1] ) {
    A_set[1] = !A_set[1];
    //  adjust counter - 1 if B leads A
    if( A_set[1] && !A_set[0] ) 
      encoderPos[0] -= 1;

    rotating[0] = false;
  }
}

// Interrupt on A changing state
void doEncoderC()
{
  // debounce
  if ( rotating[1] ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change? 
  if( digitalRead(pinsBikeB[0]) != B_set[0] ) {  // debounce once more
    B_set[0] = !B_set[0];

    // adjust counter + if A leads B
    if ( B_set[0] && !B_set[1] ) 
      encoderPos[1] += 1;

    rotating[1] = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderD()
{
  if ( rotating[1] ) delay (1);
  if( digitalRead(pinsBikeB[1]) != B_set[1] ) {
    B_set[1] = !B_set[1];
    //  adjust counter - 1 if B leads A
    if( B_set[1] && !B_set[0] ) 
      encoderPos[1] -= 1;

    rotating[1] = false;
  }
}