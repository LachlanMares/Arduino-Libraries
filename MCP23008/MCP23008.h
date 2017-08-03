#ifndef MCP23008_h
#define MCP23008_h

#include "Arduino.h"
#include <Wire.h>

// MCP23017 Registers
#define MCP23008_IODIR       0x00
#define MCP23008_IPOL        0x01
#define MCP23008_GPINTEN     0x02
#define MCP23008_DEFVAL      0x03
#define MCP23008_INTCON      0x04
#define MCP23008_IOCON       0x05
#define MCP23008_GPPU        0x06
#define MCP23008_INTF        0x07
#define MCP23008_INTCAP      0x08
#define MCP23008_GPIO        0x09
#define MCP23008_OLAT        0x0A

#define MCP_OUTPUTS          0x00
#define MCP_INPUTS           0xFF
#define MCP_PULLUP_ALL       0xFF
#define MCP_ALL_ON           0xFF
#define MCP_ALL_OFF          0x00

//Address of MCP23008 IO Expander, 8 addresses available
#define MCP23008_ADDR_0      0x20
#define MCP23008_ADDR_1      0x21
#define MCP23008_ADDR_2      0x22
#define MCP23008_ADDR_3      0x23
#define MCP23008_ADDR_4      0x24
#define MCP23008_ADDR_5      0x25
#define MCP23008_ADDR_6      0x26
#define MCP23008_ADDR_7      0x27

class MCP23008
{
public:
        MCP23008();
        MCP23008(uint8_t);
        void StartI2C();
        void SetDirection(uint8_t);
        void SetDirectionBit(uint8_t,boolean);
        void SetPullUp(uint8_t);
        void SetPullUpBit(uint8_t,boolean);
        void SetPolarity(uint8_t);
        void SetBitPolarity(uint8_t,boolean);
        void EnableInterrupt(uint8_t);
        void EnableInterruptBit(uint8_t,boolean);
        void SetInterruptControl(uint8_t);
        void SetInterruptControlBit(uint8_t,boolean);
        uint8_t ReadIOBank();
        boolean ReadIOBit(uint8_t);
        void WriteIOBank(uint8_t);
        void WriteIOBit(uint8_t,boolean);

private:
        boolean ReadRegisterBit(uint8_t,uint8_t);
        void WriteRegisterBit(uint8_t,uint8_t,boolean);
        uint8_t ReadRegister(uint8_t);
        void WriteRegister(uint8_t,uint8_t);

        uint8_t _Addr;
};

#endif
