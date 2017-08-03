#ifndef _ARTC_h
#define _ARTC_h

#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include "Arduino.h"

 class ARTC{
  tmElements_t tm; 
  char alarm[6]="ALARM"; // 00:00
  int ARelayState = 0; // 1 > On, 0 > Off
  int ATriggered = 0; // To avoid multiple calls during the alarm (one minute) 
  
  public:
  void setHourTimeToMessage(char *message);
  int checkAlarm();
  int getAlarmRelayState();
  void setAlarmRelayState(int state);
  void setAlarmRelay(char *malarm);
 };

#endif

