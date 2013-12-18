#include <ShiftEasier.h>

ShiftEasier shiftout(8, 12, 11, TWO_REGISTER);

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(50);
  Serial.println("# 0 - 15: ");
}

void loop()
{  
  if (Serial.available() > 0) 
  {
    int led = Serial.parseInt();
    shiftout.Write(led, !shiftout.Read(led));
  }
}

