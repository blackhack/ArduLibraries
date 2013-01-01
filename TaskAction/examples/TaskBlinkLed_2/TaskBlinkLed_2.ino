#include <TaskAction.h>

const int LedPin = 13;
const int Inverval = 100;
const int ticks = 50;

TaskAction task(blinkLed, Inverval, ticks);

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
  task.tick();

  if (task.GetCurrentTick() >= ticks)
    Serial.println("Task finish!!");

  // some code...
}
