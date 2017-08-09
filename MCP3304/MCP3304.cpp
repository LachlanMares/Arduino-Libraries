#include <SPI.h>
#include "MCP3304.h"
#include <Arduino.h>

MCP3304::MCP3304(int CS)
{
  _CS = CS;
  pinMode(_CS, OUTPUT);
  digitalWrite(_CS, HIGH);
  SPI.begin();
}

int MCP3304::readADC(int pin, boolean sgl)
{
  if(pin >= 0 && pin < 8)
  {
    SPI.setClockDivider(SPI_CLOCK_DIV16);                                         //Set Clockdivider for 1MHz SPI freq.
    SPI.setBitOrder(MSBFIRST);                                                    //set to most significatn bit first
    SPI.setDataMode(SPI_MODE0);                                                   //SPI 0,0 as per MCP330x data sheet

    uint8_t configBits =  sgl ? SINGLE_MODE : DIFF_MODE;

    digitalWrite(_CS, LOW);                                                       //activate Chipselect
    SPI.transfer(configBits | (pin >> 1));                                        //4bits 0, startbit, SGL/DIFF, 2 Channelbits (D2, D1)
    uint8_t hi = SPI.transfer(pin << 7);                                          //lowest Channelbit (D0), rest dont care; return= first 2 returnbits undef, nullbit, Signbit, 4 highest databits
    uint8_t lo = SPI.transfer(0x00);                                              //send dont care; return = 8 lowest databits
    digitalWrite(_CS, HIGH);                                                      //deactivate Chipselect

    uint8_t sign = hi & 0x10;                                                     //extract Sign Bit for DIFF
    int adcValue = ((hi & 0x0f) << 8) + lo;                                       //combinig the 2 return Values

    if(sign) adcValue -= 4096;                                                    //if CH- > CH+

    SPI.setClockDivider(SPI_CLOCK_DIV4);  //set back to default SPI speed

    return adcValue;
  } else
    {
      return 0;
    }
}

int MCP3304::readSingle(int pin)
{
  if(pin >= 0 && pin < 8)
  {
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);

    digitalWrite(_CS, LOW);
    SPI.transfer(SINGLE_MODE | (pin >> 1));
    uint8_t hi = SPI.transfer(pin << 7);
    uint8_t lo = SPI.transfer(0x00);
    digitalWrite(_CS, HIGH); //deactivate Chipselect

    int adcValue = ((hi & 0x0f) << 8) + lo;
    SPI.setClockDivider(SPI_CLOCK_DIV4);  //set back to default

    return adcValue;
  } else
    {
      return 0;
    }
}

int MCP3304::readDifferential(int pin)
{
  if(pin >= 0 && pin < 8)
  {
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);

    digitalWrite(_CS, LOW);
    SPI.transfer(DIFF_MODE | (pin >> 1));
    uint8_t hi = SPI.transfer(pin << 7);
    uint8_t lo = SPI.transfer(0x00);
    digitalWrite(_CS, HIGH);

    uint8_t sign = hi & 0x10;
    int adcValue = ((hi & 0x0f) << 8) + lo;

    if(sign) adcValue -= 4096;

    SPI.setClockDivider(SPI_CLOCK_DIV4);

    return adcValue;
  } else
    {
      return 0;
    }
}
