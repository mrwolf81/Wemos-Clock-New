#include "Arduino.h"
#include "SegDisplay.h"
#define ShiftRegisters 4
  

SegDisplay::SegDisplay(uint8_t DataPin, uint8_t ClockPin, uint8_t LatchPin){
  
  pinMode(DataPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(LatchPin, OUTPUT);

  _DataPin = DataPin;
  _ClockPin = ClockPin;
  _LatchPin = LatchPin;
}

void SegDisplay::updateDisplay(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  byte RegArray [ShiftRegisters];
  byte Digits [10];
  
  Digits [0] = 1 + 2 + 4 + 8 + 16 + 32; //a
  Digits [1] = 2 + 4;                   //b
  Digits [2] = 1 + 2 +64 + 16 + 8;
  Digits [3] = 1 + 2 + 4 + 8 + 64;
  Digits [4] = 32 + 64 + 2 + 4;
  Digits [5] = 1 + 32 + 64 + 4 + 8;
  Digits [6] = 1 + 32 + 16 + 8 + 4+ 64;
  Digits [7] = 1 + 2 + 4;
  Digits [8] = 1 + 2 + 4 + 8 + 16 + 32 + 64;
  Digits [9] = 1 + 2 + 4 + 8 + 64 + 32;
  Digits [99] = 0;

  _data1 = data1;
  _data2 = data2;
  _data3 = data3;
  _data4 = data4;


  
  RegArray[0] = Digits[_data1 / 10];
  RegArray[1] = Digits[_data2 % 10];
  RegArray[2] = Digits[_data3 / 10];
  RegArray[3] = Digits[_data4 % 10];
  SegDisplay::sendSerialData(ShiftRegisters, RegArray);
}

void SegDisplay::clearDisplay(){
  byte RegArray [ShiftRegisters];
  RegArray[0] = 0;
  RegArray[1] = 0;
  RegArray[2] = 0;
  RegArray[3] = 0;
  SegDisplay::sendSerialData(ShiftRegisters, RegArray);
}
void SegDisplay::blinkDisplay(){
  byte RegArray [ShiftRegisters];
  byte Digits [2];
  Digits [8] = 8 + 4 + 2 + 64 + 32 + 1 + 16;
  Digits [99] = 0;
  
  for(int i=0;i<5;i++){
    RegArray[0] = Digits[8];
    RegArray[1] = Digits[8];
    RegArray[2] = Digits[8];
    RegArray[3] = Digits[8];
    SegDisplay::sendSerialData(ShiftRegisters, RegArray);
    delay(200);

    RegArray[0] = Digits[99];
    RegArray[1] = Digits[99];
    RegArray[2] = Digits[99];
    RegArray[3] = Digits[99];
    SegDisplay::sendSerialData(ShiftRegisters, RegArray);
    delay(200);
  }
}

void SegDisplay::DisplayTemp(uint8_t data1, uint8_t data2){
  byte RegArray [ShiftRegisters];
  byte Digits [14];

  Digits [0] = 1 + 2 + 4 + 8 + 16 + 32; //a
  Digits [1] = 2 + 4;                   //b
  Digits [2] = 1 + 2 +64 + 16 + 8;
  Digits [3] = 1 + 2 + 4 + 8 + 64;
  Digits [4] = 32 + 64 + 2 + 4;
  Digits [5] = 1 + 32 + 64 + 4 + 8;
  Digits [6] = 1 + 32 + 16 + 8 + 4+ 64;
  Digits [7] = 1 + 2 + 4;
  Digits [8] = 1 + 2 + 4 + 8 + 16 + 32 + 64;
  Digits [9] = 1 + 2 + 4 + 8 + 64 + 32;
  Digits [99] = 0;
  Digits [95] = 1 + 2 + 64 + 32;       // Degree dot
  Digits [96] = 1 + 32 + 16 + 8;      // Capital C
  Digits [97] = 64 + 16;              //  r, 80
  Digits [98] = 32 + 26 + 64 + 4;      //  h, 116

  //Digits [0] = 8 + 4 + 2 + 64 + 32 + 1; //a
  //Digits [1] = 4 + 2;                   //b
  //Digits [2] = 8 + 4 + 16 + 32 + 64;
  //Digits [3] = 8 + 4 + 16 + 2 + 64;
  //Digits [4] = 1 + 16 + 4 + 2;
  //Digits [5] = 8 + 1 + 16 + 2 + 64;
  //Digits [6] = 8 + 1 + 16 + 2 + 64 + 32;
  //Digits [7] = 8 + 4 + 2;
  //Digits [8] = 8 + 4 + 2 + 64 + 32 + 1 + 16;
  //Digits [9] = 8 + 4 + 2 + 1 + 16 + 64;
  //Digits [99] = 0;


  
  RegArray[0] = Digits[data1 / 10];
  RegArray[1] = Digits[data2 % 10];
  RegArray[2] = Digits[95];
  RegArray[3] = Digits[96];
  SegDisplay::sendSerialData(ShiftRegisters, RegArray);
}

void SegDisplay::DisplayHumid(uint8_t data1, uint8_t data2){
  byte RegArray [ShiftRegisters];
  byte Digits [14];

  Digits [0] = 1 + 2 + 4 + 8 + 16 + 32; //a
  Digits [1] = 2 + 4;                   //b
  Digits [2] = 1 + 2 +64 + 16 + 8;
  Digits [3] = 1 + 2 + 4 + 8 + 64;
  Digits [4] = 32 + 64 + 2 + 4;
  Digits [5] = 1 + 32 + 64 + 4 + 8;
  Digits [6] = 1 + 32 + 16 + 8 + 4+ 64;
  Digits [7] = 1 + 2 + 4;
  Digits [8] = 1 + 2 + 4 + 8 + 16 + 32 + 64;
  Digits [9] = 1 + 2 + 4 + 8 + 64 + 32;
  Digits [99] = 0;
  Digits [95] = 1 + 8 + 4 + 16;       // Degree dot
  Digits [96] = 8 + 1 + 32 + 64;      // Capital C
  Digits [97] = 64 + 16;              //  r, 80
  Digits [98] = 32 + 16 + 64 + 4;      //  h, 116
  
  //Digits [0] = 8 + 4 + 2 + 64 + 32 + 1; //a
  //Digits [1] = 4 + 2;                   //b
  //Digits [2] = 8 + 4 + 16 + 32 + 64;
  //Digits [3] = 8 + 4 + 16 + 2 + 64;
  //Digits [4] = 1 + 16 + 4 + 2;
  //Digits [5] = 8 + 1 + 16 + 2 + 64;
  //Digits [6] = 8 + 1 + 16 + 2 + 64 + 32;
  //Digits [7] = 8 + 4 + 2;
  //Digits [8] = 8 + 4 + 2 + 64 + 32 + 1 + 16;
  //Digits [9] = 8 + 4 + 2 + 1 + 16 + 64;
  //Digits [99] = 0;

  
  RegArray[0] = Digits[data1 / 10];
  RegArray[1] = Digits[data2 % 10];
  RegArray[2] = Digits[97];
  RegArray[3] = Digits[98];
  SegDisplay::sendSerialData(ShiftRegisters, RegArray);
}

void SegDisplay::DisplayDate(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  byte RegArray [ShiftRegisters];
  byte Digits [10];
  
  Digits [0] = 1 + 2 + 4 + 8 + 16 + 32; //a
  Digits [1] = 2 + 4;                   //b
  Digits [2] = 1 + 2 +64 + 16 + 8;
  Digits [3] = 1 + 2 + 4 + 8 + 64;
  Digits [4] = 32 + 64 + 2 + 4;
  Digits [5] = 1 + 32 + 64 + 4 + 8;
  Digits [6] = 1 + 32 + 16 + 8 + 4+ 64;
  Digits [7] = 1 + 2 + 4;
  Digits [8] = 1 + 2 + 4 + 8 + 16 + 32 + 64;
  Digits [9] = 1 + 2 + 4 + 8 + 64 + 32;
  Digits [99] = 0;
  
  //Digits [0] = 8 + 4 + 2 + 64 + 32 + 1; //a
  //Digits [1] = 4 + 2;                   //b
  //Digits [2] = 8 + 4 + 16 + 32 + 64;
  //Digits [3] = 8 + 4 + 16 + 2 + 64;
  //Digits [4] = 1 + 16 + 4 + 2;
  //Digits [5] = 8 + 1 + 16 + 2 + 64;
  //Digits [6] = 8 + 1 + 16 + 2 + 64 + 32;
  //Digits [7] = 8 + 4 + 2;
  //Digits [8] = 8 + 4 + 2 + 64 + 32 + 1 + 16;
  //Digits [9] = 8 + 4 + 2 + 1 + 16 + 64;
  //Digits [99] = 0;

  
  RegArray[0] = Digits[data1 / 10];
  RegArray[1] = Digits[data2 % 10];
  RegArray[2] = Digits[data3 / 10];
  RegArray[3] = Digits[data4 % 10];
  SegDisplay::sendSerialData(ShiftRegisters, RegArray);
}

void SegDisplay::DisplayYear(uint8_t data1){
  byte RegArray [ShiftRegisters];
  byte Digits [10];

  Digits [0] = 1 + 2 + 4 + 8 + 16 + 32; //a
  Digits [1] = 2 + 4;                   //b
  Digits [2] = 1 + 2 +64 + 16 + 8;
  Digits [3] = 1 + 2 + 4 + 8 + 64;
  Digits [4] = 32 + 64 + 2 + 4;
  Digits [5] = 1 + 32 + 64 + 4 + 8;
  Digits [6] = 1 + 32 + 16 + 8 + 4+ 64;
  Digits [7] = 1 + 2 + 4;
  Digits [8] = 1 + 2 + 4 + 8 + 16 + 32 + 64;
  Digits [9] = 1 + 2 + 4 + 8 + 64 + 32;
  Digits [99] = 0;
  
  //Digits [0] = 8 + 4 + 2 + 64 + 32 + 1; //a
  //Digits [1] = 4 + 2;                   //b
  //Digits [2] = 8 + 4 + 16 + 32 + 64;
  //Digits [3] = 8 + 4 + 16 + 2 + 64;
  //Digits [4] = 1 + 16 + 4 + 2;
  //Digits [5] = 8 + 1 + 16 + 2 + 64;
  //Digits [6] = 8 + 1 + 16 + 2 + 64 + 32;
  //Digits [7] = 8 + 4 + 2;
  //Digits [8] = 8 + 4 + 2 + 64 + 32 + 1 + 16;
  //Digits [9] = 8 + 4 + 2 + 1 + 16 + 64;
  //Digits [99] = 0;
 
  RegArray[0] = Digits[(data1 % 1000)/100];
  RegArray[1] = Digits[data1 / 1000];
  RegArray[2] = Digits[data1 / 100];
  RegArray[3] = Digits[(data1 % 100)/10];
  SegDisplay::sendSerialData(ShiftRegisters, RegArray);
}

void SegDisplay::sendSerialData (byte registerCount, byte *pValueArray) {
  // Signal to the 595s to listen for data
  digitalWrite (_LatchPin, LOW);

  for (byte reg = registerCount; reg > 0; reg--)
  {
    byte value = pValueArray [reg - 1];

    for (byte bitMask = 128; bitMask > 0; bitMask >>= 1)
    {
      digitalWrite (_ClockPin, LOW);
      digitalWrite (_DataPin, value & bitMask ? HIGH : LOW);
      digitalWrite (_ClockPin, HIGH);
    }
  }
  // Signal to the 595s that I'm done sending
  digitalWrite (_LatchPin, HIGH);
}  // sendSerialData
