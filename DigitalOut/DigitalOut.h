#ifndef DigitalOut_h
#define DigitalOut_h
#include "Arduino.h"

class DigitalOut
{
public:
        DigitalOut(int);
        bool SetInitial(bool);
        bool On();
        bool Off();
        bool SetOnFor(int);
        bool SetOffFor(int);
        bool Update();
        bool Status();

private:
        bool _useDelay, _currentState, _nextState;
        int _pinNumber, _delayCompare;
        unsigned long _lastMillis;
};

#endif
