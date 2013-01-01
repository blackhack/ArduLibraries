#include "EasyButton.h"

EasyButton::EasyButton(int buttonPin, void (*function)() /* = NULL */, FunctionCallOptions call_option /* = CALL_NONE */)
{
    m_function = function;
    m_call_option = call_option;
    m_current_state = false;
    m_press_notifier = false;
    m_hold = false;
    m_hold_time = 0;
    m_pin = buttonPin;
    m_push_Threshold = DEFAULT_PUSH_THRESHOLD;
    pinMode(m_pin, INPUT);
}

void EasyButton::update(unsigned long millisec /* = NULL */)
{
    if (!millisec)
        millisec = millis();

    if (digitalRead(m_pin) == HIGH)
    {

        if (millisec - m_hold_time > m_push_Threshold && !m_hold)
        {
            m_hold = true;

            if (m_function != NULL && m_call_option & CALL_IN_HOLD)
                m_function();
        }

        if (!m_current_state)
        {
            m_current_state = true;
            m_press_notifier = true;
            m_hold_time = millisec;

            if (m_function != NULL && m_call_option & CALL_IN_PUSHED)
                m_function();
        }

        if (m_function != NULL && m_call_option & CALL_IN_PUSH)
            m_function();
    }
    else
    {
        m_current_state = false;
        m_hold = false;
        m_hold_time = millisec;
    }
}

bool EasyButton::IsPushed()
{
    if (m_press_notifier)
    {
        m_press_notifier = false;
        return true;
    }

    return false;
}

bool EasyButton::IsHold()
{
    if (m_hold)
    {
        m_hold_time = millis();
        m_hold = false;
        return true;
    }
    return false;
}