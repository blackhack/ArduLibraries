#include <TaskAction.h>

const int LedPin = 13;
const int Inverval = 100;

TaskAction task(blinkLed, Inverval, INFINITE_TICKS);

bool LedState = false;
void blinkLed()
{
  LedState = !LedState;
  digitalWrite(LedPin, LedState);
}

void setup()
{
  pinMode(LedPin, OUTPUT);
}

void loop()
{
  task.tick();

  // some code...
}
