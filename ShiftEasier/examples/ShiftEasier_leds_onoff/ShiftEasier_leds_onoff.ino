#include <ShiftEasier.h>

ShiftEasier shiftout(8, 12, 11);

void setup()
{
  // nothing to do
}

void loop()
{
  shiftout.Write(PIN_1_0, HIGH);
  delay(100);
  shiftout.Write(PIN_1_1, HIGH);
  delay(100);
  shiftout.Write(PIN_1_2, HIGH);
  delay(100);
  shiftout.Write(PIN_1_3, HIGH);
  delay(100);
  shiftout.Write(PIN_1_4, HIGH);
  delay(100);
  shiftout.Write(PIN_1_5, HIGH);
  delay(100);
  shiftout.Write(PIN_1_6, HIGH);
  delay(100);
  shiftout.Write(PIN_1_7, HIGH);
  delay(100);  
  shiftout.Write(PIN_1_0, LOW);
  delay(100);
  shiftout.Write(PIN_1_1, LOW);
  delay(100);
  shiftout.Write(PIN_1_2, LOW);
  delay(100);
  shiftout.Write(PIN_1_3, LOW);
  delay(100);
  shiftout.Write(PIN_1_4, LOW);
  delay(100);
  shiftout.Write(PIN_1_5, LOW);
  delay(100);
  shiftout.Write(PIN_1_6, LOW);
  delay(100);
  shiftout.Write(PIN_1_7, LOW);
  delay(100);    
}

