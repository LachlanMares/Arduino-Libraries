#ifndef MCP23017_h
#define MCP23017_h
#include "Arduino.h"
#include <Wire.h>

// MCP23017 Registers
#define MCP23017_IODIRA      0x00
#define MCP23017_IPOLA       0x02
#define MCP23017_GPINTENA    0x04
#define MCP23017_DEFVALA     0x06
#define MCP23017_INTCONA     0x08
#define MCP23017_IOCONA      0x0A
#define MCP23017_GPPUA       0x0C
#define MCP23017_INTFA       0x0E
#define MCP23017_INTCAPA     0x10
#define MCP23017_GPIOA       0x12
#define MCP23017_OLATA       0x14

#define MCP23017_IODIRB      0x01
#define MCP23017_IPOLB       0x03
#define MCP23017_GPINTENB    0x05
#define MCP23017_DEFVALB     0x07
#define MCP23017_INTCONB     0x09
#define MCP23017_IOCONB      0x0B
#define MCP23017_GPPUB       0x0D
#define MCP23017_INTFB       0x0F
#define MCP23017_INTCAPB     0x11
#define MCP23017_GPIOB       0x13
#define MCP23017_OLATB       0x15

#define MCP_OUTPUTS          0x00
#define MCP_INPUTS           0xFF
#define MCP_PULLUP_ALL		 0xFF

//Address of MCP23017 IO Expander, 8 addresses available
#define MCP23017_ADDR_0	     0x20
#define MCP23017_ADDR_1	     0x21
#define MCP23017_ADDR_2	     0x22
#define MCP23017_ADDR_3	     0x23
#define MCP23017_ADDR_4	     0x24
#define MCP23017_ADDR_5	     0x25
#define MCP23017_ADDR_6	     0x26
#define MCP23017_ADDR_7	     0x27

class MCP23017
{
public:
        MCP23017();
        MCP23017(int);
        void SetDirection(uint8_t, uint8_t);
        void SetDirectionBit(uint8_t ,uint8_t, bool);
        void SetPullUp(uint8_t, uint8_t);
        void SetPullUpBit(uint8_t, uint8_t, uint8_t);
        void SetPolarity(uint8_t, uint8_t);
        void SetBitPolarity(uint8_t, uint8_t, bool);
        void EnableInterrupt(uint8_t, uint8_t);
        void EnableInterruptBit(uint8_t, uint8_t, bool);
        void SetInterruptControl(uint8_t, uint8_t);
        void SetInterruptControlBit(uint8_t, uint8_t, bool);
        uint8_t ReadIOBank(uint8_t);
        bool ReadIOBit(uint8_t, uint8_t);
        void WriteIOBank(uint8_t, uint8_t);
        void WriteIOBit(uint8_t, uint8_t, bool);

private:
        bool ReadRegisterBit(uint8_t, uint8_t);
        void WriteRegisterBit(uint8_t, uint8_t, bool);
        uint8_t ReadRegister(uint8_t);
        void WriteRegister(uint8_t, uint8_t);

        int _Addr;
};

#endif
