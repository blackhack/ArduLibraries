#include "DimmerOne.h"

const int OUTPUT_PIN = 8;
const int ZERO_PIN = 2;

bool IsRunning = true;

void setup()
{
    dimmerOne.init(ZERO_PIN, OUTPUT_PIN, 60.0, 90);
    dimmerOne.Start();

    Serial.begin(250000);
}

void loop()
{
    if (Serial.available())
    {
        byte header = Serial.read();

        switch (header)
        {
            case 's':
                if (IsRunning)
                    dimmerOne.Stop();
                else
                    dimmerOne.Start();
                IsRunning = !IsRunning;
                break;
            case 'a':
                if (!dimmerOne.SetFiringAngle(Serial.parseFloat()))
                    Serial.println("Invalid angle");
                break;
            case 'f':
                if (!dimmerOne.SetFrecuency(Serial.parseFloat()))
                    Serial.println("Invalid frecuency");
                break;
            case 'z':
                if (!dimmerOne.SetZeroCrossingFix(Serial.parseInt()))
                    Serial.println("Compensation out of range (-5000 to 5000 uS)");
                break;
            default:
                Serial.read();
                break;
        }
    }
}