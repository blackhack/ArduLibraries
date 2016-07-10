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
    char const * m_name;
    bool m_debug;

public:
    TaskAction(void (*function)(), unsigned long interval, unsigned int ticks, char const * n_name = NULL);

    bool tick(unsigned long millisec = 0);
    void SetInterval(unsigned long interval) { m_interval = interval; }
    void SetTicks(unsigned int ticks) { m_tick = ticks; }
    void Enable(bool state) { m_state = state; }
    bool GetCurrentState() { return m_state; }
    unsigned int GetCurrentTick() { return m_CurrentTick; }
    unsigned long GetCurrentInterval() { return m_interval; }
    void ResetTicks() { m_CurrentTick = 0; }
    void ResetTime();
    void SetDebug(bool on);
};

#endif // _TASKACTION_h