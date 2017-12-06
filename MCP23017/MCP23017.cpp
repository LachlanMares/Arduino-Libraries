#include "MCP23017.h"

MCP23017::MCP23017()
{
    _Addr = MCP23017_ADDR_0;
}

MCP23017::MCP23017(int Addr)
{
    _Addr = Addr;
}

void MCP23017::SetDirection(uint8_t Bank_Number, uint8_t RegVal){
  switch(Bank_Number)
  {
    case 'A':
      WriteRegister(MCP23017_IODIRA, RegVal);
      break;
    case 'B':
      WriteRegister(MCP23017_IODIRB, RegVal);
      break;
    case MCP23017_IODIRA:
      WriteRegister(MCP23017_IODIRA, RegVal);
      break;
    case MCP23017_IODIRB:
      WriteRegister(MCP23017_IODIRB, RegVal);
      break;
  }
}

void MCP23017::SetDirectionBit(uint8_t Bank_Number,uint8_t BitNum, bool BitValue){
  switch(Bank_Number)
  {
    case 'A':
      WriteRegisterBit(MCP23017_IODIRA, BitNum, BitValue);
      break;
    case 'B':
      WriteRegisterBit(MCP23017_IODIRB, BitNum, BitValue);
      break;
    case MCP23017_IODIRA:
      WriteRegisterBit(MCP23017_IODIRA, BitNum, BitValue);
      break;
    case MCP23017_IODIRB:
      WriteRegisterBit(MCP23017_IODIRB, BitNum, BitValue);
      break;
  }
}

void MCP23017::SetPullUp(uint8_t Bank_Number, uint8_t RegVal){
  switch(Bank_Number)
  {
    case 'A':
      WriteRegister(MCP23017_GPPUA, RegVal);
      break;
    case 'B':
      WriteRegister(MCP23017_GPPUB, RegVal);
      break;
    case MCP23017_GPPUA:
      WriteRegister(MCP23017_GPPUA, RegVal);
      break;
    case MCP23017_GPPUB:
      WriteRegister(MCP23017_GPPUB, RegVal);
      break;
  }
}

void MCP23017::SetPullUpBit(uint8_t Bank_Number, uint8_t BitNum, bool BitValue){
  switch(Bank_Number)
  {
    case 'A':
      WriteRegisterBit(MCP23017_GPPUA, BitNum, BitValue);
      break;
    case 'B':
      WriteRegisterBit(MCP23017_GPPUB, BitNum, BitValue);
      break;
    case MCP23017_GPPUA:
      WriteRegisterBit(MCP23017_GPPUA, BitNum, BitValue);
      break;
    case MCP23017_GPPUB:
      WriteRegisterBit(MCP23017_GPPUB, BitNum, BitValue);
      break;
  }
}

void MCP23017::SetPolarity(uint8_t Bank_Number, uint8_t RegVal){
  switch(Bank_Number)
  {
    case 'A':
      WriteRegister(MCP23017_IPOLA, RegVal);
      break;
    case 'B':
      WriteRegister(MCP23017_IPOLB, RegVal);
      break;
    case MCP23017_IPOLA:
      WriteRegister(MCP23017_IPOLA, RegVal);
      break;
    case MCP23017_IPOLB:
      WriteRegister(MCP23017_IPOLB, RegVal);
      break;
  }
}

void MCP23017::SetBitPolarity(uint8_t Bank_Number, uint8_t BitNum, bool BitValue)
{
  switch(Bank_Number)
  {
    case 'A':
      WriteRegisterBit(MCP23017_IPOLA, BitNum, BitValue);
      break;
    case 'B':
      WriteRegisterBit(MCP23017_IPOLB, BitNum, BitValue);
      break;
    case MCP23017_IPOLA:
      WriteRegisterBit(MCP23017_IPOLA, BitNum, BitValue);
      break;
    case MCP23017_IPOLB:
      WriteRegisterBit(MCP23017_IPOLB, BitNum, BitValue);
      break;
  }
}

void MCP23017::EnableInterrupt(uint8_t Bank_Number, uint8_t RegVal)
{
  switch(Bank_Number)
  {
    case 'A':
      WriteRegister(MCP23017_GPINTENA, RegVal);
      break;
    case 'B':
      WriteRegister(MCP23017_GPINTENB, RegVal);
      break;
    case MCP23017_GPINTENA:
      WriteRegister(MCP23017_GPINTENA, RegVal);
      break;
    case MCP23017_GPINTENB:
      WriteRegister(MCP23017_GPINTENB, RegVal);
      break;
  }
}

void MCP23017::EnableInterruptBit(uint8_t Bank_Number, uint8_t BitNum, bool BitValue)
{
  switch(Bank_Number)
  {
    case 'A':
      WriteRegisterBit(MCP23017_GPINTENA, BitNum, BitValue);
      break;
    case 'B':
      WriteRegisterBit(MCP23017_GPINTENB, BitNum, BitValue);
      break;
    case MCP23017_GPINTENA:
      WriteRegisterBit(MCP23017_GPINTENA, BitNum, BitValue);
      break;
    case MCP23017_GPINTENB:
      WriteRegisterBit(MCP23017_GPINTENB, BitNum, BitValue);
      break;
  }
}

void MCP23017::SetInterruptControl(uint8_t Bank_Number, uint8_t RegVal)
{
  switch(Bank_Number)
  {
    case 'A':
      WriteRegister(MCP23017_INTCONA, RegVal);
      break;
    case 'B':
      WriteRegister(MCP23017_INTCONB, RegVal);
      break;
    case MCP23017_INTCONA:
      WriteRegister(MCP23017_INTCONA, RegVal);
      break;
    case MCP23017_INTCONB:
      WriteRegister(MCP23017_INTCONB, RegVal);
      break;
  }
}

