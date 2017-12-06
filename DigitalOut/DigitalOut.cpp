#include "DigitalOut.h"

DigitalOut::DigitalOut(int pinNumber)
{
  _useDelay = false;
  _pinNumber = pinNumber;
}

bool DigitalOut::SetInitial(bool state)
{
  _currentState = State;
  pinMode(_pinNumber, OUTPUT);
  digitalWrite(_pinNumber, state);
  return _currentState;
}

bool DigitalOut::On()
{
  _useDelay = false;
  _currentState = HIGH;
  digitalWrite(_pinNumber, _currentState);
  return _currentState;
}

bool DigitalOut::Off()
{
  _useDelay = false;
  _currentState = LOW;
  digitalWrite(_pinNumber, _currentState);
  return _currentState;
}

bool DigitalOut::SetOnFor(int timerValue)
{
  if(timerValue > 0)
  {
    _useDelay = true;
    _nextState = LOW;
    _currentState = HIGH;
    digitalWrite(_pinNumber, _currentState);
    _delayCompare = timerValue;
    _lastMillis = millis();
  } else
    {
      _currentState = LOW;
      digitalWrite(_pinNumber,_currentState);
    }
  return _currentState;
}

bool DigitalOut::SetOffFor(int timerValue)
{
  if(timerValue > 0)
  {
    _useDelay = true;
    _nextState = HIGH;
    _currentState = LOW;
    digitalWrite(_pinNumber, _currentState);
    _delayCompare = timerValue;
    _lastMillis = millis();
  } else
    {
      _currentState = HIGH;
      digitalWrite(_pinNumber, HIGH);
    }
  return _currentState;
}

boolean DigitalOut::Update()
{
  if(_UseDelay)
  {
    if(abs(millis() - _lastMillis) >= _delayCompare)
    {
      _currentState = _nextState;
      digitalWrite(_pinNumber, _currentState);
      _useDelay = false;
    }
  }
  return _currentState;
}

bool DigitalOut::Status()
{
  return _currentState;
}





