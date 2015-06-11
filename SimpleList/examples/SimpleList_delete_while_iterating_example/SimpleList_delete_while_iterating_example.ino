#include <SimpleList.h>

/*
* Open Monitor Serial and take a look.
*/

SimpleList<int> myList;

void setup()
{
  Serial.begin(9600);
  
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);
  myList.push_back(4);
  myList.push_back(5);
  myList.push_back(6);  

  for (SimpleList<int>::iterator itr = myList.begin(); itr != myList.end();)
  {
    if ((*itr) == 4) // delete this value therefore will not printing
    {
      itr = myList.erase(itr);
      continue;
    }

    Serial.println(*itr);
    ++itr;
  }
}

void loop()
{
  // Nothing here
}
