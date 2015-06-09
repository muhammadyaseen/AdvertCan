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

int trayPin  = 9;

boolean processRunning = false;
int minSecsBetweenEmails = 5;
 
long lastSend = -minSecsBetweenEmails * 1000L;
 
static boolean firstPass = true;
void setup() {
  
  pinMode( powerPin, OUTPUT);
  pinMode( pausePlayPin, OUTPUT);
  pinMode( rewindPin, OUTPUT);
  pinMode( trayPin, OUTPUT);

  pinMode( motorPinA, OUTPUT);
  pinMode( motorPinB, OUTPUT);
  
  pinMode( pirPin, INPUT);
  
  //keep motors turned off
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  
  digitalWrite(rewindPin, LOW);
  
  //player off
  digitalWrite(powerPin, LOW);
  delay(500);
  //player on
  digitalWrite(powerPin, HIGH);
  
  delay(3000);

  //player pause  
  digitalWrite(pausePlayPin, LOW);
  delay(500);
  digitalWrite(pausePlayPin, HIGH);
  delay(500);
  digitalWrite(pausePlayPin, LOW);
  
  // tray defaults to LOW
  digitalWrite(trayPin, LOW);

}

void loop() {
  
  if ( presenceDetected() )
  {
      processRunning = true;
      
      //turn on motors
      digitalWrite(motorPinA, HIGH);
      digitalWrite(motorPinB, HIGH);
      
      delay(2000);
      
      if ( firstPass )
      {
        //play
        //digitalWrite(pausePlayPin, LOW);
        
        digitalWrite(pausePlayPin, HIGH);
        delay(400);
        digitalWrite(pausePlayPin, LOW);        
      }
      else 
      { 
        //rewind - auto plays
       digitalWrite(rewindPin, HIGH);
       delay(400);
       digitalWrite(rewindPin, LOW);
        
      }
      
      //open tray
      digitalWrite( trayPin, HIGH );
      delay(500);
      digitalWrite( trayPin, LOW );
      
            
      //player is now on, wait a few seconds for advertisement to finish
      delay(20000);
     
      //pause
      digitalWrite(pausePlayPin, HIGH);
      delay(500);
      digitalWrite(pausePlayPin, LOW);
      
      //close tray
      digitalWrite( trayPin, HIGH );
      delay(500);
      digitalWrite( trayPin, LOW );
        
      //keep motors turned off
      digitalWrite(motorPinA, HIGH);
      digitalWrite(motorPinB, LOW);
      
      firstPass = false;
      
      delay(10000);
      
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
  
