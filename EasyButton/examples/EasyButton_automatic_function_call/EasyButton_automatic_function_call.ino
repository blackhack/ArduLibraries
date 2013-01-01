#include <EasyButton.h>

const int buttonPin = 11;
const int ledPin = 13;

// Const for the call option.
/*
 CALL_IN_PUSHED
 CALL_IN_PUSH
 CALL_IN_HOLD
 CALL_IN_ALL
 */

EasyButton button(buttonPin);

// This call foo() automatically in case of hold button
EasyButton button2(buttonPin, foo, CALL_IN_HOLD);

void foo()
{
  digitalWrite(ledPin, HIGH);
}

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  // this saves calls to millis()
  unsigned long myMillis = millis();
  button.update(myMillis);
  button2.update(myMillis);

  if (button.InPush())
    Serial.println("SPAM!!!");
}


