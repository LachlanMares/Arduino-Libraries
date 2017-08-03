#include "MCP23008.h"

MCP23008::MCP23008()
{
  _Addr = MCP23008_ADDR_0;
}

MCP23008::MCP23008(uint8_t Addr)
{
  _Addr = Addr;
}

void MCP23008::StartI2C()
{
  Wire.begin();
  TWBR = ((16000000L/400000L) - 16) / 2;        // I2C bus 400kHz
}

void MCP23008::SetDirection(uint8_t RegVal)
{
  WriteRegister(MCP23008_IODIR,RegVal);
}

void MCP23008::SetDirectionBit(uint8_t BitNum,boolean BitValue)
{
  WriteRegisterBit(MCP23008_IODIR,BitNum,BitValue);
}

void MCP23008::SetPullUp(uint8_t RegVal)
{
  WriteRegister(MCP23008_GPPU,RegVal);
}

void MCP23008::SetPullUpBit(uint8_t BitNum,boolean BitValue)
{
  WriteRegisterBit(MCP23008_GPPU,BitNum,BitValue);
}

void MCP23008::SetPolarity(uint8_t RegVal)
{
  WriteRegister(MCP23008_IPOL,RegVal);
}

void MCP23008::SetBitPolarity(uint8_t BitNum,boolean BitValue)
{
  WriteRegisterBit(MCP23008_IPOL,BitNum,BitValue);
}

void MCP23008::EnableInterrupt(uint8_t RegVal)
{
  WriteRegister(MCP23008_GPINTEN,RegVal);
}

void MCP23008::EnableInterruptBit(uint8_t BitNum,boolean BitValue)
{
  WriteRegisterBit(MCP23008_GPINTEN,BitNum,BitValue);
}

void MCP23008::SetInterruptControl(uint8_t RegVal)
{
  WriteRegister(MCP23008_INTCON,RegVal);
}

void MCP23008::SetInterruptControlBit(uint8_t BitNum,boolean BitValue)
{
  WriteRegisterBit(MCP23008_INTCON,BitNum,BitValue);
}

uint8_t MCP23008::ReadIOBank()
{
  return ReadRegister(MCP23008_GPIO);
}

boolean MCP23008::ReadIOBit(uint8_t BitNum)
{
  return ReadRegisterBit(MCP23008_GPIO,BitNum);
}

void MCP23008::WriteIOBank(uint8_t RegVal)
{
  WriteRegister(MCP23008_GPIO,RegVal);
}

void MCP23008::WriteIOBit(uint8_t BitNum,boolean BitValue)
{
  WriteRegisterBit(MCP23008_GPIO,BitNum,BitValue);
}

boolean MCP23008::ReadRegisterBit(uint8_t Reg,uint8_t BitNum){
  if((ReadRegister(Reg) & (0x01 << BitNum)) == 0){
    return false;
  } else {
      return true;
  }
}

void MCP23008::WriteRegisterBit(uint8_t Reg,uint8_t BitNum,boolean BitValue){
  uint8_t _ReadReg,_WriteReg,_WriteVal;

  switch(Reg){
    case MCP23008_GPINTEN:
      _ReadReg = MCP23008_GPINTEN;
      _WriteReg = MCP23008_GPINTEN;
      break;
    case MCP23008_GPIO:
      _ReadReg = MCP23008_OLAT;
      _WriteReg = MCP23008_GPIO;
      break;
    case MCP23008_GPPU:
      _ReadReg = MCP23008_GPPU;
      _WriteReg = MCP23008_GPPU;
      break;
    case MCP23008_IODIR:
      _ReadReg = MCP23008_IODIR;
      _WriteReg = MCP23008_IODIR;
      break;
    case MCP23008_IOCON:
      _ReadReg = MCP23008_IOCON;
      _WriteReg = MCP23008_IOCON;
      break;
  }

  _WriteVal = ReadRegister(_ReadReg);

  if(BitValue == HIGH){
    _WriteVal |= 1 << BitNum;
  } else {
      _WriteVal &= ~(1 << BitNum);
    }

  WriteRegister(_WriteReg,_WriteVal);
}

uint8_t MCP23008::ReadRegister(uint8_t Reg)
{
  Wire.beginTransmission(_Addr);
  Wire.write(Reg);
  Wire.endTransmission();
  Wire.requestFrom((int)(_Addr),1);
  uint8_t _retValue = Wire.read();
  Wire.endTransmission();
  return _retValue;
}

void MCP23008::WriteRegister(uint8_t Reg,uint8_t Val)
{
  Wire.beginTransmission(_Addr);
  Wire.write(Reg);
  Wire.write(Val);
  Wire.endTransmission();
}
