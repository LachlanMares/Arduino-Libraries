#ifndef MCP2515_H_
#define MCP2515_H_
#include "Arduino.h"
#include "MCP2515_dfs.h"
#include <SPI.h>

class MCP2515
{
public:
        MCP2515();
        void Init(unsigned char,unsigned char);
        void StartSPI();
        boolean SendMsg(unsigned int,unsigned int,unsigned char,void*);
        void ReadMsg(unsigned int*,unsigned int*,unsigned char*,void*);
        void SetMessageFiltering(unsigned char,unsigned char,unsigned char,unsigned int,unsigned int);
        unsigned char CheckReceiveBuffers();
        unsigned char CheckError();

private:
        void Reset(void);
        void SetRegister(unsigned char,unsigned char);
        void SetRegisterS(unsigned char,void*,unsigned char);
        unsigned char ReadRegister(unsigned char);
        void ReadRegisterS(unsigned char,void*,unsigned char);
        void ModifyRegister(unsigned char,unsigned char,unsigned char);
        unsigned char ReadStatus();
        unsigned char ReadRxStatus();

        unsigned char _SSPin;
};
#endif
