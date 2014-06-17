#include <SimpleList.h>

/*
* Open Monitor Serial and enter some numbers.
*/

SimpleList<int> myList;

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter one digit numbers.");
}

void loop()
{
  if (Serial.available())
  {
    myList.push_back(Serial.read());

    Serial.println("---BEGIN Data in myList---");
    for (SimpleList<int>::iterator itr = myList.begin(); itr != myList.end(); ++itr)
    {
      Serial.print("ASCII: ");
      Serial.print(*itr);
      Serial.print(", Value: ");
      Serial.println((*itr) - 48);
    }      
    Serial.println("---END Data in myList---");   
  }
}
