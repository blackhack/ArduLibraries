#include <TaskAction.h>

const int Inverval = 2000;
const int Inverval2 = 1000;

TaskAction task(NULL, Inverval, INFINITE_TICKS);
TaskAction task2(Handle, Inverval2, INFINITE_TICKS);

void Handle()
{
  Serial.println("Handle function!!");  
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (task.tick())
    Serial.println("Tick without handle function!!");

  task2.tick();

  // some code...
}


