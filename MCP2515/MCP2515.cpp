#include "MCP2515.h"

MCP2515::MCP2515(){

}

void MCP2515::StartSPI()
{
  SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(1<<SPR0);
  SPSR = 0;
  SPI.begin();
}

void MCP2515::Init(unsigned char BaudRate,unsigned char SSPin){
  _SSPin = SSPin;
  pinMode(_SSPin,OUTPUT);
  digitalWrite(_SSPin,HIGH);
  delay(10);
  Reset();

  ModifyRegister(MCP_CANCTRL,CANCTRL_MODE_MASK,MODE_CONFIG);

  switch (BaudRate) {
    case (CAN_5KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_5kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_5kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_5kBPS_CFG3);
      break;
    case (CAN_10KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_10kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_10kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_10kBPS_CFG3);
      break;
    case (CAN_20KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_20kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_20kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_20kBPS_CFG3);
      break;
    case (CAN_40KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_40kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_40kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_40kBPS_CFG3);
      break;
    case (CAN_50KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_50kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_50kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_50kBPS_CFG3);
      break;
    case (CAN_80KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_80kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_80kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_80kBPS_CFG3);
      break;
    case (CAN_100KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_100kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_100kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_100kBPS_CFG3);
      break;
    case (CAN_125KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_125kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_125kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_125kBPS_CFG3);
      break;
    case (CAN_200KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_200kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_200kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_200kBPS_CFG3);
      break;
    case (CAN_250KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_250kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_250kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_250kBPS_CFG3);
      break;
    case (CAN_500KBPS):
      SetRegister(MCP_CNF1,MCP_16MHz_500kBPS_CFG1);
      SetRegister(MCP_CNF2,MCP_16MHz_500kBPS_CFG2);
      SetRegister(MCP_CNF3,MCP_16MHz_500kBPS_CFG3);
      break;
    default:
      break;
  }

  SetRegister(MCP_CANINTE,MCP_RX0IE);                                                 // Interrupt on Rx Buffer 0 only
  SetRegister(MCP_BFPCTRL,BFPCTRL_B0BFM_MASK | BFPCTRL_B0BFE_MASK);                   // Use external interrupt on Rx Buffer 0 only
  SetRegister(MCP_TXRTSCTRL,0x00);
  SetRegister(MCP_RXB0CTRL,RXB0_ANY_MSG | RXB0_BUFF_ROLLOVER);
  SetRegister(MCP_RXB1CTRL,RXB1_ANY_MSG);
  ModifyRegister(MCP_CANCTRL,CANCTRL_MODE_MASK,MODE_NORMAL);
}

boolean MCP2515::SendMsg(unsigned int Id,unsigned int Ext,unsigned char Len,void* Data){
  boolean _MsgBufferAvail = false;
  unsigned char _DataBuf[CAN_HEADER_SIZE + CAN_SIZE];
  unsigned char _Status = ReadStatus();
  unsigned char _TxRegAddr,_TXCtrlAddr;

  if((_Status & STS_TX0REQ) == 0){
    _TxRegAddr = MCP_TXB0SIDH;
    _TXCtrlAddr = MCP_TXB0CTRL;
    _MsgBufferAvail = true;
  } else if ((_Status & STS_TX1REQ) == 0){
      _TxRegAddr = MCP_TXB1SIDH;
      _TXCtrlAddr = MCP_TXB1CTRL;
      _MsgBufferAvail = true;
    } else if ((_Status & STS_TX2REQ) == 0){
        _TxRegAddr = MCP_TXB2SIDH;
	_TXCtrlAddr = MCP_TXB2CTRL;
        _MsgBufferAvail = true;
      }

  if(_MsgBufferAvail){
    _DataBuf[0] = Id >> 3;
    _DataBuf[1] = Id << 5;
    _DataBuf[2] = Ext >> 8;
    _DataBuf[3] = Ext;
    _DataBuf[4] = Len & 0x0F;
    memcpy(&_DataBuf[CAN_HEADER_SIZE],Data,CAN_SIZE);
    SetRegisterS(_TxRegAddr,&_DataBuf,CAN_HEADER_SIZE + CAN_SIZE);
    ModifyRegister(_TXCtrlAddr,MCP_TXB_TXREQ_MASK,0xFF);
  }
  return _MsgBufferAvail;
}

