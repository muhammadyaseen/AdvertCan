/*
 *
 *
 */

// Pin declarations

int powerPin       = 11;
int pausePlayPin   = 10;
int rewindPin      = 12;

int motorPinA      = A0;
int motorPinB      = A1;

int pirSensorPin   = 8;

void setup() {
  
  pinMode( powerPin, OUTPUT);
  pinMode( pausePlayPin, OUTPUT);
  pinMode( rewindPin, OUTPUT);
  
  pinMode( motorPinA, OUTPUT);
  pinMode( motorPinB, OUTPUT);
  
  pinMode( pirSensorPin, INPUT);

}

void loop() {
  
  
  
}
