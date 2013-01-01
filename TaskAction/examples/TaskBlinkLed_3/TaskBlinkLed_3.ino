#include <TaskAction.h>

const int LedPin = 13;
const int Inverval = 5000;

TaskAction task(blinkLed, Inverval, INFINITE_TICKS);

bool LedState = false;
void blinkLed()
{
  LedState = !LedState;
  digitalWrite(LedPin, LedState);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
}

void loop()
{
  if (task.tick())
    Serial.println("Tick!!");

  // some code...
}
