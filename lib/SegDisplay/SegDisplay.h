#include "Arduino.h"

#ifndef SegDisplay_h
#define SegDisplay_h



class SegDisplay
{
  public:
  unsigned ShiftRegisters;
  SegDisplay(uint8_t DataPin, uint8_t ClockPin, uint8_t LatchPin);
  void sendSerialData(byte registerCount, byte *pValueArray);
  void updateDisplay(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  void clearDisplay();
  void blinkDisplay();
  void DisplayTemp(uint8_t data1, uint8_t data2);
  void DisplayHumid(uint8_t data1, uint8_t data2);
  void DisplayDate(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
  void DisplayYear(uint8_t data1);

  private:
  uint8_t _DataPin;
  uint8_t _ClockPin;
  uint8_t _LatchPin;
  uint8_t _data1;
  uint8_t _data2;
  uint8_t _data3;
  uint8_t _data4;
  
};

#endif
