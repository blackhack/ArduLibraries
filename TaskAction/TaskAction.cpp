#include <Arduino.h>

#include "TaskAction.h"

TaskAction::TaskAction(void (*function)(), unsigned long interval, unsigned int ticks, char const * name)
{
    m_function = function;
    m_interval = interval;
    m_state = true;
    m_tick = ticks;
    m_CurrentTick = 0;
    m_LastTime = 0;
    m_name = name;
    m_debug = false;
}

void TaskAction::ResetTime()
{
    m_LastTime = millis();
}

bool TaskAction::tick(unsigned long millisec /* = NULL */)
{
    // Check state and ticks count (if m_ticks == 0 then infinite ticks)
    if (!GetCurrentState() || (m_tick > 0 && GetCurrentTick() >= m_tick))
    {
        return false;
    }
    
    if (m_interval == 0) // If interval is 0 then treat as disabled
    {
        return false;
    }
    
    unsigned long currentTime = millisec ? millisec : millis();

    if(currentTime - m_LastTime > m_interval)
    {
        m_LastTime = currentTime;

        // Increase the ticks (if m_ticks == 0 then infite ticks)
        if (m_tick > 0)
            ++m_CurrentTick;

        // If m_function != NULL then call that function
        if (m_function != NULL)
        {
            if (m_debug && m_name)
            {
                Serial.println(m_name);
            }
            m_function();
        }

        // Return true.
        return true;
    }

    return false;
}

void TaskAction::SetDebug(bool on)
{
    m_debug = on;
}
