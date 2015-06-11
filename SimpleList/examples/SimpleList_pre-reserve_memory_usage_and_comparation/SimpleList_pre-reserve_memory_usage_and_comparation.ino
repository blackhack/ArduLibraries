#include <SimpleList.h>

/*
* Open Monitor Serial and take a look.
*/

void setup()
{
  Serial.begin(9600);

  // Test with pre-reserve memory.
  {
    SimpleList<int> myList;
    myList.reserve(300); // Pre-reserve the memory, so later the inserts and deletes will be much faster

    // Insert 300 numbers to test the speed.
    int start_timer = micros();
    for (int i = 0; i < 300; ++i)
      myList.push_back(i);
    int end_timer = micros();

    Serial.print("Takes ");
    Serial.print(end_timer - start_timer);
    Serial.println(" microseconds, to insert all elements with pre-reserve memory");
  }

  // Test without pre-reserve memory.
  {
    SimpleList<int> myList;
    //myList.reserve(300); // does not reserve memory

    // Insert 300 numbers to test the speed.
    int start_timer = micros();
    for (int i = 0; i < 300; ++i)
      myList.push_back(i);
    int end_timer = micros();

    Serial.print("Takes ");
    Serial.print(end_timer - start_timer);
    Serial.println(" microseconds, to insert all elements without pre-reserve memory");
  }
}

void loop()
{
  // Nothing here
}
