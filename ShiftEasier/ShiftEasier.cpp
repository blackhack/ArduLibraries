//
//
//

#include "ShiftEasier.h"

ShiftEasier::ShiftEasier(int latch, int clock, int data, int registers /* = ONE_REGISTER */)
{
    _latchPin = latch;
    _clockPin = clock;
    _dataPin = data;
    _registers = registers;
    _currentBits = new byte[registers]();
    
    init();
}

ShiftEasier::~ShiftEasier()
{
    Clear();
    delete _currentBits;
}

void ShiftEasier::init()
{

    pinMode(_latchPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    Clear();
}

void ShiftEasier::shiftOut(int myDataPin, int myClockPin, byte myDataOut)
{
    int i = 0;
    int pinState;

    digitalWrite(myDataPin, LOW);
    digitalWrite(myClockPin, LOW);

    for (i=7; i>=0; i--)
    {
        digitalWrite(myClockPin, LOW);

        if (myDataOut & (1<<i))
            pinState = 1;
        else
            pinState = 0;

        digitalWrite(myDataPin, pinState);
        digitalWrite(myClockPin, HIGH);
        digitalWrite(myDataPin, LOW);
    }

    digitalWrite(myClockPin, LOW);
}

void ShiftEasier::Clear()
{
    digitalWrite(_latchPin, LOW);

    for (int i = 0; i < _registers; ++i)
    {
        _currentBits[i] = B00000000;
        shiftOut(_dataPin, _clockPin, _currentBits[i]);
    }

    digitalWrite(_latchPin, HIGH);
}

void ShiftEasier::Write(int whichPin, int whichState)
{
    digitalWrite(_latchPin, LOW);
    
    for (int i = _registers; i > 0; --i)
    {
        if (i == GetRegister(whichPin))
            bitWrite(_currentBits[i-1], mapPin(whichPin, PIN_1_0, PIN_1_7), whichState);
            
        shiftOut(_dataPin, _clockPin, _currentBits[i-1]);
    }

    digitalWrite(_latchPin, HIGH);
}

int ShiftEasier::Read(int whichPin)
{
    return bitRead(_currentBits[GetRegister(whichPin)-1], mapPin(whichPin, PIN_1_0, PIN_1_7));
}

int ShiftEasier::GetRegister(int whichPin)
{
    int count = 0;
    for (int i = whichPin; i >= 0;)
    {
        i -= 8;
        ++count;
    }
    return count;
}

int ShiftEasier::mapPin(int x, int out_min, int out_max)
{
    if (x < 0 || out_min < 0 || out_max < 0 || x < out_min)
        return -1;
    
    if (x >= out_min && x <= out_max)
        return x;
    else if (x > out_max)
        return x % (out_max+1);
        
    return - 1;
}

