#ifndef MCP2515_dfs_h
#define MCP2515_dfs_h

#include "Arduino.h"

// Define MCP2515 register addresses
#define MCP_RXF0SIDH            0x00
#define MCP_RXF0SIDL            0x01
#define MCP_RXF0EID8            0x02
#define MCP_RXF0EID0            0x03
#define MCP_RXF1SIDH            0x04
#define MCP_RXF1SIDL            0x05
#define MCP_RXF1EID8            0x06
#define MCP_RXF1EID0            0x07
#define MCP_RXF2SIDH            0x08
#define MCP_RXF2SIDL            0x09
#define MCP_RXF2EID8            0x0A
#define MCP_RXF2EID0            0x0B
#define MCP_BFPCTRL             0x0C
#define MCP_CANSTAT             0x0E
#define MCP_CANCTRL             0x0F
#define MCP_RXF3SIDH            0x10
#define MCP_RXF3SIDL            0x11
#define MCP_RXF3EID8            0x12
#define MCP_RXF3EID0            0x13
#define MCP_RXF4SIDH            0x14
#define MCP_RXF4SIDL            0x15
#define MCP_RXF4EID8            0x16
#define MCP_RXF4EID0            0x17
#define MCP_RXF5SIDH            0x18
#define MCP_RXF5SIDL            0x19
#define MCP_RXF5EID8            0x1A
#define MCP_RXF5EID0            0x1B
#define MCP_TEC                 0x1C
#define MCP_REC                 0x1D
#define MCP_RXM0SIDH            0x20
#define MCP_RXM0SIDL            0x21
#define MCP_RXM0EID8            0x22
#define MCP_RXM0EID0            0x23
#define MCP_RXM1SIDH            0x24
#define MCP_RXM1SIDL            0x25
#define MCP_RXM1EID8            0x26
#define MCP_RXM1EID0            0x27
#define MCP_CNF3                0x28
#define MCP_CNF2                0x29
#define MCP_CNF1                0x2A
#define MCP_CANINTE             0x2B
#define MCP_CANINTF             0x2C
#define MCP_EFLG                0x2D
#define MCP_TXB0CTRL            0x30
#define MCP_TXB1CTRL            0x40
#define MCP_TXB2CTRL            0x50
#define MCP_RXB0CTRL            0x60
#define MCP_RXB0SIDH            0x61
#define MCP_RXB1CTRL            0x70
#define MCP_RXB1SIDH            0x71
#define MCP_TXRTSCTRL           0x0D
#define MCP_RXF0SIDH            0x00
#define MCP_RXF0SIDH            0x00
#define MCP_TXB0SIDH            0x31
#define MCP_TXB1SIDH            0x41
#define MCP_TXB2SIDH            0x51

// Define SPI Instruction Set
#define MCP_WRITE               0x02
#define MCP_READ                0x03
#define MCP_BITMOD              0x05
#define MCP_LOAD_TX             0x40
#define MCP_LOAD_TX0            0x00
#define MCP_LOAD_TX1            0x02
#define MCP_LOAD_TX2            0x04
#define MCP_RTS                 0x80
#define MCP_RTS_TX0             0x81
#define MCP_RTS_TX1             0x82
#define MCP_RTS_TX2             0x84
#define MCP_RTS_ALL             0x87
#define MCP_READ_RX             0x90
#define MCP_READ_RX0            0x00
#define MCP_READ_RX1            0x04
#define MCP_READ_STATUS         0xA0
#define MCP_RX_STATUS           0xB0
#define MCP_RESET               0xC0

// CANCTRL Register Values
#define MODE_NORMAL             0x00
#define MODE_SLEEP              0x20
#define MODE_LOOPBACK           0x40
#define MODE_LISTENONLY         0x60
#define MODE_CONFIG             0x80
#define MODE_POWERUP            0xE0
#define CANCTRL_MODE_MASK       0xE0
#define ABORT_TX                0x10
#define MODE_ONESHOT            0x08
#define CLKOUT_ENABLE           0x04
#define CLKOUT_DISABLE          0x00
#define CLKOUT_PS1              0x00
#define CLKOUT_PS2              0x01
#define CLKOUT_PS4              0x02
#define CLKOUT_PS8              0x03

// CNF1 Register Values
#define SJW1                    0x00
#define SJW2                    0x40
#define SJW3                    0x80
#define SJW4                    0xC0

// CNF2 Register Values
#define BTLMODE                 0x80
#define SAMPLE_1X               0x00
#define SAMPLE_3X               0x40

// CNF3 Register Values
#define SOF_ENABLE              0x80
#define SOF_DISABLE             0x00
#define WAKFIL_ENABLE           0x40
#define WAKFIL_DISABLE          0x00

// CANINTE Register Bits
#define MCP_RX0IE               0x01
#define MCP_RX1IE               0x02
#define MCP_TX0IE               0x04
#define MCP_TX1IE               0x08
#define MCP_TX2IE               0x10
#define MCP_ERRIE               0x20
#define MCP_WAKIE               0x40
#define MCP_MERRE               0x80

// CANINTF Register Bits
#define MCP_RX0IF               0x01
#define MCP_RX1IF               0x02
#define MCP_TX0IF               0x04
#define MCP_TX1IF               0x08
#define MCP_TX2IF               0x10
#define MCP_ERRIF               0x20
#define MCP_WAKIF               0x40
#define MCP_MERRF               0x80

// Status Register Bits
#define STS_RX0IF               0x01
#define STS_RX1IF               0x02
#define STS_TX0REQ              0x04
#define STS_TX0IF               0x08
#define STS_TX1REQ              0x10
#define STS_TX1IF               0x20
#define STS_TX2REQ              0x40
#define STS_TX2IF               0x80

