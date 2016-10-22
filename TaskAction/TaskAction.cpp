#ifndef ARDUINO
#include <stdint.h>
#include <stdlib.h>

extern unsigned long millis();
extern unsigned long micros();

#endif

#include "TaskAction.h"

TaskAction::TaskAction(void (*function)(TaskAction*), unsigned long interval, unsigned int ticks, int resolution)
{
    m_function = function;
    m_interval = interval;
    m_state = true;
    m_tick = ticks;
    m_CurrentTick = 0;
    m_LastTime = 0;
    m_resolution = resolution;
}

void TaskAction::ResetTime()
{
    m_LastTime = (m_resolution == MILLIS_RESOLUTION) ? millis() : micros();  
}

bool TaskAction::tick(unsigned long currentTime)
{
    // Check state and ticks count (if m_ticks == 0 then infinite ticks)
    if (!GetCurrentState() || (m_tick > 0 && GetCurrentTick() >= m_tick))
    {
        return false;
    }

    if (m_interval == 0) { return false; } // If interval is 0 then treat as disabled

    if (currentTime == 0)
    {
        currentTime = (m_resolution == MILLIS_RESOLUTION) ? millis() : micros();  
    }

    if(currentTime - m_LastTime > m_interval)
    {
        m_LastTime = currentTime;

        // Increase the ticks (if m_ticks == 0 then infinite ticks)
        if (m_tick > 0)
        {
            ++m_CurrentTick;
        }

        // If m_function != NULL then call that function (and optionally the debug helper)
        if (m_function != NULL)
        {
            if (m_debugHelper && m_debugHelper->on && m_debugHelper->name && m_debugHelper->name_printer)
            {
                (*m_debugHelper->name_printer)(m_debugHelper->name);
            }
            m_function(this);
        }

        return true;
    }

    return false;
}
