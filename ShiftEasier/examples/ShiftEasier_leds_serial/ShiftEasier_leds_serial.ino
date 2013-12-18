#include <ShiftEasier.h>

ShiftEasier shiftout(8, 12, 11);

void setup()
{
  Serial.begin(9600);
  Serial.println("# 0 - 7: ");
}

void loop()
{
  if (Serial.available() > 0) 
  {
    int led = Serial.read() - 48;
    shiftout.Write(led, !shiftout.Read(led));
  }
}

