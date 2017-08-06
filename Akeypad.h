#ifndef _AKeypad_h
#define _AKeypad_h

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0',':','D'}
};
// R1 , R2, R3, R4, C1, C2, C3, C4 Pinouts of the keypad  
// 10 ,  9,  8,  7,  6,  5,  4,  3 Arduino pins
// 44 , 42, 40, 38, 36, 34, 32, 30 Arduino Mega
byte rowPins[ROWS] = {44, 42, 40,38}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {36, 34, 32, 30}; //connect to the column pinouts of the keypad




#endif



