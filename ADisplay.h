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
  void displaySet(char *date, char *alarm, bool settled, char type); 
  void setColorBlink(int pos, bool black, char *alarm, unsigned int color);
  void setCursorPrintlnColor(int posn, char key, char *alarm, unsigned int color);
 };

 

#endif

