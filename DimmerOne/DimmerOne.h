#ifndef _DIMMERONE_h
#define _DIMMERONE_h

#include "Arduino.h"

class DimmerOne
{
public:
    DimmerOne();

    void init(uint8_t zero_crossing_pin, uint8_t output_pin, double frecuency = 60.0, double firing_angle = 90.0);

    bool Start();
    bool Stop();

    bool SetFiringAngle(double angle);
    bool SetFrecuency(double frecuency);
    bool SetZeroCrossingFix(int32_t microSecondsFix);

    double GetFiringAngle() { return _firing_angle; }
    double GetFrecuency() { return _frecuency; }
    int32_t GetZeroCrossingFix() { return _zero_cross_usec_fix; }

    // Do not call this!
    void ZeroCrossEvent();
    void ComparatorBEvent();
    void ComparatorAEvent();

private:
    void CalculateTCounts();

    uint8_t ZERO_CROSS_PIN;
    uint8_t OUTPUT_PIN;
    double _frecuency;
    double _firing_angle;

    // Compensation when the zero cross detector is not accurate enough.
    int32_t _zero_cross_usec_fix;

    bool _valid_zero_crossing;
    bool alreadyInit;
};

void ZeroCrossEventCaller();

extern DimmerOne dimmerOne;

#endif
