#include "DimmerOne.h"

const int OUTPUT_PIN = 8;
const int ZERO_PIN = 2;

bool increasing = true;

void setup()
{
    dimmerOne.init(ZERO_PIN, OUTPUT_PIN, 60.0, 150);
    dimmerOne.Start();
}

void loop()
{
    double angle = dimmerOne.GetFiringAngle();

    if (angle <= 10)
        increasing = true;
    else if (angle >= 150)
        increasing = false;

    if (increasing)
        ++angle;
    else
        --angle;

    dimmerOne.SetFiringAngle(angle);

    delay(15);
}
