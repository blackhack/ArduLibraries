#include "DimmerOne.h"

const int OUTPUT_PIN = 8;
const int ZERO_PIN = 2;

void setup()
{
    dimmerOne.init(ZERO_PIN, OUTPUT_PIN, 60.0, 90);
    dimmerOne.Start();
}

void loop()
{

}