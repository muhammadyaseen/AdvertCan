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

int pirPin   = 8;

boolean processRunning = false;
int minSecsBetweenEmails = 30;
 
long lastSend = -minSecsBetweenEmails * 1000L;
 
void setup() {
  
  pinMode( powerPin, OUTPUT);
  pinMode( pausePlayPin, OUTPUT);
  pinMode( rewindPin, OUTPUT);
  
  pinMode( motorPinA, OUTPUT);
  pinMode( motorPinB, OUTPUT);
  
  //keep motors turned off
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  //player on
  digitalWrite(powerPin, HIGH);
  
  digitalWrite(pausePlayPin, HIGH);
  delay(1000);
  digitalWrite(pausePlayPin, LOW);
  
  pinMode( pirPin, INPUT);

}

void loop() {
  
  if ( presenceDetected() )
  {
      processRunning = true;
      
      //turn on motors
      digitalWrite(motorPinA, HIGH);
      digitalWrite(motorPinB, HIGH);
      
      delay(2000);
      
      //turn on player
      digitalWrite(pausePlayPin, HIGH);
      delay(1000);
      digitalWrite(pausePlayPin, LOW);
      
      //player is now on, wait a few seconds for advertisement to finish
      delay(25000);
      
      digitalWrite(rewindPin, HIGH);
      
      //turn off the player now
      //digitalWrite(powerPin, LOW);
      
      //keep motors turned off
      digitalWrite(motorPinA, HIGH);
      digitalWrite(motorPinB, LOW);
      
      delay(15000);
      
  }
}

boolean presenceDetected()
{
  long now = millis();
  if (digitalRead(pirPin) == HIGH)
  {
    if (now > (lastSend + minSecsBetweenEmails * 1000L))
    {
      Serial.println("MOVEMENT");
      
      lastSend = now;
      
      return true;
    }
    else
    {
      Serial.println("Too soon, in threshold");
      return false;
    }
  }  
  
  return false;
}
  
