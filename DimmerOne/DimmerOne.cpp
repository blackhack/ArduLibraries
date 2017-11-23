#include "DimmerOne.h"

DimmerOne dimmerOne;

DimmerOne::DimmerOne()
{
    alreadyInit = false;
    _zero_cross_usec_fix = 1000;
}

void DimmerOne::init(uint8_t zero_crossing_pin, uint8_t output_pin, double frecuency /*= 60.0*/, double firing_angle /*= 90.0*/)
{
    if (alreadyInit)
        return;
    alreadyInit = true;

    ZERO_CROSS_PIN = zero_crossing_pin;
    OUTPUT_PIN = output_pin;
    _frecuency = frecuency;
    _firing_angle = firing_angle;

    pinMode(OUTPUT_PIN, OUTPUT);
    pinMode(ZERO_CROSS_PIN, INPUT);

    // Arduino have some default options in init() that we dont want (this may broken further calls to analogWrite())
    TCCR1A = 0;
    TCCR1B = 0;

    uint8_t oldSREG = SREG;
    cli();
    CalculateTCounts();
    SREG = oldSREG;

    // Enable COMPA and COMPB interruptions of TIMER1
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);

    _valid_zero_crossing = true;
}

bool DimmerOne::Start()
{
    if (!alreadyInit)
        return false;

    uint8_t oldSREG = SREG;
    cli();
    CalculateTCounts();
    SREG = oldSREG;

    attachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN), ZeroCrossEventCaller, RISING);

    return true;
}

bool DimmerOne::Stop()
{
    if (!alreadyInit)
        return false;

    detachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN));

    return false;
}

bool DimmerOne::SetFiringAngle(double angle)
{
    if (!alreadyInit)
        return false;

    if (angle > 180 || angle < 0)
        return false;

    _firing_angle = angle;

    return true;
}

bool DimmerOne::SetFrecuency(double frecuency)
{
    if (!alreadyInit)
        return false;

    if (frecuency > 65 || frecuency < 45)
        return false;

    _frecuency = frecuency;

    return true;
}

bool DimmerOne::SetZeroCrossingFix(int32_t microSecondsFix)
{
    if (!alreadyInit)
        return false;

    if (microSecondsFix < -5000 || microSecondsFix > 5000)
        return false;

    _zero_cross_usec_fix = microSecondsFix;

    return true;
}

void DimmerOne::CalculateTCounts()
{
    // Only works in 16Mhz boards!
    const unsigned long FrecuecyClockPrescale = 16000000 / 8;

    double firing_angle_rad = _firing_angle * (2 * PI / 360);
    double firing_time = (firing_angle_rad / (2 * PI * _frecuency)) + (_zero_cross_usec_fix / 1000000.0);
    unsigned long Tcounts = (unsigned long)((firing_time / (1.0 / FrecuecyClockPrescale)) - 1);

    OCR1B = Tcounts;
    OCR1A = Tcounts + 399; // Turn-off gate 200uS later
}

void ZeroCrossEventCaller()
{
    dimmerOne.ZeroCrossEvent();
}

ISR(TIMER1_COMPB_vect)
{
    dimmerOne.ComparatorBEvent();
}

ISR(TIMER1_COMPA_vect)
{
    dimmerOne.ComparatorAEvent();
}

void DimmerOne::ZeroCrossEvent()
{
    if (!_valid_zero_crossing)
        return;
    _valid_zero_crossing = false;

    // Restart counter (no need to call cli() inside an ISR)
    TCNT1 = 0;

    // Enable/start CTC and set prescaler to 8
    TCCR1B |= (1 << WGM12) | (1 << CS11);
}

void DimmerOne::ComparatorBEvent()
{
    digitalWrite(OUTPUT_PIN, HIGH);
}

void DimmerOne::ComparatorAEvent()
{
    digitalWrite(OUTPUT_PIN, LOW);

    // Disable/stop CTC
    TCCR1B = 0;

    // Update Tcounts in case of user change angle o something
    // No need to call cli() inside an ISR
    CalculateTCounts();

    // Next zero cross is a valid one
    _valid_zero_crossing = true;
}
