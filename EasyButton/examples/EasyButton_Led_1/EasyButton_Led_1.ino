#include <EasyButton.h>

const int buttonPin = 11;
const int ledPin = 13;

EasyButton button(buttonPin);

void setup() 
{
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  button.update();

  if (button.IsPushed())
    digitalWrite(ledPin, HIGH);
}

