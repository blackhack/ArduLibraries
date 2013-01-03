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
#define DEBOUNCE_DELAY 50

enum FunctionCallOptions
{
    CALL_NONE = 0,
    CALL_IN_PUSHED = 1,
    CALL_IN_PUSH = 2,
    CALL_IN_HOLD = 4,
    CALL_IN_RELEASE = 8,
    CALL_IN_ALL = (CALL_IN_PUSHED | CALL_IN_PUSH | CALL_IN_HOLD | CALL_IN_RELEASE)
};

class EasyButton
{
private:
    bool m_current_state;
    bool m_press_notifier;
    bool m_release_notifier;
    bool m_hold;
    bool m_pullup_mode;
    unsigned long m_hold_time;
    unsigned long m_release_time;
    int m_pin;
    unsigned int m_push_Threshold;
    void (*m_function)();
    FunctionCallOptions m_call_option;

public:
    EasyButton(int buttonPin, void (*function)() = NULL, FunctionCallOptions call_option = CALL_NONE, bool pullup = false);

    void update(unsigned long millisec = NULL);
    bool IsPushed();
    bool InPush() { return m_current_state; }
    bool IsHold();
    bool IsRelease();
    void SetThreshold(unsigned int ms) { m_push_Threshold = ms; }
    void SetCallFunction(void (*function)() = NULL, FunctionCallOptions call_option = CALL_NONE);
};


#endif // _EASYBUTTON_h