#ifndef _ADisplay_h
#define _ADisplay_h


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


#include "Arduino.h"

 class ADisplay{

  public:
//  ADisplay();
  void setup();
  void println(char *msg);
  void displayDateAlarm(char *odate, char *date, char *alarm);
  void displaySetAlarm(char *date, char *alarm);
  void setAlarmBlink(int pos, bool black);
  void setCursorPrintln(int row, int col, char key);
 };

 

#endif