// RxStatus Register Bits
#define RX_REG_MSG_IN_RX0       0x40
#define RX_REG_MSG_IN_RX1       0x80
#define RX_REG_MSG_IN_BOTH_RX   0xC0

// Masks For TXBnCTRL registers.
#define MCP_TXB_ABTF_MASK       0x40
#define MCP_TXB_MLOA_MASK       0x20
#define MCP_TXB_TXERR_MASK      0x10
#define MCP_TXB_TXREQ_MASK      0x08
#define MCP_TXB_TXP1_MASK       0x02
#define MCP_TXB_TXP0_MASK       0x01

// Masks For BFPCTRL Register
#define BFPCTRL_B1BFS_MASK      0x20
#define BFPCTRL_B0BFS_MASK      0x10
#define BFPCTRL_B1BFE_MASK      0x08
#define BFPCTRL_B0BFE_MASK      0x04
#define BFPCTRL_B1BFM_MASK      0x02
#define BFPCTRL_B0BFM_MASK      0x01

// RXB0CTRL Register
#define RXB0_ANY_MSG            0x60
#define RXB0_EXT_MSG_ONLY       0x40
#define RXB0_STD_MSG_ONLY       0x20
#define RXB0_ANY_MSG_W_FILTER   0x00
#define RXB0_BUFF_NO_ROLLOVER   0x00
#define RXB0_BUFF_ROLLOVER      0x04
#define RXB0_USE_RXF0           0x00
#define RXB0_USE_RXF1           0x01

// RXB1CTRL Register
#define RXB1_ANY_MSG            0x60
#define RXB1_EXT_MSG_ONLY       0x40
#define RXB1_STD_MSG_ONLY       0x20
#define RXB1_ANY_MSG_W_FILTER   0x00
#define RXB1_USE_RXF0           0x00
#define RXB1_USE_RXF1           0x01
#define RXB1_USE_RXF2           0x02
#define RXB1_USE_RXF3           0x03
#define RXB1_USE_RXF4           0x04
#define RXB1_USE_RXF5           0x05

// RXF0SIDL Register
#define RXF0_STD_FRAME          0x00
#define RXF0_EXT_FRAME          0x08

// RXF1SIDL Register
#define RXF1_STD_FRAME          0x00
#define RXF1_EXT_FRAME          0x08

// speed 16MHz
#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xb0)
#define MCP_16MHz_500kBPS_CFG3 (0x06)

#define MCP_16MHz_250kBPS_CFG1 (0x01)
#define MCP_16MHz_250kBPS_CFG2 (0xb0)
#define MCP_16MHz_250kBPS_CFG3 (0x06)

#define MCP_16MHz_200kBPS_CFG1 (0x00)
#define MCP_16MHz_200kBPS_CFG2 (0xba)
#define MCP_16MHz_200kBPS_CFG3 (0x07)

#define MCP_16MHz_125kBPS_CFG1 (0x01)
#define MCP_16MHz_125kBPS_CFG2 (0xba)
#define MCP_16MHz_125kBPS_CFG3 (0x07)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xba)
#define MCP_16MHz_100kBPS_CFG3 (0x07)

#define MCP_16MHz_80kBPS_CFG1  (0x03)
#define MCP_16MHz_80kBPS_CFG2  (0xbf)
#define MCP_16MHz_80kBPS_CFG3  (0x07)

#define MCP_16MHz_50kBPS_CFG1  (0x07)
#define MCP_16MHz_50kBPS_CFG2  (0xba)
#define MCP_16MHz_50kBPS_CFG3  (0x07)

#define MCP_16MHz_40kBPS_CFG1  (0x07)
#define MCP_16MHz_40kBPS_CFG2  (0xbf)
#define MCP_16MHz_40kBPS_CFG3  (0x07)

#define MCP_16MHz_20kBPS_CFG1  (0x0f)
#define MCP_16MHz_20kBPS_CFG2  (0xbf)
#define MCP_16MHz_20kBPS_CFG3  (0x07)

#define MCP_16MHz_10kBPS_CFG1  (0x1f)
#define MCP_16MHz_10kBPS_CFG2  (0xbf)
#define MCP_16MHz_10kBPS_CFG3  (0x07)

#define MCP_16MHz_5kBPS_CFG1  (0x3f)
#define MCP_16MHz_5kBPS_CFG2  (0xbf)
#define MCP_16MHz_5kBPS_CFG3  (0x07)

#define MCP2515_OK             0
#define MCP2515_FAIL           1
#define MCP_ALLTXBUSY          2

#define CAN_STDID              0
#define CAN_EXTID              1

#define CAN_5KBPS              1
#define CAN_10KBPS             2
#define CAN_20KBPS             3
#define CAN_40KBPS             4
#define CAN_50KBPS             5
#define CAN_80KBPS             6
#define CAN_100KBPS            7
#define CAN_125KBPS            8
#define CAN_200KBPS            9
#define CAN_250KBPS            10
#define CAN_500KBPS            11

#define CAN_OK                 0
#define CAN_FAILINIT           1
#define CAN_FAILTX             2
#define CAN_MSGAVAIL           3
#define CAN_NOMSG              4
#define CAN_CTRLERROR          5
#define CAN_GETTXBFTIMEOUT     6
#define CAN_SENDMSGTIMEOUT     7
#define CAN_ALL_TX_BUFF_FULL   8
#define CAN_FAIL               0xFF

#define CAN_SIZE               8
#define CAN_HEADER_SIZE        5
#endif
