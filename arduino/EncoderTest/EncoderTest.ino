/* Rotina de Interrupcao para Rotary Encoder
 
   The average rotary encoder has three pins, seen from front: A C B
   Clockwise rotation A(on)->B(on)->A(off)->B(off)
   CounterCW rotation B(on)->A(on)->B(off)->A(off)
 
   and may be a push switch with another two pins, pulled low at pin 8 in this case
*/
 
// Normalmente o rotary encoder possui 3 pinos, com o terra no meios
// usually the rotary encoders three pins have the ground pin in the middle
enum PinAssignments {
  // Ligacao dos Pinos
  encoderPinA = 2,   // DT
  encoderPinB = 3,   // CLK
  clearButton = 5    // SW (Switch)
  // Conecte o pino + em 5V e GND em GND
};

static int encoderStates[4][4] = {
  {  0,  1, -1,  0 }, // 00
  { -1,  0,  0,  1 }, // 01
  {  1,  0,  0, -1 }, // 10
  {  0, -1,  1,  0 }  // 11
};
 
volatile int encoderPos = 0;
volatile int lastEncoderState = 0;
 
 
void setup() {
 
  pinMode(encoderPinA, INPUT_PULLUP); // new method of enabling pullups
  pinMode(encoderPinB, INPUT_PULLUP); 
  pinMode(clearButton, INPUT_PULLUP);
  // turn on pullup resistors (old method)
  //digitalWrite(encoderPinA, HIGH);
  //digitalWrite(encoderPinB, HIGH);
  //digitalWrite(clearButton, HIGH);
 
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoder, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoder, CHANGE);
 
  Serial.begin(9600);  // output
}
 
void loop() { 
  if (digitalRead(clearButton) == LOW) {
    encoderPos = 0;
  }
  Serial.println(encoderPos);
}
 
// Interrupt on A changing state
void doEncoder(){
  int encoderState = (digitalRead(encoderPinA) << 1) | digitalRead(encoderPinB);
  encoderPos += encoderStates[lastEncoderState][encoderState];
  lastEncoderState = encoderState;
}
