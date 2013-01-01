/*
#name: TaskAction.cpp
#version: 1.0
#author: José Aristizábal
#nick: Blackhack
#contact: davidaristi.0504@gmail.com
*/

#ifndef _TASKACTION_h
#define _TASKACTION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define INFINITE_TICKS 0

class TaskAction
{
private:
    unsigned int m_tick;
    unsigned int m_CurrentTick;
    bool m_state;
    unsigned long m_interval;
    unsigned long m_LastTime;
    void (*m_function)();

public:
    TaskAction(void (*function)(), unsigned long interval, unsigned int ticks);

    bool tick(unsigned long millisec = NULL);
    void SetInterval(unsigned long interval) { m_interval = interval; }
    void SetTicks(unsigned int ticks) { m_tick = ticks; }
    void Enable(bool state) { m_state = state; }
    bool GetCurrentState() { return m_state; }
    unsigned int GetCurrentTick() { return m_CurrentTick; }
    void ResetTicks() { m_CurrentTick = 0; }
};

#endif // _TASKACTION_h