#ifndef MCP3304_h
#define MCP3304_h

#define SINGLE_MODE       0x0C
#define DIFF_MODE         0x08

#include <Arduino.h>

class MCP3304
{
  public:
      MCP3304(int CS);
      int readADC(int pin, boolean sgl);
      int readSingle(int pin);
      int readDifferential(int pin);
  private:
    int _CS;
};
#endif
