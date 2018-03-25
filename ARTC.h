#ifndef _ARTC_h
#define _ARTC_h

#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include "Arduino.h"

 class ARTC{
  tmElements_t _tm; 
  char _alarm[6]="ALARM"; // 00:00
 
  int _ATriggered = 0; // To avoid multiple calls during the alarm (one minute) 
  
  public:
  void setHourTimeToMessage(char *message);
  int checkAlarm();
  
  void setAlarm(char *alarm);
  void getAlarm(char *alarm);

  void setCTime(char *adate);
 };

#endif

