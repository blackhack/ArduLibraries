/*
#name: TaskAction.cpp
#version: 1.0
#author: José Aristizábal
#nick: Blackhack
#contact: davidaristi.0504@gmail.com
*/

#ifndef _TASKACTION_h
#define _TASKACTION_h

#if defined(ARDUINO)
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
#endif

#define INFINITE_TICKS 0
#define MILLIS_RESOLUTION 0
#define MICROS_RESOLUTION 1

typedef void (*DEBUG_NAME_PRINTER)(char const * const name);

struct TaskActionDebugHelper
{
    char * name;
    DEBUG_NAME_PRINTER name_printer;
    bool on;
};

class TaskAction
{
private:
    unsigned int m_tick;
    unsigned int m_CurrentTick;
    bool m_state;
    unsigned long m_interval;
    unsigned long m_LastTime;
    int m_resolution;
    void (*m_function)(TaskAction *);
    TaskActionDebugHelper * m_debugHelper;

public:
    TaskAction(void (*function)(TaskAction*), unsigned long interval, unsigned int ticks, int resolution = MILLIS_RESOLUTION);

    bool tick(unsigned long currentTime = 0);

    void SetResolution(int resolution) { m_resolution = resolution; }
    void SetInterval(unsigned long interval) { m_interval = interval; }
    void SetTicks(unsigned int ticks) { m_tick = ticks; }
    void Enable(bool state) { m_state = state; }
    bool GetCurrentState() { return m_state; }
    unsigned int GetCurrentTick() { return m_CurrentTick; }
    unsigned long GetCurrentInterval() { return m_interval; }
    void ResetTicks() { m_CurrentTick = 0; }
    void ResetTime();

    void SetDebugHelper(TaskActionDebugHelper * debugHelper) {m_debugHelper = debugHelper;}
};

#endif // _TASKACTION_h