/*
#name: EasyButton.cpp
#version: 1.0
#author: José Aristizábal
#nick: Blackhack
#contact: davidaristi.0504@gmail.com
*/

#ifndef _EASYBUTTON_h
#define _EASYBUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DEFAULT_PUSH_THRESHOLD 1000

enum FunctionCallOptions
{
    CALL_NONE = 0,
    CALL_IN_PUSHED = 1,
    CALL_IN_PUSH = 2,
    CALL_IN_HOLD = 4,
    CALL_IN_ALL = (CALL_IN_PUSHED | CALL_IN_PUSH | CALL_IN_HOLD)
};

class EasyButton
{
private:
    bool m_current_state;
    bool m_press_notifier;
    bool m_hold;
    unsigned long m_hold_time;
    int m_pin;
    unsigned int m_push_Threshold;
    void (*m_function)();
    FunctionCallOptions m_call_option;

public:
    EasyButton(int buttonPin, void (*function)() = NULL, FunctionCallOptions call_option = CALL_NONE);

    void update(unsigned long millisec = NULL);
    bool IsPushed();
    bool InPush() { return m_current_state; }
    bool IsHold();
    void SetThreshold(unsigned int ms) { m_push_Threshold = ms; }
};


#endif // _EASYBUTTON_h