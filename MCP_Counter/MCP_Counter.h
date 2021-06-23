#ifndef MCP_Counter_h
#define MCP_Counter_h
#include "Arduino.h"
#include <MCP23017.h>

// SN74LV8154 Pins MCP port 1
#define GAL                  5  
#define GAU                  4  
#define GBL                  3  
#define GBU                  2  
#define RCLK                 1  
#define CCLR                 0 

class MCP_Counter
{
public:
	MCP_Counter();
        void Initialise(int);
        void ReadCounter16Bit(char,unsigned int*,unsigned int*,unsigned int*);
        void ReadCounter32Bit(unsigned long*,unsigned long*,unsigned int*);
private:
        unsigned int _LastCounter0Value,_LastCounter1Value,_Counter0Value,_Counter1Value;
        unsigned long _LastCounter32BitValue,_LastMillisC0,_LastMillisC1;
        MCP23017 _mcp;  
        
        unsigned int Read16Counter(unsigned char);
        unsigned long Read32Counter();
};

#endif