void MCP2515::ReadMsg(unsigned int* Id,unsigned int* Ext,unsigned char* Len,void* Data){
  boolean _MsgInBuffer = false;
  unsigned char _DataBuf[CAN_HEADER_SIZE + CAN_SIZE];
  unsigned char _Status = ReadRegister(MCP_CANINTF);
  unsigned char _RxRegAddr;

  if((_Status & MCP_RX0IF) == MCP_RX0IF){
    _RxRegAddr = MCP_RXB0SIDH;
    _MsgInBuffer = true;
  } else if ((_Status & MCP_RX1IF) == MCP_RX1IF){
      _RxRegAddr = MCP_RXB1SIDH;
      _MsgInBuffer = true;
    }

  if(_MsgInBuffer){
    ReadRegisterS(_RxRegAddr,&_DataBuf,CAN_HEADER_SIZE + CAN_SIZE);
    *Id =((unsigned int)(_DataBuf[0]) << 3) | (_DataBuf[1] >> 5);
    *Ext = ((unsigned int)(_DataBuf[2]) << 8) | _DataBuf[1];
    *Len = _DataBuf[4] & 0x0F;
    memcpy(Data,&_DataBuf[CAN_HEADER_SIZE],CAN_SIZE);

    if(_RxRegAddr == MCP_RXB0SIDH){
      ModifyRegister(MCP_CANINTF,MCP_RX0IF,0x00);
    } else if (_RxRegAddr == MCP_RXB1SIDH){
        ModifyRegister(MCP_CANINTF,MCP_RX1IF,0x00);
      }
  }
}

unsigned char MCP2515::CheckReceiveBuffers(){
  unsigned char _Status = ReadRegister(MCP_CANINTF);
  unsigned char _NumOfMsgs = 0;
  if((_Status & MCP_RX0IF) == MCP_RX0IF){
    _NumOfMsgs++;
  }
  if((_Status & MCP_RX1IF) == MCP_RX1IF){
    _NumOfMsgs++;
  }
  return _NumOfMsgs;
}

unsigned char MCP2515::CheckError(){
  return ReadRegister(MCP_EFLG);
}

void MCP2515::Reset(){
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_RESET);
  digitalWrite(_SSPin, HIGH);
  delay(10);
}

void MCP2515::SetRegister(unsigned char Reg,unsigned char Value){
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_WRITE);
  SPI.transfer(Reg);
  SPI.transfer(Value);
  digitalWrite(_SSPin, HIGH);
}

void MCP2515::SetRegisterS(unsigned char Reg,void* Buf,unsigned char Num){
  unsigned char _RBuf[Num];
  memcpy(&_RBuf,Buf,Num);
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_WRITE);
  SPI.transfer(Reg);
  for(unsigned char _i=0;_i<Num;_i++){
    SPI.transfer(_RBuf[_i]);
  }
  digitalWrite(_SSPin, HIGH);
}

unsigned char MCP2515::ReadRegister(unsigned char Reg){
  unsigned char _RegVal;
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_READ);
  SPI.transfer(Reg);
  _RegVal = SPI.transfer(0x00);
  digitalWrite(_SSPin, HIGH);
  return _RegVal;
}

void MCP2515::ReadRegisterS(unsigned char Reg,void* Buf,unsigned char Num){
  unsigned char _RBuf[Num];
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_READ);
  SPI.transfer(Reg);
  for (unsigned char _i=0;_i<Num;_i++){
    _RBuf[_i] = SPI.transfer(0x00);
  }
  memcpy(Buf,&_RBuf,Num);
  digitalWrite(_SSPin, HIGH);
}

void MCP2515::ModifyRegister(unsigned char Reg,unsigned char Mask,unsigned char Data){
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_BITMOD);
  SPI.transfer(Reg);
  SPI.transfer(Mask);
  SPI.transfer(Data);
  digitalWrite(_SSPin, HIGH);
}

unsigned char MCP2515::ReadStatus(){
  unsigned char _RetVal;
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_READ_STATUS);
  _RetVal = SPI.transfer(0x00);
  digitalWrite(_SSPin, HIGH);
  return _RetVal;
}

unsigned char MCP2515::ReadRxStatus(){
  unsigned char _RetVal;
  digitalWrite(_SSPin, LOW);
  SPI.transfer(MCP_RX_STATUS);
  _RetVal = SPI.transfer(0x00);
  digitalWrite(_SSPin, HIGH);
  return _RetVal;
}






