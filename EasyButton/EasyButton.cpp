#include "EasyButton.h"

EasyButton::EasyButton(int buttonPin, void (*function)() /* = NULL */, FunctionCallOptions call_option /* = CALL_NONE */, bool pullup /* = false */)
{
    m_function = function;
    m_call_option = call_option;
    m_current_state = false;
    m_press_notifier = false;
    m_hold = false;
    m_hold_time = 0;
    m_release_time = 0;
    m_pin = buttonPin;
    m_push_Threshold = DEFAULT_PUSH_THRESHOLD;
    m_pullup_mode = pullup;

    if (m_pullup_mode)
        pinMode(m_pin, INPUT_PULLUP);
    else
        pinMode(m_pin, INPUT);
}

void EasyButton::update(unsigned long millisec /* = NULL */)
{
    if (!millisec)
        millisec = millis();

    if (digitalRead(m_pin) == !m_pullup_mode)
    {
        if (!m_current_state && (m_hold_time <= 0 || ((long)(millisec - m_hold_time)) > long(DEBOUNCE_DELAY)))
        {
            m_current_state = true;
            m_press_notifier = true;
            m_hold_time = millisec;
            m_release_time = 0;
            if (m_function != NULL && m_call_option & CALL_IN_PUSHED)
                m_function();
        }

        if ((millisec - m_hold_time) > m_push_Threshold && !m_hold)
        {
            m_hold = true;

            if (m_function != NULL && m_call_option & CALL_IN_HOLD)
                m_function();
        }
        if (m_function != NULL && m_call_option & CALL_IN_PUSH)
            m_function();
    }
    else
    {
        if (m_current_state && (m_release_time <= 0 || ((long)(millisec - m_release_time)) > long(DEBOUNCE_DELAY)))
        {
            m_release_notifier = true;
            m_release_time = millisec;
            m_current_state = false;
            m_hold = false;
            m_hold_time = millisec;

            if (m_function != NULL && m_call_option & CALL_IN_RELEASE)
                m_function();
        }
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

bool EasyButton::IsRelease()
{
    if (m_release_notifier)
    {
        m_release_notifier = false;
        return true;
    }

    return false;
}

void EasyButton::SetCallFunction(void (*function)() /* = NULL */, FunctionCallOptions call_option /* = CALL_NONE*/)
{
    m_function = function;
    m_call_option = call_option;
}