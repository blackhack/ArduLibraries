// ShiftEasier.h

#ifndef _SHIFTEASIER_h
#define _SHIFTEASIER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "constants.h"

class ShiftEasier
{
private:
    int _latchPin;
    int _clockPin;
    int _dataPin;
    int _registers;
    byte* _currentBits;

    void init();
    void shiftOut(int myDataPin, int myClockPin, byte myDataOut);

public:
    ShiftEasier(int latch, int clock, int data, int registers = ONE_REGISTER);
    ~ShiftEasier();
    
    void Clear();
    void Write(int whichPin, int whichState);
    int Read(int whichPin);
    int GetRegister(int whichPin);
    int mapPin(int x, int out_min, int out_max);
};

#endif

