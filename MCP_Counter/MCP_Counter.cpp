#include "MCP_Counter.h"

MCP_Counter::MCP_Counter(){
  MCP23017 _mcp;
}

void MCP_Counter::Initialise(int MCP_Addr){
  _mcp.Begin(MCP_Addr);
  _mcp.SetDirection('A',MCP_INPUTS);
  _mcp.SetPullUp('A',MCP_PULLUP_ALL);
  
  _mcp.SetDirection('B',MCP_OUTPUTS); 
  _mcp.WriteIOBank('B',0xFE);
  delay(1);
  _mcp.WriteIOBit('B',CCLR,true);
  _mcp.WriteIOBit('B',RCLK,false);  

  _LastMillisC0 = millis();
 
  _LastCounter0Value = 0;
  _LastCounter1Value = 0;
  _LastMillisC1 = _LastMillisC0;
  _LastCounter0Value = 0;    
}

void MCP_Counter::ReadCounter16Bit(char Bank,unsigned int* CounterValue,unsigned int* Difference,unsigned int* Period){
  unsigned long _MillisNow = millis();
  *CounterValue = Read16Counter(Bank);
  switch(Bank){
    case 'A':
      *Period = (unsigned int)(_MillisNow - _LastMillisC0);
      _LastMillisC0 = _MillisNow;
      if(*CounterValue >= _LastCounter0Value){
        *Difference = *CounterValue - _LastCounter0Value;
      } else {
          *Difference = (65535 - _LastCounter0Value) + *CounterValue;
        }
      _LastCounter0Value = *CounterValue;
      break;
    case 'B':
      *Period = (unsigned int)(_MillisNow - _LastMillisC1);
      _LastMillisC1 = _MillisNow;
      if(*CounterValue >= _LastCounter1Value){
        *Difference = *CounterValue - _LastCounter1Value;
      } else {
          *Difference = (65535 - _LastCounter1Value) + *CounterValue;
        }
      _LastCounter1Value = *CounterValue; 
      break;
  }
}

void MCP_Counter::ReadCounter32Bit(unsigned long* CounterValue,unsigned long* Difference,unsigned int* Period){
  unsigned long _MillisNow = millis();
  *CounterValue = Read32Counter();
  *Period = (unsigned int)(_MillisNow - _LastMillisC0);
  _LastMillisC0 = _MillisNow;
  if(*CounterValue >= _LastCounter0Value){
        *Difference = *CounterValue - _LastCounter0Value;
      } else {
          *Difference = (4294967295 - _LastCounter0Value) + *CounterValue;
        }
  _LastCounter0Value = *CounterValue; 
}

unsigned int MCP_Counter::Read16Counter(unsigned char Bank){
   unsigned int _TempCounter = 0;  
  _mcp.WriteIOBit('B',RCLK,true);
  switch(Bank){
    case 'A':
      _mcp.WriteIOBank('B',0xEF);
      _TempCounter = _mcp.ReadIOBank('A') << 8;
      _mcp.WriteIOBank('B',0xFF); 
      _mcp.WriteIOBank('B',0xDF);
      _TempCounter += _mcp.ReadIOBank('A');
      _mcp.WriteIOBank('B',0xFF);
      break;
    case 'B':
      _mcp.WriteIOBank('B',0xFB);
      _TempCounter = _mcp.ReadIOBank('A') << 8;
      _mcp.WriteIOBank('B',0xFF);  
      _mcp.WriteIOBank('B',0xF7);
      _TempCounter += _mcp.ReadIOBank('A');
      _mcp.WriteIOBank('B',0xFF); 
      break;
  }
  _mcp.WriteIOBit('B',RCLK,false);
  return _TempCounter;
}

unsigned long MCP_Counter::Read32Counter(){
  unsigned long _TempCounter = 0;
  _mcp.WriteIOBit('B',RCLK,true);
  _mcp.WriteIOBank('B',0xFB);
  _TempCounter = (unsigned long)(_mcp.ReadIOBank('A')) << 24;
  _mcp.WriteIOBank('B',0xFF); 
  _mcp.WriteIOBank('B',0xF7);
  _TempCounter += (unsigned long)(_mcp.ReadIOBank('A')) << 16;
  _mcp.WriteIOBank('B',0xFF);
  _mcp.WriteIOBank('B',0xEF);
  _TempCounter += _mcp.ReadIOBank('A') << 8;
  _mcp.WriteIOBank('B',0xFF); 
  _mcp.WriteIOBank('B',0xDF);
  _TempCounter += _mcp.ReadIOBank('A');
  _mcp.WriteIOBank('B',0xFF);
  _mcp.WriteIOBit('B',RCLK,false);
  return _TempCounter;  
}