void MCP23017::SetInterruptControlBit(uint8_t Bank_Number, uint8_t BitNum, bool BitValue){
  switch(Bank_Number)
  {
    case 'A':
      WriteRegisterBit(MCP23017_INTCONA, BitNum, BitValue);
      break;
    case 'B':
      WriteRegisterBit(MCP23017_INTCONB, BitNum, BitValue);
      break;
    case MCP23017_INTCONA:
      WriteRegisterBit(MCP23017_INTCONA, BitNum, BitValue);
      break;
    case MCP23017_INTCONB:
      WriteRegisterBit(MCP23017_INTCONB, BitNum, BitValue);
      break;
  }
}

uint8_t MCP23017::ReadIOBank(uint8_t Bank_Number)
{
  switch(Bank_Number)
  {
    case 'A':
      return ReadRegister(MCP23017_GPIOA);
      break;
    case 'B':
      return ReadRegister(MCP23017_GPIOB);
      break;
    case MCP23017_GPIOA:
      return ReadRegister(MCP23017_GPIOA);
      break;
    case MCP23017_GPIOB:
      return ReadRegister(MCP23017_GPIOB);
      break;
  }
}

bool MCP23017::ReadIOBit(uint8_t Bank_Number, uint8_t BitNum){
  switch(Bank_Number)
  {
    case 'A':
      return ReadRegisterBit(MCP23017_GPIOA, BitNum);
      break;
    case 'B':
      return ReadRegisterBit(MCP23017_GPIOB, BitNum);
      break;
    case MCP23017_GPIOA:
      return ReadRegisterBit(MCP23017_GPIOA, BitNum);
      break;
    case MCP23017_GPIOB:
      return ReadRegisterBit(MCP23017_GPIOB, BitNum);
      break;
  }
}

void MCP23017::WriteIOBank(uint8_t Bank_Number, uint8_t RegVal)
{
  switch(Bank_Number)
  {
    case 'A':
      WriteRegister(MCP23017_GPIOA, RegVal);
      break;
    case 'B':
      WriteRegister(MCP23017_GPIOB, RegVal);
      break;
    case MCP23017_GPIOA:
      WriteRegister(MCP23017_GPIOA, RegVal);
      break;
    case MCP23017_GPIOB:
      WriteRegister(MCP23017_GPIOB, RegVal);
      break;
  }
}

void MCP23017::WriteIOBit(uint8_t Bank_Number, uint8_t BitNum, bool BitValue)
{
  switch(Bank_Number)
  {
    case 'A':
      WriteRegisterBit(MCP23017_GPIOA, BitNum, BitValue);
      break;
    case 'B':
      WriteRegisterBit(MCP23017_GPIOB, BitNum, BitValue);
      break;
    case MCP23017_GPIOA:
      WriteRegisterBit(MCP23017_GPIOA, BitNum, BitValue);
      break;
    case MCP23017_GPIOB:
      WriteRegisterBit(MCP23017_GPIOB, BitNum, BitValue);
      break;
  }
}

bool MCP23017::ReadRegisterBit(uint8_t Reg, uint8_t BitNum)
{
  if((ReadRegister(Reg) & (0x01 << BitNum)) == 0)
  {
    return false;
  } else
    {
      return true;
    }
}

void MCP23017::WriteRegisterBit(uint8_t Reg, uint8_t BitNum, bool BitValue)
{
  uint8_t _ReadReg, _WriteReg, _WriteVal;
  switch(Reg)
  {
    case MCP23017_GPINTENA:
      _ReadReg = MCP23017_GPINTENA;
      _WriteReg = MCP23017_GPINTENA;
      break;
    case MCP23017_GPINTENB:
      _ReadReg = MCP23017_GPINTENB;
      _WriteReg = MCP23017_GPINTENB;
      break;
    case MCP23017_GPIOA:
      _ReadReg = MCP23017_OLATA;
      _WriteReg = MCP23017_GPIOA;
      break;
    case MCP23017_GPIOB:
      _ReadReg = MCP23017_OLATB;
      _WriteReg = MCP23017_GPIOB;
      break;
    case MCP23017_GPPUA:
      _ReadReg = MCP23017_GPPUA;
      _WriteReg = MCP23017_GPPUA;
      break;
    case MCP23017_GPPUB:
      _ReadReg = MCP23017_GPPUB;
      _WriteReg = MCP23017_GPPUB;
      break;
    case MCP23017_IODIRA:
      _ReadReg = MCP23017_IODIRA;
      _WriteReg = MCP23017_IODIRA;
      break;
    case MCP23017_IODIRB:
      _ReadReg = MCP23017_IODIRB;
      _WriteReg = MCP23017_IODIRB;
      break;
    case MCP23017_IOCONA:
      _ReadReg = MCP23017_IOCONA;
      _WriteReg = MCP23017_IOCONA;
      break;
    case MCP23017_IOCONB:
      _ReadReg = MCP23017_IOCONB;
      _WriteReg = MCP23017_IOCONB;
      break;
  }

  _WriteVal = ReadRegister(_ReadReg);

  if(BitValue == HIGH)
  {
    _WriteVal |= 1 << BitNum;
  } else
    {
      _WriteVal &= ~(1 << BitNum);
    }

  WriteRegister(_WriteReg, _WriteVal);
}

uint8_t MCP23017::ReadRegister(uint8_t Reg)
{
  Wire.beginTransmission(_Addr);
  Wire.write(Reg);
  Wire.endTransmission();
  Wire.requestFrom(_Addr, 1);
  return Wire.read();
}

void MCP23017::WriteRegister(uint8_t Reg, uint8_t Val)
{
  Wire.beginTransmission(_Addr);
  Wire.write(Reg);
  Wire.write(Val);
  Wire.endTransmission();
}
